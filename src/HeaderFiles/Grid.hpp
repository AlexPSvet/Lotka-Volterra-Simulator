#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include <vector>
using namespace std;

static const int TAILLE_GRID = 10;

struct Coord {
    public:
        Coord(int n);
        Coord(int x, int y);

        float getX() const;
        float getY() const;

        int toInt() const;

        ostream& operator<<(ostream& out);
        bool operator==(const Coord& c);
        bool operator!=(const Coord& c);
    private:
        float x, y;
};

class Grid {
    public:
        
    private:
        Coord grid[TAILLE_GRID * TAILLE_GRID];
};

#endif