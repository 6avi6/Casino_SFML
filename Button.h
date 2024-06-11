#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "GraphicalObject.h"

class Button : public GraphicalObject {
public:
    // Constructor
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& text, sf::Font& font);

    // Draw the button on the window
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    // Check if the button is clicked
    bool isClicked(const sf::Vector2f& mousePosition) const;

private:
    sf::RectangleShape shape;  // Shape of the button
    sf::Text buttonText;       // Text on the button
};

#endif // BUTTON_H
