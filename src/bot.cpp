#include <iostream>

#include "bot.h"
#include "table.h"

Bot::Bot(std::vector<Card> &&playingCards, std::string name){
    _playingCards = std::move(playingCards);
    _name = name;
}

void Bot::play(Table* table){
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
        
        //Play move
        Card discardPile = table->_discardPile;
        bool playMoveAllowed = false;

        if(discardPile._symbol == symbol::suspend){
            if (table->_discardPile._done == true)
                playMoveAllowed = true;
            else
                table->_discardPile._done = true;
                std::cout << "Bot has to suspend." << std::endl;
        }
        else if(discardPile._symbol == symbol::take2){
            if (table->_discardPile._done == true)
                playMoveAllowed = true;
            else{
                table->_discardPile._done = true;
                table->drawCards(2, _playingCards);
                std::cout << "Bot has to take 2 cards." << std::endl;
            }
        }
        else if(discardPile._symbol == symbol::take4WishColor){
            if (table->_discardPile._done == true)
                playMoveAllowed = true;
            else{
                table->_discardPile._done = true;
                table->drawCards(4, _playingCards);
                std::cout << "Bot has to take 4 cards." << std::endl;
            }
        }
        else{
            playMoveAllowed = true;
        }

        if(playMoveAllowed){
            std::vector<int> matchingPlayCards = matchingCards(discardPile);
            if(matchingPlayCards.empty()){
                table->drawCards(1, _playingCards);
                std::cout << "Bot has no matches. Therfore it has to take 1 card." << std::endl;
            }
            else{
                // Bot takes always first possible card.
                int choosenCard = matchingPlayCards[0];
                std::cout << "Choose your card(0-" << (_playingCards.size()-1) << "): ";
                std::cout << choosenCard;
                std::cout << std::endl;

                //Wish color in case of "wish card"
                if(_playingCards[choosenCard]._symbol == symbol::wishColor || _playingCards[choosenCard]._symbol == symbol::take4WishColor){
                    int colorWishBot;
                    //ToDo
                    _playingCards[choosenCard]._wish = color::blue;
                }
                //Toggel direction in case of direction turn cards
                if(_playingCards[choosenCard]._symbol == symbol::change){
                    if(table->_directionCCW){
                        table->_directionCCW = false;
                    }
                    else{
                        table->_directionCCW = true;
                    }
                }
                //Discard card on discard pile
                table->_discardPile = _playingCards[choosenCard];
                _playingCards.erase(_playingCards.begin() + choosenCard);
            }
        }
        //Print left cards and wait for 5 sec.
        std::cout << std::endl << "Left cards: " << _playingCards.size() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        //If game finished (no cards in _playingCards)
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