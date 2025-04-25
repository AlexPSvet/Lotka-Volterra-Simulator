#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"

using namespace sf;

const int CELL_SIZE = 20;
const int WINDOW_SIZE = TAILLE_GRID * CELL_SIZE;

struct Graphics {
    void draw_point(RenderWindow &w, Vector2f pos, Color color);
    void draw(Population p, RenderWindow &w);
    void start();
};

#endif