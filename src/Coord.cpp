#include "Coord.hpp"

Coord::Coord() {
    x = -1;
    y = -1;
}

Coord::Coord(int n) {
    y = n / TAILLE_GRID;
    x = n % TAILLE_GRID;
}

Coord::Coord(int x, int y) {
    if (x < 0 || y < 0 || x > TAILLE_GRID - 1 || y > TAILLE_GRID - 1) {
        throw runtime_error("Coordinates are not valid.");
    }
    this->x = x;
    this->y = y;
}

float Coord::getX() const{
    return x;
}

float Coord::getY() const{
    return y;
}

int Coord::toInt() const{
    return y * TAILLE_GRID + x;  
}

ostream& Coord::operator<<(ostream& out) {
    out << "(" << getX() << ", " << getY() << ")";
    return out;
}

bool Coord::operator==(const Coord& c) {
    return c.getX() == getX() && c.getY() == getY();
}

bool Coord::operator!=(const Coord& c) {
    return !(*this == c);
}

Ensemble Coord::neighbours() {
    Ensemble c;
    for (int i=std::max(x-1,0); i<=std::min(x+1, TAILLE_GRID - 1); i++) {
        for (int j=max(y-1, 0); j<=min(y+1, TAILLE_GRID - 1); j++) {
            if (x != i && y != j) {
                c.ajoute(Coord {i,j}.toInt());
            }
        }
    }
    return c;
}

Grid::Grid(int taille) : grid{Ensemble{}} {
    for (int i = 0; i < taille; i++) {
        grid.ajoute(-1);
    }
}

bool Grid::emptyCase(int i) const {
    return (grid[i] == -1);
}

int Grid::getValue(int i) const {
    return grid[i];
}

Ensemble Grid::getEmptyCases() {
    Ensemble ens;
    for (int i = 0; i < grid.cardinal(); i++) {
        if (grid[i] == -1) {
            ens.ajoute(i);
        }
    }
    return ens;
}

void Grid::voidCase(int i) {
    grid.setValue(i, -1);
}

void Grid::setCase(int i, int o) {
    grid.setValue(i, o);
}

Ensemble& Grid::getEnsemble() {
    return grid;
}
