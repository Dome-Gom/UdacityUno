#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
#include <future>
#include <string>

//Forward declaration
class Table;

#include "card.h"
#include "bot.h"

class Table{

private:
const int _drawPileNumberDecks;
std::vector<Card> _drawPile;
Card _discardPile;
const int _maxNmbBots;
int _nmbBots;
std::vector<std::future<void>> _players;
std::vector<std::string> _ranking;
std::vector<Bot> _bots;

public:
Table();
void RunGame();
void GenerateDrawPile();
bool drawCards(int nmb, std::vector<Card> &deck);
};


#endif /*TABLE_H_*/