#ifndef USER_H_
#define USER_H_

#include "player.h"
#include "table.h"

class User : public Player{

    public:
    void play(Table* table);
};

#endif /*USER_H_*/