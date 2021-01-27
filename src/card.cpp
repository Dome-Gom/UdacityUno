#include <iostream>

#include "card.h"

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

Card::Card(color wish, color color, symbol symbol): _wish(wish), _color(color), _symbol(symbol), _done(false) {}

void Card::printCard(){

    if(_symbol >= symbol::zero && _symbol <= symbol::take2){
        std::cout << colorAsString() << "-" << symbolAsString();
    }
    else{
        std::cout << symbolAsString() << " Wish: " << wishAsString();
    }
}

std::string Card::colorAsString(){
    switch (_color)
    {
        case color::red:
            return "Red";
        case color::blue:
            return "Blue";
        case color::green:
            return "Green";
        case color::yellow:
            return "Yellow";
        case color::black:
            return "Black";
        default:
            return "Error";
    }
}
std::string Card::symbolAsString(){
    switch (_symbol)
    {
        case symbol::zero:
            return "Zero";
        case symbol::one:
            return "One";
        case symbol::two:
            return "Two";
        case symbol::three:
            return "Three";
        case symbol::four:
            return "Four";
        case symbol::five:
            return "Five";
        case symbol::six:
            return "Six";
        case symbol::seven:
            return "Seven";
        case symbol::eight:
            return "Eight";
        case symbol::nine:
            return "Nine";
        case symbol::change:
            return "ChangeDirection";
        case symbol::suspend:
            return "Suspend";
        case symbol::take2:
            return "Take2";
        case symbol::take4WishColor:
            return "Take4WishColor";
        case symbol::wishColor:
            return "WishColor";
        default:
            return "Error";
    }
}
std::string Card::wishAsString(){
    switch (_wish)
    {
        case color::red:
            return "Red";
        case color::blue:
            return "Blue";
        case color::green:
            return "Green";
        case color::yellow:
            return "Yellow";
        case color::black:
            return "Black";
        default:
            return "Error";
    }
}