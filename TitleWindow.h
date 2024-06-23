#ifndef TITLEWINDOW_H
#define TITLEWINDOW_H

#include "Window.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.h"

#include "CoinflipGame.h"
#include "RouletteGame.h"
#include "TableScores.h"

// TitleWindow class inheriting privately from the Window class
class TitleWindow : private Window {
public:
    // Constructor that initializes the window
    TitleWindow(std::shared_ptr<sf::RenderWindow> window);

    // Overridden methods from the Window class
    void runWindow() override;
    void clear() override;
    void close() override;
    void display() override;

private:
    // Vector to store drawable graphical objects
    std::vector<std::shared_ptr<GraphicalObject>> drawableObjects;

    // Buttons in the window
    std::shared_ptr<Button> rouletteButton;
    std::shared_ptr<Button> coinflipButton;
    std::shared_ptr<Button> scoresButton;
    std::shared_ptr<Button> exitButton;

    // Background texture and sprite
    sf::Texture backgroundTexture;
    sf::Sprite background;

    // Title text and font
    sf::Text titleText;
    sf::Font font;
};

#endif // TITLEWINDOW_H
