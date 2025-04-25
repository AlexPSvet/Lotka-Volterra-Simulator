#ifndef CORD_HPP
#define CORD_HPP

#include "Ensemble.hpp"
using namespace std;

const int TAILLE_GRID = 10;

struct Coord {
    public:
        Coord();
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

class Grid : public Ensemble {
    public:
        Grid(int taille);

        void voidCase(int i);

        Ensemble getEmptyCases();
        int getGridLenght();
    private:
        int gridLenght;
};

#endif