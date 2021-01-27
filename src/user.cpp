#include <iostream>
#include <algorithm>
#include <vector>


#include "user.h"
#include "table.h"

User::User(std::vector<Card> &&playingCards){
    _playingCards = std::move(playingCards);
}

void User::play(Table* table){
    bool gameFinished = false;

    while(gameFinished == false){
        //Wait until own turn
        std::unique_lock<std::mutex> pLock(table->_mtxNextPlayer);
        table->_condNextPlayer.wait(pLock, [this, table] {return table->_nextPlayer == this;});
        //Print Cards & name
        std::cout << std::endl << "------------------------------------------------------------------------------------" << std::endl;
        std::cout << "------------------------------------------------------------------------------------" << std::endl << std::endl;
        std::cout << "Next player: " << _name << std::endl << std::endl;
        table->printDiscardPile();
        std::cout << std::endl << std::endl;
        printPlayingCards();
        std::cout << std::endl;
        
        //Play move
        Card discardPile = table->_discardPile;
        bool playMoveAllowed = false;

        if(discardPile._symbol == symbol::suspend){
            if (table->_discardPile._done == true)
                playMoveAllowed = true;
            else
                table->_discardPile._done = true;
                std::cout << "You have to suspend." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(4));
        }
        else if(discardPile._symbol == symbol::take2){
            if (table->_discardPile._done == true)
                playMoveAllowed = true;
            else{
                table->_discardPile._done = true;
                table->drawCards(2, _playingCards);
                std::cout << "You have to take 2 cards." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(4));
            }
        }
        else if(discardPile._symbol == symbol::take4WishColor){
            if (table->_discardPile._done == true)
                playMoveAllowed = true;
            else{
                table->_discardPile._done = true;
                table->drawCards(4, _playingCards);
                std::cout << "You have to take 4 cards." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(4));
            }
        }
        else{
            playMoveAllowed = true;
        }

        if(playMoveAllowed){
            std::vector<int> matchingPlayCards = matchingCards(discardPile);
            if(matchingPlayCards.empty()){
                table->drawCards(1, _playingCards);
                std::cout << "You have no matches. Therfore you have to take 1 card." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(4));
            }
            else{
                // User has to choose a card.
                bool userInputValid = false;
                int userInput;
                std::cout << "Choose your card(0-" << (_playingCards.size()-1) << "): ";
                std::cin >> userInput;
                std::cout << std::endl;
                if(userInput >= 0 && userInput <= (_playingCards.size()-1)){
                    if(std::find(matchingPlayCards.begin(), matchingPlayCards.end(), userInput) != matchingPlayCards.end()){
                        userInputValid = true;
                    }    
                }
                while (userInputValid == false)
                {
                    std::cout << "Your input was out of range. Please choose a number between 1 and " << (_playingCards.size()-1) << "." << std::endl;
                    std::cout << "Choose your card(0-" << (_playingCards.size()-1) << "): ";
                    std::cin >> userInput;
                    std::cout << std::endl;
                    if(userInput >= 0 && userInput <= (_playingCards.size()-1)){
                        if(std::find(matchingPlayCards.begin(), matchingPlayCards.end(), userInput) != matchingPlayCards.end()){
                            userInputValid = true;
                        }    
                    }
                }
                //Wish color in case of "wish card"
                if(_playingCards[userInput]._symbol == symbol::wishColor || _playingCards[userInput]._symbol == symbol::take4WishColor){
                    int colorWishUser;
                    userInputValid = false;
                    std::cout << "You Can choose a color: 0=red, 1=blue, 2=green and 3=yellow." << std::endl;
                    std::cout << "Which one do you want to choose: ";
                    std::cin >> colorWishUser;
                    std::cout << std::endl;
                    if(colorWishUser >= static_cast<int>(color::red) && colorWishUser <= static_cast<int>(color::yellow)){
                            userInputValid = true;
                    }
                    while (userInputValid == false)
                    {
                        std::cout << "Your input was out of range. Please choose a number between 1 and 3." << std::endl;
                        std::cout << "Which one do you want to choose: ";
                        std::cin >> colorWishUser;
                        std::cout << std::endl;
                        if(colorWishUser >= static_cast<int>(color::red) && colorWishUser <= static_cast<int>(color::yellow)){
                            userInputValid = true;
                        }
                    }
                    _playingCards[userInput]._wish = (color)colorWishUser;
                }
                //Toggel direction in case of direction turn cards
                if(_playingCards[userInput]._symbol == symbol::change){
                    if(table->_directionCCW){
                        table->_directionCCW = false;
                    }
                    else{
                        table->_directionCCW = true;
                    }
                }
                //Discard card on discard pile
                std::cout << "Good choice." << std::endl;
                table->_discardPile = _playingCards[userInput];
                _playingCards.erase(_playingCards.begin() + userInput);
            }
        }
        //If game won (no cards in _playingCards)
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(_playingCards.empty()){
            table->_finishedPlayer = this;
            gameFinished = true;
            table->_nextPlayer = nullptr;
            table->_condPlayerFinished.notify_all();
        }
        else{
            if(table->_directionCCW){
                table->_nextPlayer = _rightPlayer;
            }
            else{
                table->_nextPlayer = _leftPlayer;
            }
            table->_condNextPlayer.notify_all();
        }
    }
}