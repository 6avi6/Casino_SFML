#ifndef ROULETTEGAME_H
#define ROULETTEGAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Window.h"
#include "Button.h"
#include "Text.h"
#include "BoardsForBets.h"
#include "EndGameScreen.h"

#include <ranges>
#include <ctime>
#include <cstdlib>
#include <random>
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
    float generateSpinSpeed();
    int calculateResult();
    // Metoda do obliczania i wyœwietlania wyniku
    void calculateAndDisplayResult(int resultNumber);

    sf::Font font;
    sf::Text resultText;
    sf::Text cashBalance;
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

    std::shared_ptr<BoardsForBets> board;

    double playerTopScore;
    double playerCredits;
    sf::Text textPlayerCredits;
};

#endif // ROULETTEGAME_H
