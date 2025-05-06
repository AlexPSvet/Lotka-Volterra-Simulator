#ifndef CORD_HPP
#define CORD_HPP

#include "Ensemble.hpp"
using namespace std;

const int TAILLE_GRID = 20;

/**
 * @brief Represents a 2D coordinate on the grid.
 */
struct Coord {
public:
    Coord();
    Coord(int n);            ///< Initializes from a single index.
    Coord(int x, int y);     ///< Initializes from x and y values.

    float getX() const;
    float getY() const;

    /// Converts the coordinate to a single integer (flattened index).
    int toInt() const;

    /// Returns neighboring coordinates (Moore or Von Neumann depending on implementation).
    Ensemble neighbours();

    ostream& operator<<(ostream& out);
    bool operator==(const Coord& c);
    bool operator!=(const Coord& c);

private:
    int x, y;
};

/**
 * @brief Represents the simulation grid and manages cell values.
 */
class Grid : public Ensemble {
public:
    /// Constructs a grid with the given side length.
    Grid(int taille);

    /// Empties the cell at the given index.
    void voidCase(int i);

    /// Resets the grid to initial empty state.
    void restartGrid();

    /// Returns a set of currently empty cells.
    Ensemble getEmptyCases();

    /// Returns the side length of the grid.
    int getGridLenght();

private:
    int gridLenght;
};

#endif
