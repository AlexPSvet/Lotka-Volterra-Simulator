#include "Graphics.hpp"

void Graphics::draw_point(RenderWindow &w, Vector2f pos, Color color, Vector2f offset) {
    RectangleShape cell(Vector2f(60, 60));
    cell.setPosition(pos + offset);
    cell.setFillColor(color);
    w.draw(cell);
}

void Graphics::draw(Population p, RenderWindow &w, Vector2f offset, float cellSize) {
    const vector<Entity*> entities = p.getEntities();
    for (auto entity : entities) {
        Coord coord = entity->getCoord();
        float x = coord.getX();
        float y = coord.getY();
        float px = x * cellSize;
        float py = y * cellSize;

        if (entity->getType() == Type::rabbit) {
            draw_point(w, {px, py}, Color::Blue, offset);
        } else {
            draw_point(w, {px, py}, Color::Red, offset);
        }
    }
    sleep(seconds(0.5));
}

void Graphics::start(RenderWindow &window) {
    EntityParams params;
    TypeParams rabbitParams(20, 5, 15, 1, 2, 65, 3, {});
    TypeParams foxParams(15, 5, 15, -1, 2, 65, 3, {Type::rabbit});
    params.addType(Type::rabbit, rabbitParams);
    params.addType(Type::fox, foxParams);

    Texture texture;
    if (!texture.loadFromFile("../Assets/Start.png")) {
        cerr << "Error: no se pudo cargar la imagen." << endl;
        return;
    }
    Sprite sprite(texture);

    FloatRect menuButton({950.f, 420.f}, {120.f, 280.f});
    RectangleShape Simulator(Vector2f(600.f, 600.f));
    Simulator.setPosition(Vector2f(270.f, 270.f));
    Simulator.setFillColor(Color::White);

    const float simulatorSize = 600.f;
    const int gridSize = TAILLE_GRID;
    const float cellSize = simulatorSize / gridSize;

    Game game(params, gridSize);
    game.start();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        if (Mouse::isButtonPressed(Mouse::Button::Left)) {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            if (menuButton.contains(mousePos)) {
                std::cout << "Menu presionado 🦊🚀" << std::endl;
                game.stop();
                return;
            }
        }
        window.clear(Color::White);
        window.draw(sprite);
        window.draw(Simulator);
        draw(game.getPopulation(), window, Simulator.getPosition(), cellSize);
        game.next();
        window.display();
    }
}

void Graphics::menu() {
    RenderWindow window(VideoMode({WINDOW_SIZE,WINDOW_SIZE}), "Simulation");
    window.setFramerateLimit(5);

    Texture texture;
    if (!texture.loadFromFile("../Assets/Life.png")) {
        cerr << "Error: no se pudo cargar la imagen." << endl;
        return;
    }

    Sprite sprite(texture);
    FloatRect startButton({280.f, 890.f}, {240.f, 80.f});
    FloatRect paramsButton({620.f, 890.f}, {220.f, 80.f});

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //Botones
        if (Mouse::isButtonPressed(Mouse::Button::Left)) {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            if (startButton.contains(mousePos)) {
                std::cout << "Start presionado 🦊🚀" << std::endl;
                start(window);

            }
            if (paramsButton.contains(mousePos)) {
                std::cout << "Params presionado 🐰🛠️" << std::endl;
            }
            sleep(sf::milliseconds(200));
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}
