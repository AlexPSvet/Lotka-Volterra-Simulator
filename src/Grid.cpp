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

