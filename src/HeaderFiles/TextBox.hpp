#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class TextBox {
    public:
        TextBox(
            float x, 
            float y, 
            float width, 
            float height, 
            Font& font, 
            unsigned int charSize = 24
        );

        void handle_event(const Event& event, const RenderWindow& window);
        void draw(RenderWindow& window) const;
        const std::string& get_text() const;
    private:
        RectangleShape box;
        Text text;
        std::string input;
        bool is_focused;

        void set_focus(bool focus);
};

#endif