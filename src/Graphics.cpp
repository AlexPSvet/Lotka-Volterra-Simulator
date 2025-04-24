#include "HeaderFiles/Graphics.hpp"
#include <SFML/Graphics.hpp>
#include "HeaderFiles/Population.hpp"
#include "HeaderFiles/Coord.hpp"
#include "HeaderFiles/Simulator.hpp"

using namespace sf;
using Point = Vector2f;

const int CELL_SIZE = 20;
const int WINDOW_SIZE = TAILLE_GRID * CELL_SIZE;

void draw_point(RenderWindow &w, Point pos, Color color) {
    RectangleShape cell(Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setPosition(pos);
    cell.setFillColor(color);
    w.draw(cell);
}

void draw(Population p, RenderWindow &w) {
    const vector<Entity*> entities = p.getEntities();
    for (auto entitie : entities) {
        Coord coord = entitie->getCoord();
        float x = coord.getX();
        float y = coord.getY();
        float px = x * CELL_SIZE;
        float py = y * CELL_SIZE;

        if (entitie->getType() == Type::rabbit) {
            draw_point(w, {px, py}, Color::Blue);
        } else {
            draw_point(w, {px, py}, Color::Red);
        }
    }
}

int main() {
    Game game;
    game.start();

    RenderWindow window(VideoMode({WINDOW_SIZE,WINDOW_SIZE}, WINDOW_SIZE), "Simulación");
    window.setFramerateLimit(5);

    while (window.isOpen()) {
        window.clear(Color::White);
        draw(game.getPopulation(), window);
        game.next();
        window.display();
    }

    return 0;
}
