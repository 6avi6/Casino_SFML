#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "GraphicalObject.h"

class Button : public GraphicalObject {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& text, sf::Font& font);

    void draw(sf::RenderWindow* window) override;
    bool isClicked(const sf::Vector2f& mousePosition) const;

private:
    sf::RectangleShape shape;
    sf::Text buttonText;
};

#endif // BUTTON_H
