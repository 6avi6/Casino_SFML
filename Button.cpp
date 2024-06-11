#include "Button.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& text, sf::Font& font) {
    //this->position = position;
    this->size = size;

    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(color);

    buttonText.setString(text);
    buttonText.setFont(font);
    buttonText.setCharacterSize(24); // Adjust as needed
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(
        position.x + (size.x - buttonText.getGlobalBounds().width) / 2,
        position.y + (size.y - buttonText.getGlobalBounds().height) / 2
    );
}

void Button::draw(sf::RenderWindow* window) {
    window->draw(shape);
    window->draw(buttonText);
}

bool Button::isClicked(const sf::Vector2f& mousePosition) const {
    return shape.getGlobalBounds().contains(mousePosition);
}
