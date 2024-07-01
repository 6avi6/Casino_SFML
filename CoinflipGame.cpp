#include "CoinflipGame.h"
#include <iostream>

// Constructor to initialize the game
CoinflipGame::CoinflipGame(std::shared_ptr<sf::RenderWindow> window) {
    // Create the window
    this->window = std::move(window);

    // Load font
    this->font = this->readFont("Assets/Fonts/arial.ttf");

    // Create the flip button
    flipButton = std::make_shared<Button>(sf::Vector2f(this->window->getSize().x * 0.5f, this->window->getSize().y * 0.6), sf::Vector2f(200, 50), sf::Color::Green, "Flip Coin", font);

    // Create the exit button in the top right corner
    exitButton = std::make_shared<Button>(sf::Vector2f(this->window->getSize().x - 100 / 2, 50 / 2), sf::Vector2f(100, 50), sf::Color::Red, "Exit", font);

    // Use std::make_shared with appropriate parameters
    int initialValue = 0; // Default value for headsButton
    headsButton = std::make_shared<SelectedButton>(sf::Vector2f((this->window->getSize().x) * 0.6f, this->window->getSize().y * 0.8), sf::Vector2f(100, 50), sf::Color::Cyan, "Heads", font, initialValue);

    int anotherValue = 1; // Another value for tailsButton
    tailsButton = std::make_shared<SelectedButton>(sf::Vector2f((this->window->getSize().x) * 0.4f, this->window->getSize().y * 0.8), sf::Vector2f(100, 50), sf::Color::Magenta, "Tails", font, anotherValue);

    // Initialize game state
    result = "Click the button to flip the coin!";
    this->initCoinEntity();
    this->clear();
    loadBackground("Assets/Pics/Roulette/background.png");
    spinNumber = -1;
}

// Main function to run the game window
void CoinflipGame::runWindow() {
    this->isOpen = true;
    while (window->isOpen() && this->isOpen) {
        handleEvents();
        update();
        render();
    }
}

// Function to clear the window
void CoinflipGame::clear() {
    window->clear(sf::Color::Black);
}

// Function to close the game window
void CoinflipGame::close() {
    window->close();
}

// Function to display the window content
void CoinflipGame::display() {
    window->display();
}

// Function to handle events
void CoinflipGame::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (spinNumber <= 0 && (headsButton->getSelected() || tailsButton->getSelected()) && flipButton->isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                // Randomly determine the result of the coin flip
                spinNumber = rand() % 6 + 1;
                // result = std::to_string(spinNumber); // Used to check rand generator
            }
            else if (spinNumber <= 0 && exitButton->isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                // Close the window if the exit button is clicked
                this->isOpen = false;
            }
            else if (spinNumber <= 0 && headsButton->isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                spinNumber = -1;
                result = "Click the button to flip the coin!";
                headsButton->setSelected(!headsButton->getSelected());
                if (tailsButton->getSelected())
                    tailsButton->setSelected(false);
            }
            else if (spinNumber <= 0 && tailsButton->isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                spinNumber = -1;
                result = "Click the button to flip the coin!";
                tailsButton->setSelected(!tailsButton->getSelected());
                if (headsButton->getSelected())
                    headsButton->setSelected(false);
            }
        }
    }
}

// Function to update the game state
void CoinflipGame::update() {
    this->tossCoin();
}

// Function to render the game objects
void CoinflipGame::render() {
    clear();
    window->draw(this->background);
    flipButton->draw(window);
    exitButton->draw(window);

    // Display the result
    sf::Text resultText;
    resultText.setFont(font);
    resultText.setString(result);
    resultText.setCharacterSize(24);
    resultText.setFillColor(sf::Color::White);
    resultText.setOrigin(resultText.getGlobalBounds().getSize().x * 0.5, resultText.getGlobalBounds().getSize().y * 0.5);
    resultText.setPosition(this->window->getSize().x * 0.5f, this->window->getSize().y * 0.7);

    window->draw(resultText);

    if (show)
        window->draw(this->coinEntity[0]);
    else
        window->draw(this->coinEntity[1]);

    headsButton->draw(window);
    tailsButton->draw(window);

    display();
}

// Function to initialize the coin entity
void CoinflipGame::initCoinEntity() {
    // Loading heads texture
    this->coinTexture[0] = this->readTexture("Assets/Pics/Coin/sample_heads.png");
    this->coinEntity[0].setTexture(coinTexture[0]);
    this->coinEntity[0].setOrigin(this->coinEntity[0].getGlobalBounds().getSize().x * 0.5, this->coinEntity[0].getGlobalBounds().getSize().y * 0.5);
    this->coinEntity[0].setPosition(this->window->getSize().x * 0.5f, this->window->getSize().y * 0.3);
    this->coinEntity[0].scale(0.5, 0.5);

    // Loading tails texture
    this->coinTexture[1] = this->readTexture("Assets/Pics/Coin/sample_tails.png");
    this->coinEntity[1].setTexture(coinTexture[1]);
    this->coinEntity[1].setOrigin(this->coinEntity[1].getGlobalBounds().getSize().x * 0.5, this->coinEntity[1].getGlobalBounds().getSize().y * 0.5);
    this->coinEntity[1].setPosition(this->window->getSize().x * 0.5f, this->window->getSize().y * 0.3);
    this->coinEntity[1].scale(0.5, 0.5); // The y should be negative but coin looks better not upside down ;>

    this->spin = true;
    this->show = true;
    this->spinNumber = 0;
}

// Function to toss the coin
void CoinflipGame::tossCoin() {
    float scalar = 0.07;
    if (spin && spinNumber > 0) {
        if (coinEntity[0].getGlobalBounds().width * 0.1 > coinEntity[0].getGlobalBounds().height) {
            show = false;
            coinEntity[1].scale(1, 1 + scalar);
            if (coinEntity[1].getGlobalBounds().width <= coinEntity[1].getGlobalBounds().height) {
                spin = false;
                spinNumber--;
            }
        }
        else {
            coinEntity[0].scale(1, 1 - scalar);
            coinEntity[1].scale(1, 1 - scalar);
        }
    }
    else if (!spin && spinNumber > 0) {
        if (coinEntity[1].getGlobalBounds().width * 0.1 > coinEntity[1].getGlobalBounds().height) {
            show = true;
            coinEntity[0].scale(1, 1 + scalar);
            if (coinEntity[0].getGlobalBounds().width <= coinEntity[0].getGlobalBounds().height) {
                spin = true;
                spinNumber--;
            }
        }
        else {
            coinEntity[1].scale(1, 1 - scalar);
            coinEntity[0].scale(1, 1 - scalar);
        }
    }

    if (spinNumber == 0) {
        result = "";
        result = result + ((show) ? " Heads " : " Tails ");
        if (show == headsButton->getSelected())
            result = result + "You win";
        else
            result = result + "You lose";
    }
}
