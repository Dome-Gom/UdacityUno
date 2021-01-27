#ifndef USER_H_
#define USER_H_

//Forward declaration
class Table;

#include "player.h"


class User : public Player{

    public:
    User(std::vector<Card> &&playingCards);
    void play(Table* table);

    //Getter & Setter
    void setName(const std::string &name);
    std::string getName();
};

#endif /*USER_H_*/