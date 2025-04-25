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
    private:
        void print();
        void drawGrid();
        EntityParams getParams();

        void checkInput(string text, int& reponse);
        string toString(Type type);

        Game* game;
        int compteurFichier = 0;
};

#endif