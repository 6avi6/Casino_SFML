#ifndef BOARDSFORBEDS_H
#define BOARDSFORBEDS_H

#include <SFML/Graphics.hpp>
#include "memory"
#include "vector"
#include "SelectedButton.h"

#include <iostream>


class BoardsForBets :public GraphicalObject
{	

public:
	BoardsForBets(sf::Vector2f postion, sf::Vector2f scale,sf::Font& font);
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	std::vector<std::shared_ptr<SelectedButton>> boardFields;
	void update(sf::Event event);
	float calculateWinnings(int resultNumber) const;
private:
	sf::Vector2f scale;
	sf::Font font;
	void initBoard();

};

#endif // !BOARDSFORBEDS_H

