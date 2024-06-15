#include "SelectedButton.h"

SelectedButton::SelectedButton(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& text, sf::Font& font, int& value)
    : isSelected(false), value(value)
{
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

void SelectedButton::draw(std::shared_ptr<sf::RenderWindow> window) {
    update();
    // Draw the button shape
    window->draw(shape);

    // Draw the button text
    window->draw(buttonText);
}

void SelectedButton::update()
{
    sf::Color currentColor = shape.getFillColor();

    if (isSelected) {
        sf::Color newColor(currentColor.r, currentColor.g, currentColor.b, 100); // Ustaw przezroczystoœæ na 100 (zak³adam, ¿e jest to wartoœæ od 0 do 255)

        shape.setFillColor(newColor);
    }
    else {
        sf::Color newColor(currentColor.r, currentColor.g, currentColor.b, 255); // Ustaw przezroczystoœæ na 100 (zak³adam, ¿e jest to wartoœæ od 0 do 255)
        shape.setFillColor(newColor);


    }
}

bool SelectedButton::isClicked(const sf::Vector2f& mousePosition) const {
    // Check if the mouse position is within the button's bounds
    return shape.getGlobalBounds().contains(mousePosition);
}

const bool SelectedButton::getSelected()
{
    return isSelected;
}

void SelectedButton::setSelected(bool value)
{
    isSelected = value;
}
