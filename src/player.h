#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <string>

//Forward declaration
class Table;

#include "card.h"

class Player{

    public:
    //Function
    virtual void play(Table* table);
    //Variable
    Player* _leftPlayer;
    Player* _rightPlayer;
    std::string _name;

    protected:
    //Function
    void printPlayingCards();
    std::vector<int> matchingCards(const Card &discardPile);
    //Variable
    std::vector<Card> _playingCards;
};


#endif /*PLAYER_H_*/