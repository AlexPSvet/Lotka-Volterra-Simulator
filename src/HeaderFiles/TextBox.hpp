#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

/**
 * @brief A simple text input box using SFML.
 *
 * This class handles user keyboard input, focus detection, and rendering
 * of a basic editable text field.
 */
class TextBox {
public:
    /**
     * @brief Constructs a new TextBox.
     *
     * @param x         X position of the top-left corner.
     * @param y         Y position of the top-left corner.
     * @param width     Width of the text box.
     * @param height    Height of the text box.
     * @param font      Reference to the font used for rendering the text.
     * @param charSize  Font size (default is 24).
     */
    TextBox(
        float x,
        float y,
        float width,
        float height,
        Font& font,
        unsigned int charSize = 24
    );

    /**
     * @brief Handles keyboard and mouse events for text input and focus.
     *
     * @param event  The SFML event (e.g. mouse click, key press).
     * @param window The render window to check for mouse focus.
     */
    void handle_event(const Event& event, const RenderWindow& window);

    /**
     * @brief Draws the text box and current input text on the window.
     *
     * @param window The SFML window to draw on.
     */
    void draw(RenderWindow& window) const;

    /**
     * @brief Returns the current text content entered by the user.
     *
     * @return const reference to the input string.
     */
    const std::string& get_text() const;

private:
    RectangleShape box;   ///< The rectangle representing the input box.
    Text text;            ///< SFML Text object for displaying user input.
    std::string input;    ///< Internal string storing the typed characters.
    bool is_focused;      ///< Whether the text box is currently focused for input.

    /**
     * @brief Sets the focus state of the text box.
     *
     * @param focus True to enable text input, false to disable.
     */
    void set_focus(bool focus);
};

#endif
