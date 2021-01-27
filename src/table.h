#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
#include <future>
#include <string>
#include <mutex>
#include <condition_variable>

#include "card.h"
#include "bot.h"
#include "user.h"
#include "player.h"

class Table{

    public:
    //Constructor
    Table();
    //Function
    void RunGame();
    void drawCards(int nmb, std::vector<Card> &deck);
    void printDiscardPile();
    //Varibable
    Player* _nextPlayer;
    std::mutex _mtxNextPlayer;
    std::condition_variable _condNextPlayer;
    Player* _finishedPlayer;
    std::mutex _mtxPlayerFinished;
    std::condition_variable _condPlayerFinished;
    Card _discardPile;
    bool _directionCCW;

    private:
    //Function
    void GenerateDrawPile();
    void setNeighborPlayer();
    void printRanking();
    //Variable
    const int _drawPileNumberDecks;
    std::vector<Card> _drawPile;
    const int _maxNmbBots;
    int _nmbBots;
    std::vector<std::future<void>> _players;
    std::vector<std::string> _ranking;
    std::vector<std::shared_ptr<Bot>> _bots;
    std::shared_ptr<User> _user;
    const int _nmbStartCards;
};


#endif /*TABLE_H_*/