#include "BoardsForBets.h"

BoardsForBets::BoardsForBets(sf::Vector2f postion, sf::Vector2f scale, sf::Font& font):
    scale(scale),font(font)
{   
    this->position = sf::Vector2f(postion.x-(50.f*6), postion.y - (50.f * 1.5));
	this->initBoard();
}

void BoardsForBets::draw(std::shared_ptr<sf::RenderWindow> window)
{
	for (auto& field : boardFields)
	{
		field->draw(window);
	}
}

void BoardsForBets::update(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            for (auto& field : boardFields)
            {
                if (field->isClicked(mousePos))
                {
                    // Handle the event for the button
                    field->setSelected(!field->getSelected());
                }
            }
        }
    }
}

void BoardsForBets::initBoard()
{
    const sf::Vector2f sizeOfOneField(50.f, 50.f);
    int rows = 3; // Number of rows for the betting board
    int cols = 12; // Number of columns for the betting board
    const sf::Vector2f _position = this->position;

    // Add the zero field
    std::shared_ptr<SelectedButton> button = std::make_shared<SelectedButton>(
        sf::Vector2f(_position.x, _position.y + 50.f),
        sf::Vector2f(sizeOfOneField.x, sizeOfOneField.y * 3),
        sf::Color::Green, "0", font, 20
    );
    boardFields.push_back(button);

    // Define the standard European roulette sequence
    const int rouletteNumbers[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
                                      13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
                                      23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
                                      33, 34, 35, 36 };

    const sf::Color colors[36] = {
        sf::Color::Black, sf::Color::Red, sf::Color::Black,
        sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Black,
        sf::Color::Red, sf::Color::Black, sf::Color::Black, sf::Color::Red,
        sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red,
        sf::Color::Black, sf::Color::Red, sf::Color::Red, sf::Color::Black,
        sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Black,
        sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Black,
        sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red,
        sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red,sf::Color::Black
    };

    int counter = 0;
    for (int j = 1; j < cols + 1; ++j)
    {
        for (int i = 0; i < rows; ++i)
        {
            if (counter >= 36) break; // Ensure we don't go out of bounds

            const sf::Vector2f buttonPosition = this->position + sf::Vector2f(j * sizeOfOneField.x, (2-i) * sizeOfOneField.y);
            const int number = rouletteNumbers[counter];
            const std::string numStr = std::to_string(number);
            const sf::Color color = colors[counter];

            auto button = std::make_shared<SelectedButton>(buttonPosition, sizeOfOneField, color, numStr, font, counter);
            boardFields.push_back(button);

            counter++;
        }
    }
    std::shared_ptr<SelectedButton> buttonRED = std::make_shared<SelectedButton>(
        sf::Vector2f(_position.x*3, _position.y + 50.f*3),
        sf::Vector2f(sizeOfOneField.x*3, sizeOfOneField.y),
        sf::Color::Red,"", font, -1
    );
    std::shared_ptr<SelectedButton> buttonBLACK = std::make_shared<SelectedButton>(
        sf::Vector2f(_position.x*5, _position.y + 50.f*3),
        sf::Vector2f(sizeOfOneField.x*3, sizeOfOneField.y),
        sf::Color::Black, "", font, -2
    );
    boardFields.push_back(buttonRED);
    boardFields.push_back(buttonBLACK);
}


float BoardsForBets::calculateWinnings(int resultNumber) const {
    float multiplier = 0.0f; // Default multiplier
    static const sf::Color numberColors[37] = {
        sf::Color::Green, sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red,
        sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Black,
        sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red,
        sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Red,
        sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Black,
        sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red,
        sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Black,
        sf::Color::Red, sf::Color::Black
    };

    // Check if the result matches the color and adjust multiplier
    if (boardFields[boardFields.size() - 2]->getSelected() && numberColors[resultNumber] == sf::Color::Red) {
        multiplier = 2.0f;
        //std::cout << "RED " << boardFields[37]->getValue() << std::endl;
    }
    else if (boardFields[boardFields.size() - 1]->getSelected() && numberColors[resultNumber] == sf::Color::Black) {
        multiplier = 2.0f;
        //std::cout << "BLACK " << boardFields[38]->getValue() << std::endl;
    }
    int c = 0;
    if (multiplier == 0.0f) {

        for (int i = 0; i < boardFields.size() - 2; i++) {
            if(boardFields[i]->getSelected()){
                if (boardFields[i]->getSelected() && boardFields[i]->getValue() == resultNumber) {
                    multiplier = 36.0f; // Payout for single number bet is 36 times the bet amount
                    std::cout << "WIN ";
                }
                c++;
            }
        }
    }
    if (c > 0)
        multiplier=multiplier / c;
    std::cout << "NUMEREK " << resultNumber << std::endl;

    return multiplier;
}