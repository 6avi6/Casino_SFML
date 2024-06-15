#include "TitleWindow.h"

TitleWindow::TitleWindow(std::shared_ptr<sf::RenderWindow> window) {
    this->window = std::move(window);

    // Load font
    this->font = this->readFont("Assets/Fonts/arial.ttf");

    // Load and set window icon
    sf::Image icon = this->readImage("Assets/Pics/icon.png");
    this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Initialize background texture and sprite
    this->backgroundTexture = this->readTexture("Assets/Pics/main.png");
    this->background.setTexture(backgroundTexture);

    // Scale background to fit window size
    sf::Vector2u windowSize = this->window->getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / (textureSize.y * 1.2f);//it looks better with that scale 
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    this->background.setScale(scaleX, scaleY);

    // Initialize buttons
    sf::Vector2f buttonSize(200.f, 50.f);
    sf::Color buttonColor(100, 100, 100);
    sf::Color textColor(255, 255, 255);

    // Create rouletteButton
    sf::Vector2f rouletteButtonPosition(this->window->getSize().x * 0.35f, 300.f);
    rouletteButton = std::make_shared<Button>(rouletteButtonPosition, buttonSize, buttonColor, "Roulette", font);
    drawableObjects.push_back(rouletteButton);

    // Create coinflipButton
    sf::Vector2f coinflipButtonPosition(this->window->getSize().x * 0.65f, 300.f);
    coinflipButton = std::make_shared<Button>(coinflipButtonPosition, buttonSize, buttonColor, "Coinflip", font);
    drawableObjects.push_back(coinflipButton);

    // Create exitButton
    sf::Vector2f exitButtonPosition(this->window->getSize().x * 0.5f, 380.f);
    exitButton = std::make_shared<Button>(exitButtonPosition, buttonSize, sf::Color::Red, "Exit", font);
    drawableObjects.push_back(exitButton);
}

void TitleWindow::runWindow() {
    while (this->window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                    // Check if exitButton is clicked
                    if (exitButton->isClicked(mousePos)) {
                        window->close();
                    }

                    // Check if rouletteButton is clicked
                    if (rouletteButton->isClicked(mousePos)) {
                        // Handle button click for roulette
                        RouletteGame rouletteGame(this->window);
                        rouletteGame.runWindow();
                    }

                    // Check if coinflipButton is clicked
                    if (coinflipButton->isClicked(mousePos)) {
                        // Handle button click for coinflip
                        CoinflipGame coinflipGame(this->window);
                        coinflipGame.runWindow();
                    }
                }
            }
        }

        // Clear the window
        clear();

        // Draw the background
        window->draw(background);

        // Draw all drawable objects
        for (const auto& obj : drawableObjects) {
            obj->draw(window);
        }

        // Display the drawn frame
        display();
    }
}

void TitleWindow::clear() {
    window->clear();
}

void TitleWindow::close() {
    window->close();
}

void TitleWindow::display() {
    window->display();
}
