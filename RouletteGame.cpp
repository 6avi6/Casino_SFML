#include "RouletteGame.h"


// Constructor to initialize the game
RouletteGame::RouletteGame(std::shared_ptr<sf::RenderWindow> window) : 
    isSpinning(false), wheelAngle(0.f), spinSpeed(0.0f),playerCredits(100),playerTopScore(100) {
    this->window = std::move(window);

    // Load the font
    font = readFont("Assets/Fonts/arial.ttf");

    // Initialize background texture and sprite
    backgroundTexture = readTexture("Assets/Pics/Roulette/background.png");
    background.setTexture(backgroundTexture);
    background.setScale((this->window->getSize().x / this->background.getGlobalBounds().getSize().x)*1.2f, this->window->getSize().y / background.getGlobalBounds().getSize().y);

    // Initialize result text
    resultText.setFont(font);
    resultText.setCharacterSize(24);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(350, 50);
    resultText.setString("Click Spin to Start");

    cashBalance.setFont(font);
    cashBalance.setCharacterSize(24);
    cashBalance.setFillColor(sf::Color::White);
    cashBalance.setPosition(600, 120);
    cashBalance.setString("Funds:");


    // Create buttons
    spinButton = std::make_shared<Button>(sf::Vector2f(115, 120), sf::Vector2f(200, 50), sf::Color::Green, "Spin", font);
    exitButton = std::make_shared<Button>(sf::Vector2f(750, 25), sf::Vector2f(100, 50), sf::Color::Red, "Exit", font);

    // Load the roulette wheel texture
    wheelTexture = readTexture("Assets/Pics/Roulette/roulette_wheel.png");
    wheelSprite.setTexture(wheelTexture);
    wheelSprite.scale(0.3, 0.3);
    wheelSprite.setOrigin(wheelTexture.getSize().x / 2, wheelTexture.getSize().y / 2);
    wheelSprite.setPosition(400, 250);

    this->wheelSprite.setRotation(180.f);
    int resultNumber = calculateResult();
    result = "Result: " + std::to_string(resultNumber);
    resultText.setString(result);

    textPlayerCredits.setFont(font);
    textPlayerCredits.setCharacterSize(24);
    textPlayerCredits.setFillColor(sf::Color::White);
    textPlayerCredits.setString(to_string_with_precision(playerCredits, 2) +" $");
    textPlayerCredits.setPosition(600, 150);

    // Define a triangle shape (arrow shape)
    
    arrow.setPointCount(3); // Triangle has 3 points

    // Set the points of the triangle to form an arrow shape
    arrow.setPoint(0, sf::Vector2f(0, 0));         // Top point
    arrow.setPoint(1, sf::Vector2f(50, 0));      // Bottom-right point
    arrow.setPoint(2, sf::Vector2f(25, -75));       // Bottom-left point
    arrow.setOrigin(arrow.getGlobalBounds().getSize().x / 2, arrow.getGlobalBounds().getSize().y / 2);
    // Set the position of the arrow shape
    arrow.setPosition(400, 220);
    arrow.setOutlineThickness(2);
    arrow.setOutlineColor(sf::Color::White);
    // Set the fill color
    arrow.setFillColor(sf::Color::Red);
    arrow.scale(0.5, 0.5);

    this->bid = std::make_shared<Text>(font,"Write amount to bid");
    this->bid->setPosition(15.f, 50.f);


    this->board = std::make_shared<BoardsForBets>(sf::Vector2f(this->window->getSize().x*0.5f, this->window->getSize().y * 0.8f), sf::Vector2f(1, 1), font);
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
            if (spinButton->isClicked(mousePos) && bid->getIsClicked()==false) {
                spinWheel();
            }
            else if (exitButton->isClicked(mousePos)) {
                isOpen = false;
            }
            if (bid->contains(static_cast<sf::Vector2f>(mousePos))) {
                if (bid->getIsClicked()) {
                    if (playerCredits - std::stod(bid->getString()) >= 0) {
                        playerCredits = playerCredits -std::stod(bid->getString());
                    }
                    else {
                        bid->setString(to_string_with_precision(playerCredits));
                        playerCredits = 0;

                    }
                }
                else {
                    try {
                        // Attempt to convert the string to a double and add to playerCredits
                        playerCredits += std::stod(bid->getString());
                    }
                    catch (const std::invalid_argument&) {
                        // If conversion fails, set the bid string to "0"
                        bid->setString("0");
                    }
                    catch (const std::out_of_range&) {
                        // If conversion is out of range, set the bid string to "0"
                        bid->setString("0");
                    }

                }
                textPlayerCredits.setString(to_string_with_precision(playerCredits, 2) + " $");
                bid->clicked();
            }
            

        }
        if (event.type == sf::Event::TextEntered && bid->getIsClicked() == true) {
            bid->handleEvent(event);
        }
        if(spinSpeed<=0)
        this->board->update(event);
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
            calculateAndDisplayResult(resultNumber);
        }
        wheelSprite.setRotation(wheelAngle);
    }
    int bidNumber = 0;
    try {
        // Attempt to convert the string to a double and add to playerCredits
       bidNumber= std::stod(bid->getString());
    }
    catch (const std::invalid_argument&) {
        // If conversion fails, set the bid string to "0"
        bidNumber = 0;
    }
    catch (const std::out_of_range&) {
        // If conversion is out of range, set the bid string to "0"
        bidNumber = 0;
    }


    if ( (playerCredits+bidNumber<=0) ) {
        this->clear();
        std::shared_ptr<EndGameScreen> endGameScreen=std::make_shared<EndGameScreen>(this->window, this->playerTopScore);
        endGameScreen->runWindow();
        this->isOpen = false;
    }
}

