#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "GraphicalObject.h"

class Window {
public:
	std::shared_ptr<sf::RenderWindow> window;
	virtual void runWindow()=0;
	virtual void clear()=0;
	virtual void close() = 0;
	virtual void display() = 0;

private:

	std::shared_ptr<GraphicalObject> drawableObjects;



};

#endif // !WINDOW_H

