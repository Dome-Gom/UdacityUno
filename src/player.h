#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <string>

#include "card.h"
#include "table.h"

class Player{

    protected:
    Player* _leftPlayer;
    Player* _rightPlayer;
    std::vector<Card> _playingCards;
    std::string _name;

    public:
    //virtual void play(Table* table);
};


#endif /*PLAYER_H_*/