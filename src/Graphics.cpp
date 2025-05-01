#include "HeaderFiles/Graphics.hpp"

Graphics::Graphics() {
    if (!rabbitTexture.loadFromFile("../Assets/bugs.png")) {
        std::cerr << "Error: no se pudo cargar la imagen del conejo." << std::endl;
    }
}

void Graphics::draw_point(RenderWindow &w, Vector2f pos, Color color, Vector2f offset, float cellSize) {
    RectangleShape cell(Vector2f(cellSize, cellSize));
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
            Sprite bugs(rabbitTexture);
            float scaleX = cellSize / rabbitTexture.getSize().x;
            float scaleY = cellSize / rabbitTexture.getSize().y;
            bugs.setScale({scaleX, scaleY});
            bugs.setPosition({px + offset.x, py + offset.y});
            w.draw(bugs);
        } else {
            draw_point(w, {px, py}, Color::Red, offset, cellSize);
        }
    }
    sleep(seconds(0.5));
}


void Graphics::graphEvolution(RenderWindow &w, Population p, float turn, Vector2f offset) {
    const vector<Entity*> entities = p.getEntities();
    float card_rab = 0;
    float card_fox = 0;
    float graphWidth = 250.f;
    float graphHeight = 200.f;
    float xStep = 5.f;
    float pointSize = 3.f;


    for (auto entity : entities) {
        if (entity->getType() == Type::rabbit) {
            card_rab++;
        } else {
            card_fox++;
        }
    }
    rabbitsHistory.push_back(card_rab);
    foxesHistory.push_back(card_fox);

    float max_y = 1.f;
    for (size_t i = 0; i < rabbitsHistory.size(); ++i) {
        max_y = std::max(max_y, std::max(rabbitsHistory[i], foxesHistory[i]));
    }

    VertexArray axes(PrimitiveType::Lines, 4);
    axes[0].position = offset;
    axes[0].color = Color::Black;
    axes[1].position = offset + Vector2f(0.f, graphHeight);
    axes[1].color = Color::Black;
    axes[2].position = offset + Vector2f(0.f, graphHeight);
    axes[2].color = Color::Black;
    axes[3].position = offset + Vector2f(graphWidth, graphHeight);
    axes[3].color = Color::Black;
    w.draw(axes);

    for (size_t i = 0; i < rabbitsHistory.size(); ++i) {
        float x = i * xStep;
        if (x > graphWidth - pointSize) break;

        float y_rabbit = graphHeight * (1 - rabbitsHistory[i] / max_y);
        float y_fox = graphHeight * (1 - foxesHistory[i] / max_y);

        draw_point(w, {x, y_rabbit - pointSize / 2.f}, Color::Blue, offset, pointSize);
        draw_point(w, {x, y_fox - pointSize / 2.f}, Color::Red, offset, pointSize);
    }
}



void Graphics::start(RenderWindow &window) {
    float turn = 0;

    EntityParams params;

    TypeParams rabbitParams(
        40,   // entityInit
        10,   // foodMin
        20,   // foodMax
        15,   // foodToReproduceLevel
        1,    // foodPerMove
        5,    // foodValue
        40,   // probReproduce
        1,    // minFreeBirth
        {}    // preys
    );

    TypeParams foxParams(
        20,               // entityInit
        20,               // foodMin
        30,               // foodMax
        25,               // foodToReproduceLevel
        -1,               // foodPerMove
        15,               // foodValue
        50,               // probReproduce
        2,                // minFreeBirth
        {Type::rabbit}    // preys
    );

    params.addType(Type::rabbit, rabbitParams);
    params.addType(Type::fox, foxParams);

    Texture texture;
    if (!texture.loadFromFile("../Assets/Start.png")) {
        cerr << "Error: no se pudo cargar la imagen." << endl;
        return;
    }
    Sprite sprite(texture);

    RectangleShape graphEvo({250,200});
    graphEvo.setPosition(Vector2f(10.f, 450.f));
    graphEvo.setFillColor(Color::White);


    FloatRect menuButton({950.f, 420.f}, {120.f, 280.f});
    RectangleShape Simulator(Vector2f(600.f, 600.f));
    Simulator.setPosition(Vector2f(270.f, 270.f));
    Simulator.setFillColor(Color::White);

    const int gridSize = TAILLE_GRID;

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
                rabbitsHistory.clear();
                foxesHistory.clear();
                return;
            }
        }
        window.clear(Color::White);
        window.draw(sprite);
        window.draw(Simulator);
        draw(game.getPopulation(), window, Simulator.getPosition(), 60);
        window.draw(graphEvo);
        graphEvolution(window, game.getPopulation(), turn, graphEvo.getPosition());
        game.next();
        turn++;
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
            sleep(sf::milliseconds(100));
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}
