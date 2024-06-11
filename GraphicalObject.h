#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H
#include <SFML/Graphics.hpp>

class GraphicalObject {
public:
	sf::Vector2f position;
	sf::Vector2f size;
	
	virtual void draw(sf::RenderWindow* window) = 0;

};


#endif // !GRAPHICALOBJECT_H
