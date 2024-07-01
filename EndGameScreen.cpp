#include "EndGameScreen.h"
#include <thread>
#include <fstream>
#include <iostream>

EndGameScreen::EndGameScreen(std::shared_ptr<sf::RenderWindow> window, float playerScore)
    : playerScore(playerScore) {
    this->window = window;
    this->isOpen = true;
    newHighScore = false;
}

void EndGameScreen::runWindow() {
    displayScore();
    if (newHighScore) {
        promptForName();
    }
    else {
        close();
    }
}

void EndGameScreen::clear() {
    window->clear(sf::Color::White);
}

void EndGameScreen::close() {
    isOpen = false;
    clear();
}

void EndGameScreen::display() {
    window->display();
}

// Function to convert float to string with two decimal places

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
void EndGameScreen::displayScore() {





    displayScoreText();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    checkHighScore();

    this->clear();
}

void EndGameScreen::checkHighScore() {
    std::ifstream inputFile("Data/results.txt");
    if (inputFile.is_open()) {
        float score;
        std::string name;
        while (inputFile >> score >> name) {
            std::pair<float, std::string > tempScore{ score, name };
            scores.push_back(tempScore);
            std::cout << name << " " << score << "\n";
        }
        inputFile.close();
    }

    std::ranges::sort(scores, [](const auto& a, const auto& b) {
        return a.first > b.first;
        });

    // Update scores with player name
    for (auto& score : scores) {

            std::cout << score.second << "\n";


        }
  
    
    if (scores.empty() || playerScore > scores.back().first) {

        newHighScore = true;
        scores.push_back({ playerScore, "" });

        if (scores.empty()) {
            std::cout << "Scores empty" << "\n";
        }
        else
            std::cout << scores.back().first << "\n";
    }

}

void EndGameScreen::promptForName() {
    sf::Text promptText;
    promptText.setFont(font);
    promptText.setString("New High Score! Enter your name:");
    promptText.setCharacterSize(30);
    promptText.setFillColor(sf::Color::White);
    promptText.setOrigin(promptText.getGlobalBounds().getSize().x / 2, promptText.getGlobalBounds().getSize().y / 2);
    promptText.setPosition(window->getSize().x / 2, window->getSize().y / 3);

    std::string playerName;
    sf::Text playerNameText;
    playerNameText.setFont(font);
    playerNameText.setCharacterSize(30);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setPosition(window->getSize().x * 0.5, window->getSize().y *0.4);

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
                    playerNameText.setOrigin(playerNameText.getGlobalBounds().getSize().x / 2, playerNameText.getGlobalBounds().getSize().y / 2);
                    playerNameText.setPosition(window->getSize().x * 0.5, window->getSize().y * 0.4);

                }
                else if (event.text.unicode < 128 && playerName.size() < 10) { // Handle printable characters
                    playerName += static_cast<char>(event.text.unicode);
                    playerNameText.setOrigin(playerNameText.getGlobalBounds().getSize().x / 2, playerNameText.getGlobalBounds().getSize().y / 2);
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
            

            /*for (const auto& score : scores) {
                std::cout << score.first << " " << score.second << "\n";
            }*/
            // Update scores with player name
            for (auto& score : scores) {
                if (score.first == playerScore && score.second.empty()) {
                    score.second = playerName;
                    std::cout << playerName << "\n";

                    break;
                }
            }
            std::ranges::sort(scores, [](const auto& a, const auto& b) {
                return a.first > b.first;
                });
            //// Manually sort the scores vector in descending order using a simple for loop
            //for (int i = scores.size() - 1; i > 0; --i) {
            //    if (scores[i].first > scores[i - 1].first) {
            //        std::swap(scores[i], scores[i - 1]);
            //    }
            //    else {
            //        break; // Break the loop early if no more swaps are needed
            //    }
            //}


            // Write scores to file (append mode)
            std::ofstream outputFile("Data/results.txt", std::ios::trunc);
            if (outputFile.is_open()) {
                for (int i = 0; i < 10; i++) {
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
