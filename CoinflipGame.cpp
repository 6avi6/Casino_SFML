#include "CoinflipGame.h"
#include <iostream>

// Constructor to initialize the game
CoinflipGame::CoinflipGame(std::shared_ptr<sf::RenderWindow> window) {
    // Create the window
    this->window = std::move(window);

    // Load font
    this->font = this->readFont("Assets/Fonts/arial.ttf");

    // Create the flip button
    flipButton = std::make_shared<Button>(sf::Vector2f(this->window->getSize().x*0.5f , this->window->getSize().y * 0.6), sf::Vector2f(200, 50), sf::Color::Green, "Flip Coin", font);

    // Create the exit button in the top right corner
    exitButton = std::make_shared<Button>(sf::Vector2f(this->window->getSize().x -100/2,  50/2), sf::Vector2f(100, 50), sf::Color::Red, "Exit", font);

    // U¿ycie std::make_shared z odpowiednimi parametrami
    int initialValue = 0; // Domyœlna wartoœæ dla headsButton
    headsButton = std::make_shared<SelectedButton>(sf::Vector2f((this->window->getSize().x) * 0.6f, this->window->getSize().y * 0.8), sf::Vector2f(100, 50), sf::Color::Cyan , "Heads", font, initialValue);

    int anotherValue = 1; // Inna wartoœæ dla tailsButton
    tailsButton = std::make_shared<SelectedButton>(sf::Vector2f((this->window->getSize().x) * 0.4f, this->window->getSize().y * 0.8), sf::Vector2f(100, 50), sf::Color::Magenta, "Tails", font, anotherValue);

    // Initialize game state
    result = "Click the button to flip the coin!";
    this->initCoinEntity();
    this->clear();
    spinNumber = -1;
}

void CoinflipGame::runWindow() {
    // Main game loop
    this->isOpen = true;
    while (window->isOpen() && this->isOpen) {
        handleEvents();
        update();
        render();
    }
}

void CoinflipGame::clear() {
    window->clear(sf::Color::Black);
}

void CoinflipGame::close() {
    window->close();
}

void CoinflipGame::display() {
    window->display();
}

void CoinflipGame::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (spinNumber <= 0 && (headsButton->getSelected() || tailsButton->getSelected()) && flipButton->isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                // Randomly determine the result of the coin flip
                spinNumber=rand() % 6 +1;
                //result = std::to_string(spinNumber);Used to check rand generator

            }
            else if (spinNumber<=0 && exitButton->isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
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

void CoinflipGame::update() {
    this->tossCoin();
}

void CoinflipGame::render() {
    clear();

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

void CoinflipGame::initCoinEntity()
{
    //loading heads
    this->coinTexture[0] = this->readTexture("Assets/Pics/Coin/sample_heads.png");
    this->coinEntity[0].setTexture(coinTexture[0]);
    this->coinEntity[0].setOrigin(this->coinEntity[0].getGlobalBounds().getSize().x * 0.5, this->coinEntity[0].getGlobalBounds().getSize().y * 0.5);
    this->coinEntity[0].setPosition(this->window->getSize().x * 0.5f, this->window->getSize().y * 0.3);
    this->coinEntity[0].scale(0.5, 0.5);
    //loading tails
    this->coinTexture[1] = this->readTexture("Assets/Pics/Coin/sample_tails.png");
    this->coinEntity[1].setTexture(coinTexture[1]);
    this->coinEntity[1].setOrigin(this->coinEntity[1].getGlobalBounds().getSize().x * 0.5, this->coinEntity[1].getGlobalBounds().getSize().y * 0.5);
    this->coinEntity[1].setPosition(this->window->getSize().x * 0.5f, this->window->getSize().y * 0.3);
    this->coinEntity[1].scale(0.5, 0.5);//the y should be negative but coin look better not upside down ;>
    this->spin = true;
    this->show = true;
    this->spinNumber = 0;
}

void CoinflipGame::tossCoin()
{   
    float scalar = 0.07;
    if (spin && spinNumber >0) {
        if (coinEntity[0].getGlobalBounds().width * 0.1 > coinEntity[0].getGlobalBounds().height) {
            show = false;
            coinEntity[1].scale(1, 1+scalar);
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
    else if (!spin && spinNumber > 0){
        if (coinEntity[1].getGlobalBounds().width * 0.1 > coinEntity[1].getGlobalBounds().height) {
            show = true;
            coinEntity[0].scale(1, 1 + scalar);
            if (coinEntity[0].getGlobalBounds().width <= coinEntity[0].getGlobalBounds().height) {
                spin = true;
                spinNumber--;
            }
        }
        else {
            coinEntity[1].scale(1,1 - scalar);
            coinEntity[0].scale(1,1 - scalar);
        }
    }

    if (spinNumber == 0) {
        result="";
        result = result + ((show) ? " Heads " : " Tails ");
        if (show == headsButton->getSelected())
            result = result + "You win";
        else
            result = result + "You lose";
    }
   
    


}
