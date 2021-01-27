#include <iostream>

#include "player.h"
#include "table.h"

void Player::play(Table* table){
    return;
}

void Player::printPlayingCards(){
    std::cout << "Playing cards:" << std::endl;
    int number = 0;
    for(auto card : _playingCards){
        std::cout << "(" << number << "): ";
        card.printCard();
        std::cout << "  ";
        number++;
    }
    std::cout << std::endl;
}

std::vector<int> Player::matchingCards(const Card &discardPile){
    std::vector<int> matchingCards;
    int number = 0;
    for(auto it = std::begin(_playingCards); it != std::end(_playingCards); it++, number++){
        if((*it)._symbol == symbol::take4WishColor){
            matchingCards.push_back(number);
            }
        else if((*it)._symbol == symbol::wishColor){
            matchingCards.push_back(number);
        }
        else{
            if((*it)._symbol == discardPile._symbol){
                matchingCards.push_back(number);
            }
            else if((*it)._color == discardPile._color){
                matchingCards.push_back(number);
            }
            else if(discardPile._symbol == symbol::wishColor && (*it)._color == discardPile._wish){
                matchingCards.push_back(number);
            }
            else if(discardPile._symbol == symbol::take4WishColor && (*it)._color == discardPile._wish){
                matchingCards.push_back(number);
            }
        }
    }
    return matchingCards;
}