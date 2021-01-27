#ifndef CARD_H_
#define CARD_H_

enum class symbol{
    zero = 0,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    change,
    suspend,
    take2,
    take4WishColor,
    wishColor,
    lastValue
};

symbol operator++(symbol& sym);

enum class color{
    red = 0, 
    blue,
    green,
    yellow,
    black,
    lastValue
};

color operator++(color& clr);

class Card{

    public:
    
    //Constructor
    Card();
    Card(color wish, color color, symbol symbol);
    //Function
    void printCard();
    std::string colorAsString();
    std::string symbolAsString();
    std::string wishAsString();
    //Variables
    color _color;
    symbol _symbol;
    color _wish;
    bool _done;
};

#endif /*CARD_H_*/