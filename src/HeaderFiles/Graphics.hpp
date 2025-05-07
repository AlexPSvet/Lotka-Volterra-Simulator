#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "TextBox.hpp"

using namespace sf;

// Window size constant (square window)
const int WINDOW_SIZE = 1120;

// Enum to represent which screen is currently active
enum class ScreenState { menu, params, simulation };

// Represents a clickable UI button with text
struct Button {
public:
    /*
     * Constructor to create a button with custom text, colors, position, and size.
     * @param textStr: Text to display
     * @param textColor: Color of the text
     * @param fillColor: Background color of the button
     * @param outlineColor: Outline color of the button
     * @param x, y: Position on screen
     * @param width, height: Dimensions of the button
     * @param font: Font to use for the text
     */
    Button(
        std::string textStr,
        Color textColor,
        Color fillColor,
        Color outlineColor,
        float x, float y,
        float width, float height,
        const sf::Font& font
    );

    // Draws the button onto the window
    void draw(sf::RenderWindow& window) const;

    sf::RectangleShape box;  // The button shape
    sf::Text text;           // The button label
};

// Contains bounds for buttons in the main menu
struct Menu {
    FloatRect startButton;
    FloatRect paramsButton;
};

// UI screen to configure simulation parameters
struct ParamsMenu {
public:
    // Constructor
    ParamsMenu(Game*& game);

    /*
     * Draws the parameter menu.
     * @return true if parameter values are valid
     */
    bool draw(RenderWindow& window);

    // Handles button interactions and inputs
    void handleButtons(RenderWindow& window, const std::optional<Event>& event);

    // Updates text based on current parameters
    void setParamsText();

    // Saves the parameters into the game object
    void saveParams();

private:
    Game*& game;                 // Reference to the game logic
    Font font;                   // Font used for text

    vector<Button> buttons;      // List of action buttons
    std::vector<TextBox> textBoxs; // Editable text fields

    int typeParamsId = 0;        // Tracks which parameter group is being edited
};

// Contains state and graphics for the simulation screen
struct SimulatorMenu {
    vector<float> rabbitsHistory = {};  // Historical rabbit population
    vector<float> foxesHistory = {};    // Historical fox population
    int startIndex = 0;                 // For graph scrolling or cropping

    RectangleShape graphEvo;           // Graph area for population evolution
    FloatRect menuButton;              // Clickable area to return to menu
    RectangleShape background;         // Background rectangle for the screen
};

// Handles window rendering, UI state management, and event handling
class Graphics {
public:
    Graphics();  // Constructor
    ~Graphics(); // Destructor

    void start(); // Starts the rendering loop
    void stop();  // Stops rendering and exits

private:
    // Draws a small square point on the window
    void draw_point(RenderWindow &w, Vector2f pos, Color color, Vector2f offset, float cellSize);

    // Draws all entities in the population onto the grid
    void draw(Population p, RenderWindow &w, Vector2f offset, float cellSize);

    // Renders the population evolution graph over time
    void graphEvolution(RenderWindow &w, Population p, Vector2f offset);

    // Draws the simulation screen including the graph and entities
    void drawSimulator(RenderWindow &window);

    // Draws the main menu screen
    void drawMenu(RenderWindow& window);

    // Handles input events for all screens
    bool handleEvents(RenderWindow& window);

    Menu menu;                 // Main menu UI
    SimulatorMenu simulator;  // Simulation UI
    ParamsMenu paramsMenu;    // Parameter configuration UI

    // Textures used to display animals and backgrounds
    Texture rabbitTexture;
    Texture foxTexture;
    Texture gameTexture;
    Texture menuTexture;
    Texture paramsTexture;

    Game* game;                // Pointer to the game instance
    ScreenState state = ScreenState::menu; // Current screen state
};

#endif
