#ifndef COINFLIPGAME_H
#define COINFLIPGAME_H

#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Button.h"
#include <memory>


#include <thread>
#include <chrono>

// Derived class for the Coinflip game
class CoinflipGame : public Window {
public:
    CoinflipGame(std::shared_ptr<sf::RenderWindow> window);

    // Override pure virtual functions from Window
    void runWindow() override;
    void clear() override;
    void close() override;
    void display() override;

private:
    // Method to handle game logic
    void handleEvents();
    void update();
    void render();

    // SFML font and button for the game
    sf::Font font;
    std::shared_ptr<Button> flipButton;
    std::shared_ptr<Button> exitButton;

    // Game state
    std::string result;

    sf::Texture coinTexture[2];
    sf::Sprite coinEntity[2];
    int spinNumber;
    bool spin;
    bool show;
    void initCoinEntity();
    void tossCoin();
};

#endif // COINFLIPGAME_H
