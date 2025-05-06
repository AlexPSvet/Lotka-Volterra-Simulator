#include "HeaderFiles/Graphics.hpp"

// BUTTON

Button::Button(
    std::string textStr, 
    Color textColor, 
    Color fillColor, 
    Color outlineColor,
    float x, float y,
    float width, float height, 
    const sf::Font& font) : text(font)
{
    text.setFont(font);
    text.setFillColor(textColor);

    box = RectangleShape({width, height});
    box.setPosition({x, y});
    box.setFillColor(fillColor);
    box.setOutlineColor(outlineColor);
    box.setOutlineThickness(2.f);

    text.setFont(font);
    text.setString(textStr);
    int amountChar = textStr.size();
    float charSizeWidth = width / amountChar;
    text.setCharacterSize(charSizeWidth > height ? height : charSizeWidth);
    float positionX = x + ( width - text.getCharacterSize() * amountChar ) / 2;
    float positionY = y + ( height - text.getCharacterSize() ) / 2;
    text.setPosition({positionX, positionY});
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(box);
    window.draw(text);
}

// PARAMS MENU

ParamsMenu::ParamsMenu(Game*& game) : game(game) {
    if (!font.openFromFile("../fonts/tannimbus.otf")) {
        std::cerr << "Error while loading text font.";
    }

    float midScreen = WINDOW_SIZE / 2;

    std::vector<std::string> strings = {
            "Entity init",
            "Food min",
            "Food max",
            "Food to reproduce",
            "Food per move",
            "Food value",
            "Probability to reproduce",
            "Min free cases"
        };
    for (int i = 0; i < strings.size(); i++) {
        TextBox text(strings[i], midScreen - 250, 200 + 50 * i, 400, 40, font);
        textBoxs.push_back(text);
    }

    Color outline(80, 80, 80);
    Button menuButton("MENU", Color::Green, Color::Black, outline, midScreen, WINDOW_SIZE - 400, 100, 100, font);
    Button rabbitButton("RABBIT", Color::White, Color::Black, outline, midScreen - 100, 50, 150, 60, font);
    Button foxButton("FOX", Color::White, Color::Black, outline,  midScreen + 100, 50, 150, 60, font);
    buttons.push_back(menuButton);
    buttons.push_back(rabbitButton);
    buttons.push_back(foxButton);
}

bool ParamsMenu::draw(RenderWindow& window) {
    for (Button& button : buttons) {
        button.draw(window);
    }

    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (buttons[0].box.getGlobalBounds().contains(mousePos)) {
            saveParams();
            return true;
        } else if (buttons[1].box.getGlobalBounds().contains(mousePos)) {
            typeParamsId = 0;
            saveParams();
            setParamsText();
        } else if (buttons[2].box.getGlobalBounds().contains(mousePos)) {
            typeParamsId = 1;
            saveParams();
            setParamsText();
        }
    }

    for (int i = 0; i < textBoxs.size(); i++) {
        textBoxs[i].draw(window);
    }
    return false;
}

void ParamsMenu::handleButtons(RenderWindow& window, const std::optional<Event>& event) {
    for (TextBox& textBox : textBoxs) {
        textBox.handle_event(event, window);
    }
}

void ParamsMenu::setParamsText() {
    EntityParams& params = game->getPopulation().getParams();
    Type type = ALL_TYPES[typeParamsId];
    TypeParams& typeParams = params.getTypeParams(type);

    textBoxs[0].setText(std::to_string(typeParams.entityInit));
    textBoxs[1].setText(std::to_string(typeParams.foodMin));
    textBoxs[2].setText(std::to_string(typeParams.foodMax));
    textBoxs[3].setText(std::to_string(typeParams.foodToReproduceLevel));
    textBoxs[4].setText(std::to_string(typeParams.foodPerMove));
    textBoxs[5].setText(std::to_string(typeParams.foodValue));
    textBoxs[6].setText(std::to_string(typeParams.probReproduce));
    textBoxs[7].setText(std::to_string(typeParams.minFreeBirth));
}

void ParamsMenu::saveParams() {
    EntityParams& params = game->getPopulation().getParams();
    Type type = ALL_TYPES[typeParamsId];
    TypeParams& typeParams = params.getTypeParams(type);

    typeParams.entityInit = std::stoi(textBoxs[0].getText());
    typeParams.foodMin = std::stoi(textBoxs[1].getText());
    typeParams.foodMax = std::stoi(textBoxs[2].getText());
    typeParams.foodToReproduceLevel = std::stoi(textBoxs[3].getText());
    typeParams.foodPerMove = std::stoi(textBoxs[4].getText());
    typeParams.foodValue = std::stoi(textBoxs[5].getText());
    typeParams.probReproduce = std::stoi(textBoxs[6].getText());
    typeParams.minFreeBirth = std::stoi(textBoxs[7].getText());
}

