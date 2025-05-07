#include "Coord.hpp"

Coord::Coord() {
    x = -1;
    y = -1;
}

Coord::Coord(int n) {
    if (n < 0 || n >= TAILLE_GRID * TAILLE_GRID) {
        throw std::runtime_error("Invalid 1D coordinate index.");
    }

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

int Coord::getX() const{
    return x;
}

int Coord::getY() const{
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
    for (int i = max(x - 1, 0); i <= min(x + 1, TAILLE_GRID - 1); i++) {
        for (int j = max(y - 1, 0); j <= min(y + 1, TAILLE_GRID - 1); j++) {
            if (!(x == i && y == j)) {
                c.ajoute(Coord {i,j}.toInt());
            }
        }
    }
    return c;
}

Grid::Grid(int lenght) {
    gridLenght = lenght;
    restartGrid();
}

void Grid::voidCase(int i) {
    setValue(i, -1);
}

void Grid::restartGrid() {
    clear();
    set(-1, gridLenght * gridLenght);
}

Ensemble Grid::getEmptyCases() {
    Ensemble ens;
    for (int i = 0; i < cardinal(); i++) {
        if (this->operator[](i) == -1) {
            ens.ajoute(i);
        }
    }
    return ens;
}

int Grid::getGridLenght() {
    return gridLenght;
}