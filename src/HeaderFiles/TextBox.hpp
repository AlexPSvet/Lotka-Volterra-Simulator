#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;

class TextBox {
    public:
        TextBox(
            std::string textLabel,
            float x, 
            float y, 
            float width, 
            float height, 
            Font& font, 
            unsigned int charSize = 24
        );

        void handle_event(const std::optional<Event>& event, const RenderWindow& window);
        void draw(RenderWindow& window) const;
        const std::string& get_text() const;
        void set_label(const std::string& labelText);
        void setText(const std::string& textStr);
    private:
        RectangleShape box;
        Text text, label;
        std::string input;
        bool is_focused;

        void set_focus(bool focus);
};

#endif