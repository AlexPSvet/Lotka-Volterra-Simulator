#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>
#include "Game.hpp"

class Console {
    public:
        void start();

        void print();
        EntityParams getParams();

        string toString(Type type);
    private:
        Game* game;
};

#endif