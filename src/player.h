#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <string>

//Forward declaration
class Table;

#include "card.h"

class Player{

    protected:
    void printPlayingCards();
    std::vector<int> matchingCards(const Card &discardPile);
    std::vector<Card> _playingCards;

    public:
    Player* _leftPlayer;
    Player* _rightPlayer;
    virtual void play(Table* table);
    std::string _name;
};


#endif /*PLAYER_H_*/