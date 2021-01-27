#ifndef USER_H_
#define USER_H_

//Forward declaration
class Table;

#include "player.h"

class User : public Player{

    public:
    //Constructor
    User(std::vector<Card> &&playingCards);
    //Function
    void play(Table* table);
};

#endif /*USER_H_*/