#ifndef ROULETTEGAME_H
#define ROULETTEGAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Window.h"
#include "Button.h"
#include "Text.h"

#include <vector>
#include <cmath>
class RouletteGame : public Window {
public:
    RouletteGame(std::shared_ptr<sf::RenderWindow> window);

    // Override pure virtual functions from Window
    void runWindow() override;
    void clear() override;
    void close() override;
    void display() override;
    bool isOpen;

private:
    void handleEvents();
    void update();
    void render();
    void spinWheel();
    int calculateResult();

    sf::Font font;
    sf::Text resultText;
    std::shared_ptr<Button> spinButton;
    std::shared_ptr<Button> exitButton;
    sf::ConvexShape arrow;

    sf::Texture wheelTexture;
    sf::Sprite wheelSprite;
    float wheelAngle;
    bool isSpinning;
    float spinSpeed;

    // Game logic variables
    std::string result;

    std::shared_ptr<Text> bid;

};

#endif // ROULETTEGAME_H
