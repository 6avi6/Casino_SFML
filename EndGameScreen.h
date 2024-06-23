#ifndef ENDGAMESCREEN_H
#define ENDGAMESCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <vector>
#include "Window.h"

class EndGameScreen : public Window {
public:
    EndGameScreen(std::shared_ptr<sf::RenderWindow> window, float playerScore);

    void runWindow() override;
    void clear() override;
    void close() override;
    void display() override;

private:
    float playerScore;
    sf::Text scoreText;
    sf::Font font;
    bool newHighScore;
    std::vector<std::pair<float, std::string>> scores;

    void displayScore();
    void displayScoreText();
    void checkHighScore();
    void promptForName();
};



#endif // ENDGAMESCREEN_H