void RouletteGame::render() {
    clear();
    window->draw(background);
    window->draw(textPlayerCredits);
    window->draw(wheelSprite);
    spinButton->draw(window);
    exitButton->draw(window);
    window->draw(resultText);
    window->draw(cashBalance);
    window->draw(arrow);
    bid->draw(window);
    board->draw(window);
    display();
}

void RouletteGame::spinWheel() {
    if (!isSpinning) {
        isSpinning = true;
        spinSpeed = this->generateSpinSpeed() + 5.f; // Initial speed
        std::cout <<"Speed: "<< spinSpeed << std::endl;
        

    }
}
float RouletteGame::generateSpinSpeed()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Using the <random> library for better randomness
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(5.0f, 10.0f);

    return dist(gen);
}
int RouletteGame::calculateResult() {
    // Calculate the result number based on the current wheel angle
    int resultNumber = static_cast<int>(std::ceil((180 - (this->wheelSprite.getRotation()) -5.f)/ (360.f / 37.f))); // 0 to 36
    std::cout << "rotation " << this->wheelSprite.getRotation() << std::endl;

    // Adjust the result number based on 180-degree rotation
    if (resultNumber < 0) {
        resultNumber += 37; // Ensure the number is positive
    }

    // Map the original number to its new position after 180-degree rotation
    // Assuming a standard European roulette wheel, the opposite positions are:
    // 0 <-> 0, 1 <-> 18, 2 <-> 19, ..., 36 <-> 36
    static const int oppositeNumbers[37] = {
        0, 32, 15, 19, 4, 21, 2, 25, 17, 27, 6, 34, 13, 36, 11, 30, 8, 23, 10, 5, 24,
        16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26
    };
    static const sf::Color numberColors[37] = {
        sf::Color::Green, // 0 - Green
        sf::Color::Black, // 1 - Black
        sf::Color::Red,   // 2 - Red
        sf::Color::Black, // 3 - Black
        sf::Color::Red,   // 4 - Red
        sf::Color::Black, // 5 - Black
        sf::Color::Red,   // 6 - Red
        sf::Color::Black, // 7 - Black
        sf::Color::Red,   // 8 - Red
        sf::Color::Black, // 9 - Black
        sf::Color::Red,   // 10 - Red
        sf::Color::Red,   // 11 - Red
        sf::Color::Black, // 12 - Black
        sf::Color::Red,   // 13 - Red
        sf::Color::Black, // 14 - Black
        sf::Color::Red,   // 15 - Red
        sf::Color::Black, // 16 - Black
        sf::Color::Red,   // 17 - Red
        sf::Color::Black,   // 18 - Black
        sf::Color::Black, // 19 - Black
        sf::Color::Red,   // 20 - Red
        sf::Color::Black, // 21 - Black
        sf::Color::Red,   // 22 - Red
        sf::Color::Black, // 23 - Black
        sf::Color::Red,   // 24 - Red
        sf::Color::Black, // 25 - Black
        sf::Color::Red,   // 26 - Red
        sf::Color::Black, // 27 - Black
        sf::Color::Red,   // 28 - Red
        sf::Color::Red,   // 29 - Red
        sf::Color::Black, // 30 - Black
        sf::Color::Red,   // 31 - Red
        sf::Color::Black, // 32 - Black
        sf::Color::Red,   // 33 - Red
        sf::Color::Black, // 34 - Black
        sf::Color::Red,   // 35 - Red
        sf::Color::Black  // 36 - Black

    };

    
    std::cout << "Numer: " << oppositeNumbers[resultNumber]
        << " Kolor: " << ((numberColors[oppositeNumbers[resultNumber]] == sf::Color::Red) ? "Czerwony" :
            (numberColors[oppositeNumbers[resultNumber]] == sf::Color::Black) ? "Czarny" : "Zielony")
        << std::endl;
/**/
    return oppositeNumbers[resultNumber];
}

void RouletteGame::calculateAndDisplayResult(int resultNumber) {
    // Obliczanie wygranej na podstawie planszy
    float winnings = board->calculateWinnings(resultNumber);

    // Pobranie stringa z bid i próba konwersji na liczbê
    std::string inputString = bid->getString();
    int bidAmount = 0;

    // Walidacja czy inputString jest liczb¹ za pomoc¹ ranges
    if (std::ranges::all_of(inputString, [](char c) { return std::isdigit(c); }))//ranges used
    {
        bidAmount = std::stoi(inputString);
    }

    // Logika wyœwietlania wyniku i wygranej
    std::cout << "Wygrana: " << winnings << std::endl;

    // Przyk³adowe u¿ycie wyniku jako tekstu na ekranie
    
    playerCredits +=bidAmount * winnings- std::stod(bid->getString());
    if (playerTopScore < playerCredits + std::stod(bid->getString()))
        playerTopScore = playerCredits + std::stod(bid->getString());

    std::cout << "Top Score: " << playerTopScore << std::endl;
        
    textPlayerCredits.setString(to_string_with_precision(playerCredits, 2) + " $");


    // Inne operacje zwi¹zane z wyœwietlaniem wyniku na ekranie
}