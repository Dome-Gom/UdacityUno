#include "bot.h"

Bot::Bot(std::vector<Card> &&playingCards, std::string name){
    _playingCards = std::move(playingCards);
    _name = name;
}

//void Bot::play(Table* table){

//}