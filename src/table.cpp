#include <iostream>
#include <algorithm>
#include <random>
#include <memory>

#include "table.h"

Table::Table() : _maxNmbBots(5), _drawPileNumberDecks(4), _nmbStartCards(5){
    GenerateDrawPile();
    _discardPile = std::move(_drawPile.back());
    _drawPile.pop_back();
    _finishedPlayer = nullptr;
    _nextPlayer = nullptr;
    _directionCCW = true;
}

void Table::GenerateDrawPile(){
    //Generate draw pile
    //1 zero card per color
    for(color c = color::red; c != color::black; ++c){
        _drawPile.emplace_back(Card(color::black, c, symbol::zero ));
    }
    //Number one to nine each 2 cards per color
    for(color c = color::red; c != color::black; ++c){
        for(symbol s = symbol::one; s != symbol::take4WishColor; ++s)
        {
            _drawPile.emplace_back(Card(color::black, c, s));
            _drawPile.emplace_back(Card(color::black, c, s));
        }
    }
    //Action cards: wishColor and take4WishColor each 4 cards
    for(symbol s = symbol::take4WishColor; s != symbol::lastValue; ++s){
        _drawPile.emplace_back(Card(color::black, color::black, s));
        _drawPile.emplace_back(Card(color::black, color::black, s));
        _drawPile.emplace_back(Card(color::black, color::black, s));
        _drawPile.emplace_back(Card(color::black, color::black, s));
    }
    //Multiply number of decks
    auto simplDrawPile = _drawPile;
    for(int decks = 2;decks <= _drawPileNumberDecks; decks++){ 
        auto temp = simplDrawPile;
        _drawPile.insert(
            _drawPile.end(), 
            std::make_move_iterator(temp.begin()), 
            std::make_move_iterator(temp.end())
        );
    }
    //Shuffel drawPile
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(_drawPile.begin(), _drawPile.end(), std::default_random_engine(seed));
    return;
}

void Table::drawCards(int nmb, std::vector<Card> &deck){
        
    deck.insert(
        deck.end(), 
        std::make_move_iterator(_drawPile.end()-nmb), 
        std::make_move_iterator(_drawPile.end())
    );
    _drawPile.erase(_drawPile.end()-nmb, _drawPile.end());
    return;
}

void Table::printDiscardPile(){
   std::cout << "Discard pile: ";
   _discardPile.printCard();
}

void Table::setNeighborPlayer(){
    //Set player left & right
    _user->_rightPlayer = (*_bots.begin()).get();
    _user->_leftPlayer = (*(_bots.end()-1)).get();
    (*_bots.begin())->_leftPlayer = _user.get();
    (*(_bots.end()-1))->_rightPlayer = _user.get();

    for(int i = 0; i < _bots.size(); i++){
        if(i != 0){
            _bots[i]->_leftPlayer = _bots[i-1].get();
        }
        if(i != (_bots.size()-1)){
            _bots[i]->_rightPlayer = _bots[i+1].get();
        }
    }
}

void Table::printRanking(){
    std::cout << "Game end." << std::endl;
    std::cout << std::endl << "Ranking:" << std::endl;
    int nmbRank = 1;
    for(auto rank = std::begin(_ranking); rank != std::end(_ranking); ++rank, ++nmbRank){
        std::cout << nmbRank << ": " << (*rank) << std::endl;
    }
    std::cout << std::endl << "Thanks for gaming." << std::endl << std::endl;
    std::cout << "////////////////////////////////////////////////////////////////" << std::endl;
    std::cout << "////////////////////////////////////////////////////////////////" << std::endl << std::endl;
}

