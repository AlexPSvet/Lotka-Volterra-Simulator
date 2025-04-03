#ifndef GRID_HPP
#define GRID_HPP

#include "Entity.hpp"
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
    private:
        const float x, y;
};

class Grid {
    public:
        
    private:
        Coord grid[TAILLE_GRID * TAILLE_GRID];
};

#endif