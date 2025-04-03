#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
using namespace std;

struct Coord {
    float x, y;
    Entity* animal;
};

class Grid {
    public:
        
    private:
        vector<Coord> grid;
};

#endif