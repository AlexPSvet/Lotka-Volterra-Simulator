#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "TextBox.hpp"

using namespace sf;

const int WINDOW_SIZE = 1120;

enum class ScreenState {menu, params, simulation};

class Button {
    public:
        Button(
            std::string textStr, 
            Color textColor, 
            Color fillColor, 
            Color outlineColor,
            float x, float y,
            float width, float height, 
            const sf::Font& font
        );

        void draw(sf::RenderWindow& window) const;
    private:
        sf::RectangleShape box;
        sf::Text text;
};

struct Menu {
    FloatRect startButton;
    FloatRect paramsButton;
};

struct ParamsMenu {
    public:
        ParamsMenu();

        void draw(RenderWindow& window);
        void handleButtons(RenderWindow& window, const std::optional<Event>& event);
    private:
        Font font;

        vector<Button> buttons;
        std::vector<TextBox> textBoxs;

        int typeParamsId = 0;
};

struct SimulatorMenu {
    vector<float> rabbitsHistory = {};
    vector<float> foxesHistory = {};
    int startIndex = 0;

    RectangleShape graphEvo;
    FloatRect menuButton;
    RectangleShape background;
};

class Graphics {
    public:
        Graphics();

        void start();
        void stop();
    private:
        void draw_point(RenderWindow &w, Vector2f pos, Color color, Vector2f offset, float cellSize);
        void draw(Population p, RenderWindow &w, Vector2f offset, float cellSize);
        void graphEvolution(RenderWindow &w, Population p, Vector2f offset);
        
        void drawSimulator(RenderWindow &window);
        void drawMenu(RenderWindow& window);

        bool handleEvents(RenderWindow& window);

        Menu menu;
        SimulatorMenu simulator;
        ParamsMenu paramsMenu;

        Texture rabbitTexture;
        Texture foxTexture;
        Texture gameTexture;
        Texture menuTexture;

        Game* game;
        ScreenState state = ScreenState::menu;
};

#endif