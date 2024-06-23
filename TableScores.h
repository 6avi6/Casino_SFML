#ifndef TABLESCORES_H
#define TABLESCORES_H

#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "fstream"
#include <queue>
#include <iostream>
#include <string>
class TableScores:private Window {
public:
	TableScores(std::shared_ptr<sf::RenderWindow> window);
	void runWindow() override;
	virtual void clear() override {};
	virtual void close()override {};
	virtual void display() override {};
private:
	sf::Text titleOfWindow;
	sf::Font font;
	void loadPlayerScoresFromFile(const std::string& filename);
	sf::Text scores[10];

	void initScores();

	void displayTableScores();
	std::shared_ptr<Button> exitButton;
	std::shared_ptr<sf::RenderWindow> window;

};


#endif // TABLESCORES_H
