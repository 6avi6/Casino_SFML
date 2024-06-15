#include "RouletteGame.h"
#include <iostream>

// Constructor to initialize the game
RouletteGame::RouletteGame(std::shared_ptr<sf::RenderWindow> window) : isSpinning(false), wheelAngle(0.f), spinSpeed(0.0f) {
    this->window = std::move(window);

    // Load the font
    font = readFont("Assets/Fonts/arial.ttf");

    // Initialize result text
    resultText.setFont(font);
    resultText.setCharacterSize(24);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(350, 50);
    resultText.setString("Click Spin to Start");

    // Create buttons
    spinButton = std::make_shared<Button>(sf::Vector2f(400, 300), sf::Vector2f(200, 50), sf::Color::Green, "Spin", font);
    exitButton = std::make_shared<Button>(sf::Vector2f(750, 25), sf::Vector2f(100, 50), sf::Color::Red, "Exit", font);

    // Load the roulette wheel texture
    wheelTexture = readTexture("Assets/Pics/Roulette/roulette_wheel.png");
    wheelSprite.setTexture(wheelTexture);
    wheelSprite.scale(0.5, 0.5);
    wheelSprite.setOrigin(wheelTexture.getSize().x / 2, wheelTexture.getSize().y / 2);
    wheelSprite.setPosition(400, 300);

    this->wheelSprite.setRotation(180.f);
    int resultNumber = calculateResult();
    result = "Result: " + std::to_string(resultNumber);
    resultText.setString(result);

    // Define a triangle shape (arrow shape)
    
    arrow.setPointCount(3); // Triangle has 3 points

    // Set the points of the triangle to form an arrow shape
    arrow.setPoint(0, sf::Vector2f(0, 0));         // Top point
    arrow.setPoint(1, sf::Vector2f(50, 0));      // Bottom-right point
    arrow.setPoint(2, sf::Vector2f(25, -75));       // Bottom-left point
    arrow.setOrigin(arrow.getGlobalBounds().getSize().x / 2, arrow.getGlobalBounds().getSize().y / 2);
    // Set the position of the arrow shape
    arrow.setPosition(400, 270);
    arrow.setOutlineThickness(2);
    arrow.setOutlineColor(sf::Color::White);
    // Set the fill color
    arrow.setFillColor(sf::Color::Red);

    this->bid = std::make_shared<Text>(font,"Write amount to bid");
    this->bid->setPosition(15.f, 50.f);
}

void RouletteGame::runWindow() {
    isOpen=true;
    while (window->isOpen() && isOpen) {
        handleEvents();
        update();
        render();
    }
}

void RouletteGame::clear() {
    window->clear(sf::Color::Black);
}

void RouletteGame::close() {
    window->close();
}

void RouletteGame::display() {
    window->display();
}

void RouletteGame::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (spinButton->isClicked(mousePos)) {
                spinWheel();
            }
            else if (exitButton->isClicked(mousePos)) {
                isOpen = false;
            }
            if (bid->contains(static_cast<sf::Vector2f>(mousePos))) {
                bid->clicked();
            }


        }
        if (event.type == sf::Event::TextEntered && bid->getIsClicked() == true) {
            bid->handleEvent(event);
        }
    }
}

void RouletteGame::update() {
    if (isSpinning) {
        wheelAngle += spinSpeed;
        if (spinSpeed > 0) {
            spinSpeed -= 0.04f; // Slow down the wheel
        }
        else if (wheelAngle >= 360) {
            wheelAngle -= 360.f;
        }
        else {
            isSpinning = false;
            // Determine result
            int resultNumber = calculateResult();
            result = "Result: " + std::to_string(resultNumber);
            resultText.setString(result);
            std::cout << "Results: " << resultNumber << std::endl;
        }
        wheelSprite.setRotation(wheelAngle);
    }
}

void RouletteGame::render() {
    clear();
    window->draw(wheelSprite);
    spinButton->draw(window);
    exitButton->draw(window);
    window->draw(resultText);
    window->draw(arrow);
    bid->draw(window);
    display();
}

void RouletteGame::spinWheel() {
    if (!isSpinning) {
        isSpinning = true;
        spinSpeed = ((rand() % 50) / 10.f) + 5.f; // Initial speed
        std::cout <<"Speed: "<< spinSpeed << std::endl;
        

    }
}
int RouletteGame::calculateResult() {
    // Calculate the result number based on the current wheel angle
    int resultNumber = static_cast<int>(std::ceil((180 - (this->wheelSprite.getRotation()) -5.f)/ (360.f / 37.f))); // 0 to 36
    std::cout << "rotation " << this->wheelSprite.getRotation() << std::endl;
    std::cout << "num " << resultNumber << std::endl;
    // Adjust the result number based on 180-degree rotation
    if (resultNumber < 0) {
        resultNumber += 37; // Ensure the number is positive
    }

    // Map the original number to its new position after 180-degree rotation
    // Assuming a standard European roulette wheel, the opposite positions are:
    // 0 <-> 0, 1 <-> 18, 2 <-> 19, ..., 36 <-> 36
    static const int oppositeNumbers[37] = {
        0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24,
        16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26
    };

    return oppositeNumbers[resultNumber];
}