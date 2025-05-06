#include "TextBox.hpp"

TextBox::TextBox(std::string textLabel, float x, float y, float width, float height, sf::Font& font, unsigned int charSize)
    : text(font), label(font), is_focused(false)
{   
    label.setFont(font);
    label.setCharacterSize(charSize);
    label.setFillColor(sf::Color::Black);
    label.setPosition({x + 10.f, y + (height - charSize) / 2.f});
    label.setString(textLabel);

    box.setSize({width, height});
    box.setPosition({x, y});
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);

    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setFillColor(sf::Color::Black);
    text.setPosition({x + 450.f, y + (height - charSize) / 2.f});
    text.setString("Test");
}

void TextBox::handle_event(const std::optional<Event>& event, const sf::RenderWindow& window) {
    if (event->is<Event::MouseButtonPressed>()) {
        auto mouse_pos = sf::Mouse::getPosition(window);
        if (box.getGlobalBounds().contains({static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y)})) {
            set_focus(true);
        } else {
            set_focus(false);
        }
        std::cout << "MOUSE PRESSED" << std::endl;
    }

    if (is_focused) {
        if (const auto* e = event->getIf<sf::Event::TextEntered>()) {
             if (e->unicode == 8 && !input.empty()) {
                input.pop_back();
            } else if (e->unicode >= 32 && e->unicode < 128) {
                input += static_cast<char>(e->unicode);
            }
            text.setString(input);
        }
    }
}

void TextBox::draw(sf::RenderWindow& window) const {
    window.draw(box);
    window.draw(label);
    window.draw(text);
}

void TextBox::set_label(const std::string& labelText) {
    label.setString(labelText);
}

void TextBox::setText(const std::string& textStr) {
    text.setString(textStr);
}

const std::string& TextBox::get_text() const {
    return input;
}

void TextBox::set_focus(bool focus) {
    is_focused = focus;
    box.setOutlineColor(focus ? sf::Color::Blue : sf::Color::Black);
}