void Table::RunGame(){
    //Lock mutex for user tread
    std::unique_lock<std::mutex> pLock(_mtxNextPlayer);
    
    //Create user tread
    std::vector<Card> userDeck;
    drawCards(_nmbStartCards, userDeck);
    _user = std::make_shared<User>(std::move(userDeck));
    _players.emplace_back(std::async(std::launch::async, &User::play, _user, this));

    /*Initialze the game*/
    // Ask user number of enemies
    int userInput = -1;
    bool userInputOk = false;

    std::cout << "////////////////////////////////////////////////////////////////" << std::endl;
    std::cout << "////////////////////////////////////////////////////////////////" << std::endl << std::endl;
    std::cout << "Welcome to Dominik's UNO. Great that you want to play this game!" << std::endl;
    std::cout << "How many enemies do you want to have (1-" << _maxNmbBots << ")?";
    std::cout << std::endl << std::endl << "Number enemies: ";
    std::cin >> userInput;
    
    //Create Bots according to number request by user
    while (userInput < 1 || userInput > _maxNmbBots)
    {
        std::cout << std::endl;
        std::cout << "Your input was out of range. Please choose a number between 1 and " << _maxNmbBots << "." << std::endl << std::endl << "Number enemies: ";
        std::cin >> userInput;
    } 
    
    _nmbBots = userInput;
    std::cout << std::endl << "Okay great! There will be " << _nmbBots << " enemies who will try to challenge you." << std::endl;
    
    //Create bot treads
    for(int i = 0; i < _nmbBots; i++){
        std::vector<Card> botDeck;
        drawCards(_nmbStartCards, botDeck);
        std::shared_ptr<Bot> bot(new Bot(std::move(botDeck), "Bot " + std::to_string(i+1)));
        _bots.emplace_back(bot);
        _players.emplace_back(std::async(std::launch::async, &Bot::play, bot, this));
    }
    
    setNeighborPlayer();
    
    //Ask for user name
    std::string userInputString;

    std::cout << std::endl << "How is your name?" << std::endl;
    std::cout << std::endl << "Name: ";
    std::cin >> userInputString;
    _user->_name = userInputString;
    std::cout << std::endl << "Ok " << userInputString << ". Let the game beginn:" << std::endl << std::endl;;

    //Notify player to start
    _nextPlayer = _user.get();
    pLock.unlock();
    _condNextPlayer.notify_all();

    bool gameEnd = false;
    while(!gameEnd){
        //Wait for finisher
        std::unique_lock<std::mutex> fLock(_mtxPlayerFinished);
        _condPlayerFinished.wait(fLock, [this] {return _finishedPlayer != nullptr;});
        //Print player done and add to ranking
        std::cout << "------------------------------------------------------------------------------------" << std::endl;
        std::cout << "------------------------------------------------------------------------------------" << std::endl << std::endl;
        std::cout << _finishedPlayer->_name << " has finished the game." << std::endl;
        _ranking.emplace_back(_finishedPlayer->_name);
        //Check if finisher is user
        if(_user.get() == _finishedPlayer){
            for(auto bot : _bots){
                _ranking.emplace_back(bot->_name);
            }
            printRanking();
            gameEnd = true;
        }
        else{
            //Only set _nextPlayer one step bevore _condNextPlayer.notify_all(). 
            //Otherwise sporadic thread start could start a thread in  parallel.
            Player* nextPlayer;
            for(auto it = std::begin(_bots); it != std::end(_bots); it++){
                if((*it).get() == _finishedPlayer){
                    if(_directionCCW){
                        nextPlayer = _finishedPlayer->_rightPlayer;
                    }
                    else{
                        nextPlayer = _finishedPlayer->_leftPlayer;
                    }
                    _bots.erase(it);
                    break;
                }      
            }
            if(_bots.empty()){
                std::cout << "Sorry, but you lost the game." << std::endl;
                _ranking.emplace_back(_user->_name);
                printRanking();
                gameEnd = true;
            }
            else{
                setNeighborPlayer();
                _finishedPlayer = nullptr;
                _nextPlayer = _nextPlayer;
                _condNextPlayer.notify_all();
            }
        }
    }
}