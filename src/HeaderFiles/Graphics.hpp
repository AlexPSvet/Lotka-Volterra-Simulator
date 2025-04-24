#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include "Population.hpp"

using namespace sf;
using Point = Vector2f;

const int CELL_SIZE = 20;
const int WINDOW_SIZE = TAILLE_GRID * CELL_SIZE;

void draw_point(RenderWindow &w, Point pos, Color color);
void draw(Population p, RenderWindow &w);


#endif