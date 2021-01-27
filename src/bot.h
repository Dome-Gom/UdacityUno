#ifndef BOT_H_
#define BOT_H_

#include <string>

//Forward declaration
class Table;

#include "player.h"
#include "card.h"

class Bot : public Player{

    public:
    //Constructor
    Bot(std::vector<Card> &&playingCards, std::string name);
    //Function
    void play(Table* table);
};

#endif /*BOT_H_*/