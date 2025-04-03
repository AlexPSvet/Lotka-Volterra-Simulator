#include <iostream>
#include "HeaderFiles/Grid.hpp"

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

float Coord::getX() {
    return x;
}

float Coord::getY() {
    return y;
}

int Coord::toInt() {
    return y * TAILLE_GRID + x;  
}

ostream& operator<<(ostream& out, const Coord& c) {
    out << "(" << c.getX() << ", " << c.getY() << ")";
    return out;
}