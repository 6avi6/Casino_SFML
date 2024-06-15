#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>
#include "GraphicalObject.h"

#include <iostream>
#include <chrono>

class Text :public GraphicalObject{
public:
    Text(sf::Font& font, const std::string& initialString="$");
    void setString(const std::string& newString);
    void setPosition(float x, float y);
    void clicked();
    void update(std::shared_ptr<sf::RenderWindow> window);
    void draw(std::shared_ptr<sf::RenderWindow> window) override;
    bool contains(const sf::Vector2f& point);
    void handleEvent(const sf::Event& event);
    const bool getIsClicked();
    sf::Color colorOfText;
private:
    sf::Vector2f postion;
    bool isClicked;
    std::string string;
    sf::Text text;
    sf::Font font;
    
    bool cursorVisible;
    std::chrono::time_point<std::chrono::steady_clock> lastBlinkTime;
    sf::RectangleShape hitbox; //(hitbox)
    sf::RectangleShape underline; // White text underline
};

#endif // TEXT_H
