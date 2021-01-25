#include"card.h"

color operator++(color& clr){
    if (clr == color::black) return clr;
    clr = static_cast<color>(static_cast<int>(clr)+1);
    return clr;
}

symbol operator++(symbol& sym){
    if (sym == symbol::lastValue) return sym;
    sym = static_cast<symbol>(static_cast<int>(sym)+1);
    return sym;
}

Card::Card(){

}

Card::Card(color wish, color color, symbol symbol): _wish(wish), _color(color), _symbol(symbol) {}