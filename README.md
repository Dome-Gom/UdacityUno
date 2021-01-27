# CPPND: Capstone Game Uno

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application starting with this repo, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Uno`.

## Project description

* Project type:       Project of my choice
* Project end date:   27.01.2021
* Project name:       Uno

Short Description:
This is a simple digital version of the card game "UNO". The rules can be found here: (https://en.wikipedia.org/wiki/Uno_(card_game)).
The user is able to choose 1 to 5 enemies/bot. The player (bot or user) who has placed all cards first, wins the game.

## Class/File structur

Each class has it's own .cpp and .h file.

* main
  * Starts the game.
* table
  * Represents the game table with discard pile and draw pile.
  * Initialze the game. 
  * Hold and start treads of object type user and bot.
  * Hold data for thread scheduling.
  * Finish the game.
* player
  * Base class for user and bot.
  * Holds commen attributes and functions.
* bot
  * Function play() simulates the behavior of the bot and runs in a seperate tread.
* user
  * Function play() represents the user during the game.
  * Automate mandatory steps for user like take cards from the drawing pile, if he/she has no fitting cards.
  * Communicate with user.
* card
  * Represent a single card.

## Acceptance Criterias

Loops, Functions, I/O

* The project demonstrates an understanding of C++ functions and control structures.
  * table.cpp: 158, 168, 175
* The project accepts user input and processes the input.
  * table.cpp: 114ff

Object Oriented Programming

* The project uses Object Oriented Programming techniques.
  * table.h

* Classes use appropriate access specifiers for class members.
  * table.h

* Class constructors utilize member initialization lists.
  * table.cpp: 8ff

* Classes abstract implementation details from their interfaces.
  * player.h: 25

* Classes encapsulate behavior.
  * player.h

* Classes follow an appropriate inheritance hierarchy.
  * Composition: card.h and table.h
  * Inheritance: player.h, bot.h and user.h

* Overloaded functions allow the same function to operate on different parameters.
  * card.h: 23 and 34

* Derived class functions override virtual base class functions.
  * player.h: 16 and user.h: 15

Memory Management

* The project makes use of references in function declarations.
  * player.h: 25

* The project uses move semantics to move data, instead of copying it, where possible.
  * bot.h: 16, table.cpp: 136

* The project uses smart pointers instead of raw pointers.
  * table.cpp: 136

Concurrency

* The project uses multithreading.
  * table.cpp: 136

* A promise and future is used in the project.
  *table.cpp: 136

* A mutex or lock is used in the project.
  * table.h: 26

* A condition variable is used in the project.
  * table.h: 27



