#include "HeaderFiles/Graphics.hpp"

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

