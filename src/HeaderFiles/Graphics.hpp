#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "TextBox.hpp"

using namespace sf;

const int WINDOW_SIZE = 1120;

/// Enum representing the current screen of the application.
enum class ScreenState { menu, params, simulation };

/**
 * @brief Stores interactive regions for the main menu.
 */
struct Menu {
    FloatRect startButton;   ///< Rectangle area for the "Start" button.
    FloatRect paramsButton;  ///< Rectangle area for the "Parameters" button.
};

/**
 * @brief Stores GUI elements and data for the simulation screen.
 */
struct SimulatorMenu {
    vector<float> rabbitsHistory = {};  ///< Historical data of rabbit population.
    vector<float> foxesHistory = {};    ///< Historical data of fox population.
    int startIndex = 0;                 ///< Starting index for displaying the graph.

    RectangleShape graphEvo;           ///< Shape used to draw the evolution graph.
    FloatRect menuButton;              ///< Rectangle area for the "Menu" button.
    RectangleShape background;         ///< Background shape for the simulation screen.
};

/**
 * @brief Manages all graphical rendering and screen transitions using SFML.
 */
class Graphics {
public:
    /// Constructor. Initializes the graphic system and assets.
    Graphics();

    /// Starts the main graphical loop.
    void start();

    /// Stops the graphical loop.
    void stop();

private:
    /**
     * @brief Draws a single point (entity) on the grid.
     * @param w Window where to draw.
     * @param pos Position of the point.
     * @param color Color of the point.
     * @param offset Offset from the top-left corner.
     * @param cellSize Size of a cell in the grid.
     */
    void draw_point(RenderWindow& w, Vector2f pos, Color color, Vector2f offset, float cellSize);

    /**
     * @brief Draws the current population on the window.
     * @param p Population to render.
     * @param w Window where to draw.
     * @param offset Offset from the top-left corner.
     * @param cellSize Size of a cell in the grid.
     */
    void draw(Population p, RenderWindow& w, Vector2f offset, float cellSize);

    /**
     * @brief Draws the graph showing population evolution over time.
     * @param w Window where to draw.
     * @param p Population used to retrieve historical data.
     * @param offset Offset position for the graph.
     */
    void graphEvolution(RenderWindow& w, Population p, Vector2f offset);

    /// Draws the simulation screen and its UI.
    void drawSimulator(RenderWindow& window);

    /// Draws the main menu screen and its UI.
    void drawMenu(RenderWindow& window);

    Menu* menu;                 ///< UI elements for the main menu.
    SimulatorMenu* simulator;  ///< UI elements and data for the simulation view.

    Texture rabbitTexture;     ///< Texture used for displaying rabbits.
    Texture foxTexture;        ///< Texture used for displaying foxes.
    Texture gameTexture;       ///< Background or decorative texture for the simulation.
    Texture menuTexture;       ///< Background or decorative texture for the menu.

    Game* game;                ///< Pointer to the simulation logic.
    ScreenState state = ScreenState::menu; ///< Current screen being displayed.
};

#endif
