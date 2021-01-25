#ifndef BOT_H_
#define BOT_H_

#include <string>

//Forward declaration
class Bot;

#include "player.h"
#include "card.h"

class Bot : public Player{

    public:
    Bot(std::vector<Card> &&playingCards, std::string name);
    void play(Table* table);

};

#endif /*BOT_H_*/