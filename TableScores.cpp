#include "TableScores.h"

TableScores::TableScores(std::shared_ptr<sf::RenderWindow> window) 
{   
    // Create the exit button in the top right corner

    isOpen = true;
    this->window = window;
    font = readFont("Assets/Fonts/arial.ttf");
    this->loadPlayerScoresFromFile("Data/results.txt");
    this->initScores();
    exitButton = std::make_shared<Button>(sf::Vector2f(this->window->getSize().x - 100 / 2, 50 / 2), sf::Vector2f(100, 50), sf::Color::Red, "Exit", font);
    loadBackground("Assets/Pics/Roulette/background.png");


}
void TableScores::loadPlayerScoresFromFile(const std::string& filename) {
    // Clear existing player scores
    // Assuming topScores and scores are member variables of TableScores

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    int i = 0;

    // Assuming topScores and scores are large enough to hold all potential scores
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string score_str;
        std::string name;

        // Read the score (as a string first to handle decimals correctly)
        iss >> score_str;

        // Convert score_str to a floating point number
        double score = std::stod(score_str);

        // Read the rest of the line as the player name
        std::getline(iss >> std::ws, name);

        // Check if i is within bounds of topScores and scores arrays
        if (i < 10) {  // MAX_SCORES should be defined or determined based on your needs
            scores[i].setString(name + " " + to_string_with_precision(score));
           
        }
        else {
            std::cerr << "Exceeded maximum number of scores." << std::endl;
            break;  // Break the loop if trying to write beyond allocated memory
        }

        i++;
    }

    file.close();
}




void TableScores::runWindow()
{

    while (this->isOpen) {
        // Process events
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.key.code == sf::Keyboard::Escape)
                this->isOpen = false;
            else if ( exitButton->isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                // Close the window if the exit button is clicked

                this->isOpen = false;
            }
        }

        // Clear the window
        window->clear();
        window->draw(background);
        this->displayTableScores();
        exitButton->draw(this->window);
        // Display the contents of the window
        window->display();
    }

}


void TableScores::initScores()
{
    size_t length = 10;
    float upDonwPadding = (window->getSize().y * 0.8) / length;

    titleOfWindow.setFont(this->font);
    titleOfWindow.setString("Top Scores");
    titleOfWindow.setCharacterSize(34);
    titleOfWindow.setFillColor(sf::Color::White);
    titleOfWindow.setOrigin(titleOfWindow.getLocalBounds().getSize().x / 2, 0);
    titleOfWindow.setPosition(window->getSize().x / 2, 1 * upDonwPadding);


    for (int i = 0; i < length; i++) {
        scores[i].setFont(this->font);

        scores[i].setCharacterSize(24);
        scores[i].setFillColor(sf::Color::White);
        scores[i].setOrigin(scores[i].getLocalBounds().getSize().x / 2, 0);
        scores[i].setPosition(window->getSize().x / 2, 2 * upDonwPadding + upDonwPadding * i);

    }
}

void TableScores::displayTableScores()
{
    size_t length = 10;
    this->window->draw(this->titleOfWindow);
    for (int i = 0; i < length; i++) {
        this->window->draw(this->scores[i]);

    }
}
