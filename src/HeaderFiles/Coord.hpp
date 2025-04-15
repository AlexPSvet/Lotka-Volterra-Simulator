#ifndef CORD_HPP
#define CORD_HPP

#include "Ensemble.hpp"
using namespace std;

const int TAILLE_GRID = 10;

const Ensemble grid;

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

class Grid {
    public:
        Grid();

        bool emptyCase(int pos) const;
        int getCaseId(int pos) const;

        void voidCase(int pos);
        void setCase(int id, int pos);

    private:
        Ensemble grid;
};

#endif