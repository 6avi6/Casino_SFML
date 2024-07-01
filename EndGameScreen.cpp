#include "EndGameScreen.h"
#include <thread>
#include <fstream>
#include <iostream>

// Constructor for the EndGameScreen class
EndGameScreen::EndGameScreen(std::shared_ptr<sf::RenderWindow> window, float playerScore)
    : playerScore(playerScore) {
    this->window = window;
    this->isOpen = true;
    newHighScore = false;
}

// Main function to run the end game screen
void EndGameScreen::runWindow() {
    displayScore();
    if (newHighScore) {
        promptForName();
    }
    else {
        close();
    }
}

// Function to clear the window
void EndGameScreen::clear() {
    window->clear(sf::Color::White);
}

// Function to close the end game screen
void EndGameScreen::close() {
    isOpen = false;
    clear();
}

// Function to display the window contents
void EndGameScreen::display() {
    window->display();
}

// Function to display the score text
void EndGameScreen::displayScoreText() {
    font = readFont("Assets/Fonts/arial.ttf");

    loadBackground("Assets/Pics/Roulette/background.png");
    window->draw(scoreText);
    window->draw(background);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Congratulations! You scored: " + to_string_with_precision(playerScore, 2) + " $");
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(100, 100);

    window->draw(scoreText);
    this->display();
}

// Function to display the score
void EndGameScreen::displayScore() {
    displayScoreText();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    checkHighScore();
    this->clear();
}

bool isValidLine(const std::string& line) {
    std::regex pattern(R"(^\d+(\.\d{1,2})? [A-Za-z]+$)");
    return std::regex_match(line, pattern);
}

void checkFileStructure(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;
    bool isValid = true;

    while (std::getline(file, line)) {
        lineNumber++;
        if (!isValidLine(line)) {
            std::cout << "Invalid structure at line " << lineNumber << ": " << line << std::endl;
            isValid = false;
        }
    }

    if (isValid) {
        std::cout << "All lines have a valid structure." << std::endl;
    }
    else {
        std::cout << "File has lines with invalid structure." << std::endl;
    }

    file.close();
}

// Function to check if the player's score is a new high score
void EndGameScreen::checkHighScore() {
    std::ifstream inputFile("Data/results.txt");

    ///

    checkFileStructure("Data/results.txt");

    ///

    if (inputFile.is_open()) {
        float score;
        std::string name;
        while (inputFile >> score >> name) {
            std::pair<float, std::string> tempScore{ score, name };
            scores.push_back(tempScore);
            std::cout << name << " " << score << "\n";
        }
        inputFile.close();
    }

    std::ranges::sort(scores, [](const auto& a, const auto& b) {
        return a.first > b.first;
        });

    // Print updated scores
    for (auto& score : scores) {
        std::cout << score.second << "\n";
    }

    if (scores.empty() || playerScore > scores.back().first) {
        newHighScore = true;
        scores.push_back({ playerScore, "" });

        if (scores.empty()) {
            std::cout << "Scores empty" << "\n";
        }
        else {
            std::cout << scores.back().first << "\n";
        }
    }
}

// Function to prompt the player for their name if they have a new high score
void EndGameScreen::promptForName() {
    sf::Text promptText;
    promptText.setFont(font);
    promptText.setString("New High Score! Enter your name:");
    promptText.setCharacterSize(30);
    promptText.setFillColor(sf::Color::White);
    promptText.setOrigin(promptText.getGlobalBounds().width / 2, promptText.getGlobalBounds().height / 2);
    promptText.setPosition(window->getSize().x / 2, window->getSize().y / 3);

    std::string playerName;
    sf::Text playerNameText;
    playerNameText.setFont(font);
    playerNameText.setCharacterSize(30);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setPosition(window->getSize().x * 0.5, window->getSize().y * 0.4);

    bool nameEntered = false; // Flag to track if player name is entered

    while (window->isOpen() && isOpen) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Handle backspace
                    if (!playerName.empty()) {
                        playerName.pop_back();
                    }
                    playerNameText.setOrigin(playerNameText.getGlobalBounds().width / 2, playerNameText.getGlobalBounds().height / 2);
                    playerNameText.setPosition(window->getSize().x * 0.5, window->getSize().y * 0.4);
                }
                else if (event.text.unicode < 128 && playerName.size() < 10) { // Handle printable characters
                    playerName += static_cast<char>(event.text.unicode);
                    playerNameText.setOrigin(playerNameText.getGlobalBounds().width / 2, playerNameText.getGlobalBounds().height / 2);
                    playerNameText.setPosition(window->getSize().x * 0.5, window->getSize().y * 0.4);
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (!playerName.empty()) {
                    nameEntered = true; // Mark name as entered
                }
            }
        }

        playerNameText.setString(playerName);

        window->clear();
        window->draw(background);
        window->draw(promptText);
        window->draw(playerNameText);
        window->display();

        // Check if name is entered and save scores if so
        if (nameEntered) {
            // Update scores with player name
            for (auto& score : scores) {
                if (score.first == playerScore && score.second.empty()) {
                    score.second = playerName;
                    std::cout << playerName << "\n";
                    break;
                }
            }

            // Sort the scores vector in descending order
            std::ranges::sort(scores, [](const auto& a, const auto& b) {
                return a.first > b.first;
                });

            // Write scores to file (trunc mode)
            std::ofstream outputFile("Data/results.txt", std::ios::trunc);
            if (outputFile.is_open()) {
                for (int i = 0; i < 10 && i < scores.size(); ++i) {
                    outputFile << scores[i].first << " " << scores[i].second << "\n";
                    std::cout << scores[i].first << " " << scores[i].second << "\n";
                }
                outputFile.close();
            }
            else {
                std::cerr << "Failed to open results file for writing." << std::endl;
            }

            isOpen = false;
        }
    }
}
