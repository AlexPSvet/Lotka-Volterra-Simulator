#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
#include "Game.hpp"

using namespace std;

class Console {
    public:
        void start();
        void stop();

        void setParams();
        void setGame(Game* game);
        
        Game* getGame();
    private:
        void simulation();
        void print();
        void drawGrid();

        void checkInput(string text, int& reponse);
        string toString(Type type);

        Game* game;
        int compteurFichier = 0;
};

#endif