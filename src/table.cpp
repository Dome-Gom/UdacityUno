#include <iostream>
#include <algorithm>
#include <random>
#include <memory>

#include "table.h"

Table::Table() : _maxNmbBots(5), _drawPileNumberDecks(4){
    GenerateDrawPile();
    _discardPile = std::move(_drawPile.back());
    _drawPile.pop_back();
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
}

bool Table::drawCards(int nmb, std::vector<Card> &deck){
        
        deck.insert(
            deck.end(), 
            std::make_move_iterator(_drawPile.end()-nmb), 
            std::make_move_iterator(_drawPile.end())
        );
        _drawPile.erase(_drawPile.end()-nmb, _drawPile.end());
}

void Table::RunGame(){

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

    while (userInput < 1 || userInput > _maxNmbBots)
    {
        std::cout << std::endl;
        std::cout << "Your input was out of range. Please choose a number between 1 and " << _maxNmbBots << "." << std::endl << std::endl << "Number enemies: ";
        std::cin >> userInput;
    } 
    
    _nmbBots = userInput;
    std::cout << std::endl << "Okay great! There will be " << _nmbBots << " enemies who will try to challenge you." << std::endl;
    std::cout << "Let the game beginn:";
    //Create bot treads
    for(int i = 0; i <= _nmbBots; i++){
        std::vector<Card> botDeck;
        drawCards(7, botDeck);
        Bot bot(std::move(botDeck), "Bot " + std::to_string(i+1));
        _bots.emplace_back(std::move(bot));
    }
    //_players.emplace_back(std::async(&Bot::play, std::make_unique<Bot>(), this));
    int t = 5;
}