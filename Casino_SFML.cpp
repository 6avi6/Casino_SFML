#include <SFML/Graphics.hpp>
#include "TitleWindow.h"
#include <memory>

int main() {
    // Create a shared pointer to an SFML window
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "My Casino");
    window->setFramerateLimit(60);

    // Create an instance of TitleWindow
    TitleWindow titleWindow(window);
    titleWindow.runWindow();

    return 0;
}
