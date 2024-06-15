#include "Text.h"

Text::Text(sf::Font& font, const std::string& initialString)
    : isClicked(false), string(initialString), cursorVisible(false), font(font), colorOfText(sf::Color::White) {
    text.setFont(this->font);
    text.setString(string.empty() ? " " : string);
    text.setCharacterSize(30); // Example size, adjust as needed
    colorOfText = sf::Color::White;
    text.setFillColor(colorOfText);
    lastBlinkTime = std::chrono::steady_clock::now();

    // Inicjalizacja hitboxa
    sf::FloatRect textRect = text.getGlobalBounds();
    hitbox.setSize(sf::Vector2f(textRect.width, textRect.height * 1.5f));
    hitbox.setFillColor(sf::Color(255, 0, 0, 0)); // Transparent color

    // Inicjalizacja podkreœlenia
    underline.setSize(sf::Vector2f(textRect.width, 2));
    underline.setFillColor(sf::Color::White);
    underline.setPosition(textRect.left, textRect.top + textRect.height + 5);
}

void Text::setString(const std::string& newString) {
    string = newString;
    text.setString(string.empty() ? " " : string);

    // Aktualizacja hitboxa
    sf::FloatRect textRect = text.getGlobalBounds();
    hitbox.setSize(sf::Vector2f(textRect.width, textRect.height));
    hitbox.setPosition(textRect.left, textRect.top);

    // Aktualizacja podkreœlenia
    underline.setSize(sf::Vector2f(textRect.width, 2));
    underline.setPosition(textRect.left, textRect.top + textRect.height + 5);
}

void Text::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    text.setPosition(position.x, position.y);

    // Aktualizacja hitboxa
    hitbox.setPosition(position.x, position.y);

    // Aktualizacja podkreœlenia
    sf::FloatRect textRect = text.getGlobalBounds();
    underline.setPosition(textRect.left, textRect.top + textRect.height + 5);
}

void Text::clicked() {
    std::cout << "Clicked" << std::endl;
    isClicked = !isClicked;
}

void Text::update(std::shared_ptr<sf::RenderWindow> window) {
    if (isClicked) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - lastBlinkTime;
        if (elapsed.count() > 0.5) { // Blink every 0.5 seconds
            cursorVisible = !cursorVisible;
            lastBlinkTime = now;
        }
    }
    if (isClicked) {

        text.setFillColor(sf::Color(colorOfText.r, colorOfText.g, colorOfText.b, (colorOfText.a)*0.5f));

    }
    else {
        text.setFillColor(colorOfText);
    }


    if (isClicked && cursorVisible) {
        sf::RectangleShape cursor(sf::Vector2f(2, text.getCharacterSize())); // Width of 2 pixels and height of character size
        cursor.setFillColor(sf::Color::White);
        sf::FloatRect textRect = text.getGlobalBounds();
        // Correct the position based on the string content
        if (string.empty()) {
            cursor.setPosition(textRect.left + textRect.width + 2, textRect.top + 8 - (this->text.getCharacterSize()));
        }
        else {
            cursor.setPosition(textRect.left + textRect.width + 2, textRect.top);
        }
        window->draw(cursor);
    }
}

void Text::draw(std::shared_ptr<sf::RenderWindow> window) {
    // Optional: draw the hitbox for debugging
    //window->draw(hitbox);
    this->update(window);
    

    window->draw(text);
    window->draw(underline);
    
}

bool Text::contains(const sf::Vector2f& point) {
    return this->hitbox.getGlobalBounds().contains(point);
}

void Text::handleEvent(const sf::Event& event) {
    if (isClicked && event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= '0' && event.text.unicode <= '9') { // Check if the entered character is a digit
            string += static_cast<char>(event.text.unicode);
            text.setString(string.empty() ? " " : string);

            // Aktualizacja hitboxa
            sf::FloatRect textRect = text.getGlobalBounds();
            hitbox.setSize(sf::Vector2f(textRect.width, textRect.height));
            hitbox.setPosition(textRect.left, textRect.top);

            // Aktualizacja podkreœlenia
            underline.setSize(sf::Vector2f(textRect.width, 2));
            underline.setPosition(textRect.left, textRect.top + textRect.height + 5);
        }
        else if (event.text.unicode == 8 && !string.empty()) { // Handle backspace (unicode 8)
            string.pop_back();
            text.setString(string.empty() ? " " : string);

            // Aktualizacja hitboxa
            sf::FloatRect textRect = text.getGlobalBounds();
            hitbox.setSize(sf::Vector2f(textRect.width, textRect.height));
            hitbox.setPosition(textRect.left, textRect.top);

            // Aktualizacja podkreœlenia
            underline.setSize(sf::Vector2f(textRect.width, 2));
            underline.setPosition(textRect.left, textRect.top + textRect.height + 5);
        }
    }
}

const bool Text::getIsClicked() {
    return this->isClicked;
}
