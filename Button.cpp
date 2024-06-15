#include "Button.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& text, sf::Font& font) {
    this->position = position;
    this->size = size;

    // Set the size and color of the button shape
    shape.setSize(size);
    shape.setFillColor(color);

    // Set the origin point to the center of the shape
    shape.setOrigin(size.x * 0.5f, size.y * 0.5f);

    // Set the position of the button shape
    shape.setPosition(position);

    // Set the button text properties
    buttonText.setString(text);
    buttonText.setFont(font);
    buttonText.setCharacterSize(24); // Adjust if needed
    buttonText.setFillColor(sf::Color::White);

    // Calculate the offset to center the text within the button
    float textOffsetX = buttonText.getGlobalBounds().width * 0.5f;
    float textOffsetY = buttonText.getGlobalBounds().height * 0.75f; // Adjust the Y-axis offset

    // Set the origin point to the center of the text
    buttonText.setOrigin(textOffsetX, textOffsetY);

    // Set the position of the button text
    buttonText.setPosition(position);
}

Button::Button()
{
}

void Button::draw(std::shared_ptr<sf::RenderWindow> window) {
    // Draw the button shape
    window->draw(shape);

    // Draw the button text
    window->draw(buttonText);
}

bool Button::isClicked(const sf::Vector2f& mousePosition) const {
    // Check if the mouse position is within the button's bounds
    return shape.getGlobalBounds().contains(mousePosition);
}
