#ifndef ROULETTEFIELD_H
#define ROULETTEFIELD_H


#include <SFML/Graphics.hpp>
#include "GraphicalObject.h"

class RouletteField :public GraphicalObject{
public:
	int id;
	sf::Color color;

	sf::Vector2f postion;
	sf::Vector2f originPoint;
	float angle;
	sf::Text text;
	sf::Font font;




};


#endif // !ROULETTEFIELD_H
