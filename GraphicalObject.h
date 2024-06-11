#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include <SFML/Graphics.hpp>
#include <memory>

// Abstract base class representing a graphical object
class GraphicalObject {
public:
    sf::Vector2f position; // Position of the object
    sf::Vector2f size; // Size of the object

    // Pure virtual function to draw the object on a SFML render window
    virtual void draw(std::shared_ptr<sf::RenderWindow> window) = 0;
};

#endif // !GRAPHICALOBJECT_H
