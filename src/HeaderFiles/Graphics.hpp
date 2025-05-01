#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"

using namespace sf;

const int WINDOW_SIZE = 1120;

struct  Graphics {
    Graphics();

    static void draw_point(RenderWindow &w, Vector2f pos, Color color, Vector2f offset, float cellSize);
    void draw(Population p, RenderWindow &w, Vector2f offset, float cellSize);
    void graphEvolution(RenderWindow &w, Population p, float turn, Vector2f offset);
    void start(RenderWindow &window);
    void menu();

    vector<float> rabbitsHistory = {};
    vector<float> foxesHistory = {};
    sf::Texture rabbitTexture;
};

#endif