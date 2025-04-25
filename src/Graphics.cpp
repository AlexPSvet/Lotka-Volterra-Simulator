#include "HeaderFiles/Graphics.hpp"
#include "Console.hpp"
#include "Game.hpp"

void Graphics::draw_point(RenderWindow &w, Point pos, Color color) {
    RectangleShape cell(Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setPosition(pos);
    cell.setFillColor(color);
    w.draw(cell);
}

void Graphics::draw(Population p, RenderWindow &w) {
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
    sleep(seconds(1));
}

void Graphics::start() {
    Console console;

    // Descomentar en caso de Emergencia
    // EntityParams params;
    // TypeParams foxParams(7, 20, 15, 10, 5, 20, 7, {Type::rabbit});
    // params.addType(Type::fox, foxParams);
    //
    // TypeParams rabbitParams(20, 50, 10, 4,10, 30, 1, {});
    // params.addType(Type::rabbit, rabbitParams);

    EntityParams params = console.getParams();

    Game game(params, TAILLE_GRID*TAILLE_GRID);
    game.start();

    RenderWindow window(VideoMode({WINDOW_SIZE,WINDOW_SIZE}, WINDOW_SIZE), "Simulation");
    window.setFramerateLimit(5);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(Color::White);
        draw(game.getPopulation(), window);
        game.next();
        window.display();
    }
}