// GRAPHICS

Graphics::Graphics() : paramsMenu(game) {
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

Graphics::~Graphics() {
    delete game;
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

    for (auto entity : entities) {
        if (entity->getType() == Type::rabbit) {
            card_rab++;
        } else {
            card_fox++;
        }
    }
    simulator.rabbitsHistory.push_back(card_rab);
    simulator.foxesHistory.push_back(card_fox);

    float max_y = 1.f;
    for (size_t i = 0; i < simulator.rabbitsHistory.size(); ++i) {
        max_y = std::max(max_y, std::max(simulator.rabbitsHistory[i], simulator.foxesHistory[i]));
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

    size_t pointCount = simulator.rabbitsHistory.size();
    float xStepProp = graphWidth / std::max(1.f, static_cast<float>(pointCount - 1));

    for (size_t i = simulator.startIndex; i < simulator.rabbitsHistory.size(); ++i) {
        float x = (i - simulator.startIndex) * xStep;
        if (x > graphWidth - pointSize) {
            x = i*xStepProp;
            break;
        }

        float y_rabbit = graphHeight * (1 - simulator.rabbitsHistory[i] / max_y);
        float y_fox = graphHeight * (1 - simulator.foxesHistory[i] / max_y);

        draw_point(w, {x, y_rabbit - pointSize / 2.f}, Color::Blue, offset, pointSize);
        draw_point(w, {x, y_fox - pointSize / 2.f}, Color::Red, offset, pointSize);
    }
}

void Graphics::drawSimulator(RenderWindow &window) {
    const int gridSize = TAILLE_GRID;

    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (simulator.menuButton.contains(mousePos)) {
            std::cout << "Menu presionado 🦊🚀" << std::endl;
            game->stop();
            simulator.startIndex = 0;
            simulator.rabbitsHistory.clear();
            simulator.foxesHistory.clear();
            state = ScreenState::menu;
            return;
        }
    }

    window.draw(Sprite(gameTexture));
    window.draw(simulator.background);
    draw(game->getPopulation(), window, simulator.background.getPosition(), 600 / gridSize);
    window.draw(simulator.graphEvo);
    graphEvolution(window, game->getPopulation(), simulator.graphEvo.getPosition());
    game->next();
}

void Graphics::drawMenu(RenderWindow& window) {
    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (menu.startButton.contains(mousePos)) {
            std::cout << "Start presionado 🦊🚀" << std::endl;
            game->start();
            state = ScreenState::simulation;
        }
        if (menu.paramsButton.contains(mousePos)) {
            std::cout << "Params presionado 🐰🛠️" << std::endl;
            paramsMenu.setParamsText();
            state = ScreenState::params;
        }
        // sleep(sf::milliseconds(100));
    }
    window.draw(Sprite(menuTexture));
}

bool Graphics::handleEvents(RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            return true;
        }

        switch (state) {
            case ScreenState::params:
                paramsMenu.handleButtons(window, event);
                break;
            default:
                break;
        }
    }
    return false;
}

void Graphics::start() {
    RenderWindow window(VideoMode({WINDOW_SIZE,WINDOW_SIZE}), "Simulation");
    window.setFramerateLimit(5);

    // -- Set local graphics variables.

    // MENU
    menu.startButton = FloatRect({280.f, 890.f}, {240.f, 80.f});
    menu.paramsButton = FloatRect({620.f, 890.f}, {220.f, 80.f});

    // SIMULATOR
    simulator.graphEvo = RectangleShape({250,200});
    simulator.graphEvo.setPosition(Vector2f(10.f, 450.f));
    simulator.graphEvo.setFillColor(Color::White);
    simulator.menuButton = FloatRect({950.f, 420.f}, {120.f, 280.f});
    simulator.background = RectangleShape(Vector2f(600.f, 600.f));
    simulator.background.setPosition(Vector2f(270.f, 270.f));
    simulator.background.setFillColor(Color::White);

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
        if (handleEvents(window)) {
            break;
        }

        window.clear(Color::White);
        switch (state) {
            case ScreenState::menu:
                drawMenu(window);
                break;
            case ScreenState::params:
                if (paramsMenu.draw(window)) {
                    state = ScreenState::menu;
                }
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
}