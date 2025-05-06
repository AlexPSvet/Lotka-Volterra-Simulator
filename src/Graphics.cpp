#include "HeaderFiles/Graphics.hpp"

Graphics::Graphics() {
    if (!rabbitTexture.loadFromFile("../assets/bugs.png")) {
        std::cerr << "Error: no se pudo cargar la imagen del conejo." << std::endl;
    }
    if (!foxTexture.loadFromFile("../assets/Zorro.png")) {
        std::cerr << "Error: no se pudo cargar la imagen del Zorro." << std::endl;
    }
    if (!gameTexture.loadFromFile("../assets/Start.png")) {
        cerr << "Error: no se pudo cargar la imagen." << endl;
        return;
    }
    if (!menuTexture.loadFromFile("../assets/Life.png")) {
        cerr << "Error: no se pudo cargar la imagen." << endl;
        return;
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
            Sprite zorro(foxTexture);
            float scaleX = cellSize / foxTexture.getSize().x;
            float scaleY = cellSize / foxTexture.getSize().y;
            zorro.setScale({scaleX, scaleY});
            zorro.setPosition({px + offset.x, py + offset.y});
            w.draw(zorro);
        }
    }
}


void Graphics::graphEvolution(RenderWindow &w, Population p, Vector2f offset) {
    const vector<Entity*> entities = p.getEntities();
    float card_rab = 0;
    float card_fox = 0;
    float graphWidth = 250.f;
    float graphHeight = 200.f;
    float xStep = 5.f;
    float pointSize = 3.f;

    SimulatorMenu& simGame = *simulator;
    for (auto entity : entities) {
        if (entity->getType() == Type::rabbit) {
            card_rab++;
        } else {
            card_fox++;
        }
    }
    simGame.rabbitsHistory.push_back(card_rab);
    simGame.foxesHistory.push_back(card_fox);

    float max_y = 1.f;
    for (size_t i = 0; i < simGame.rabbitsHistory.size(); ++i) {
        max_y = std::max(max_y, std::max(simGame.rabbitsHistory[i], simGame.foxesHistory[i]));
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

    for (size_t i = simGame.startIndex; i < simGame.rabbitsHistory.size(); ++i) {
        float x = (i - simGame.startIndex) * xStep;
        if (x > graphWidth - pointSize) {
            simGame.startIndex++;
            break;
        }

        float y_rabbit = graphHeight * (1 - simGame.rabbitsHistory[i] / max_y);
        float y_fox = graphHeight * (1 - simGame.foxesHistory[i] / max_y);

        draw_point(w, {x, y_rabbit - pointSize / 2.f}, Color::Blue, offset, pointSize);
        draw_point(w, {x, y_fox - pointSize / 2.f}, Color::Red, offset, pointSize);
    }
}

void Graphics::drawSimulator(RenderWindow &window) {
    const int gridSize = TAILLE_GRID;

    SimulatorMenu& simGame = *simulator;
    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (simGame.menuButton.contains(mousePos)) {
            std::cout << "Menu presionado 🦊🚀" << std::endl;
            game->stop();
            simGame.rabbitsHistory.clear();
            simGame.foxesHistory.clear();
            state = ScreenState::menu;
            return;
        }
    }

    window.draw(Sprite(gameTexture));
    window.draw(simGame.background);
    draw(game->getPopulation(), window, simGame.background.getPosition(), 600 / gridSize);
    window.draw(simGame.graphEvo);
    graphEvolution(window, game->getPopulation(), simGame.graphEvo.getPosition());
    game->next();
}

void Graphics::drawMenu(RenderWindow& window) {
    Menu& menuSimulator = *menu;
    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (menuSimulator.startButton.contains(mousePos)) {
            std::cout << "Start presionado 🦊🚀" << std::endl;
            game->start();
            state = ScreenState::simulation;
        }
        if (menuSimulator.paramsButton.contains(mousePos)) {
            std::cout << "Params presionado 🐰🛠️" << std::endl;
            state = ScreenState::params;
        }
        // sleep(sf::milliseconds(100));
    }
    window.draw(Sprite(menuTexture));
}

void Graphics::start() {
    RenderWindow window(VideoMode({WINDOW_SIZE,WINDOW_SIZE}), "Simulation");
    window.setFramerateLimit(5);

    // -- Set local graphics variables.

    // MENU
    menu = new Menu();
    menu->startButton = FloatRect({280.f, 890.f}, {240.f, 80.f});
    menu->paramsButton = FloatRect({620.f, 890.f}, {220.f, 80.f});

    // SIMULATOR
    simulator = new SimulatorMenu();
    simulator->graphEvo = RectangleShape({250,200});
    simulator->graphEvo.setPosition(Vector2f(10.f, 450.f));
    simulator->graphEvo.setFillColor(Color::White);
    simulator->menuButton = FloatRect({950.f, 420.f}, {120.f, 280.f});
    simulator->background = RectangleShape(Vector2f(600.f, 600.f));
    simulator->background.setPosition(Vector2f(270.f, 270.f));
    simulator->background.setFillColor(Color::White);

    // -- Set local game simulation.
    EntityParams params;

    TypeParams rabbitParams(
        20,   // entityInit
        5,   // foodMin
        20,   // foodMax
        15,   // foodToReproduceLevel
        1,    // foodPerMove
        6,    // foodValue
        45,   // probReproduce
        3,    // minFreeBirth
        {}    // preys
    );

    TypeParams foxParams(
        20,               // entityInit
        5,                // foodMin
        20,               // foodMax
        10,               // foodToReproduceLevel
        -1,               // foodPerMove
        15,               // foodValue
        80,               // probReproduce
        4,                // minFreeBirth
        {Type::rabbit}    // preys
    );

    params.addType(Type::rabbit, rabbitParams);
    params.addType(Type::fox, foxParams);

    game = new Game(params, TAILLE_GRID);

    // -- Window logic.
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                stop();
                window.close();
                return;
            }
        }

        window.clear(Color::White);
        switch (state) {
            case ScreenState::menu:
                drawMenu(window);
                break;
            case ScreenState::params:
                
                break;
            case ScreenState::simulation:
                drawSimulator(window);
        }
        window.display();
    }

    stop();
}

void Graphics::stop() {
    game->stop();
    delete menu;
    delete simulator;
    delete game;
}