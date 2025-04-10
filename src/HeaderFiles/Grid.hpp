#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include "HeaderFiles/Ensemble.hpp"

using namespace std;

static const int TAILLE_GRID = 10;

Ensemble grid;

struct Coord {
    public:
        Coord(int n);
        Coord(int x, int y);

        float getX() const;
        float getY() const;

        int toInt() const;

        Ensemble neighbours();

        ostream& operator<<(ostream& out);
        bool operator==(const Coord& c);
        bool operator!=(const Coord& c);
    private:
        int x, y;
};


#endif