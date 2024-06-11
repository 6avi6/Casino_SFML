#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PLAYER_SIZE = 50;
const int OBSTACLE_WIDTH = 20;
const int OBSTACLE_HEIGHT = 100;
const float OBSTACLE_SPEED = 2.0f;
const float PLAYER_SPEED = 5.0f;

struct Obstacle {
    sf::RectangleShape shape;
    float speed;

    Obstacle(float x, float y, float speed)
        : speed(speed) {
        shape.setSize(sf::Vector2f(OBSTACLE_WIDTH, OBSTACLE_HEIGHT));
        shape.setPosition(x, y);
    }

    void move() {
        shape.move(-speed, 0);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game");
    window.setFramerateLimit(60);
    sf::RectangleShape player(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    player.setFillColor(sf::Color::Green);
    player.setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);

    std::vector<Obstacle> obstacles;
    std::srand(static_cast<unsigned>(std::time(0)));

    sf::Clock clock;
    float spawnTimer = 0.0f;
    float spawnInterval = 1.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y > 0) {
            player.move(0, -PLAYER_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y + PLAYER_SIZE < WINDOW_HEIGHT) {
            player.move(0, PLAYER_SPEED);
        }

        // Spawn obstacles
        spawnTimer += clock.restart().asSeconds();
        if (spawnTimer >= spawnInterval) {
            float y = static_cast<float>(std::rand() % (WINDOW_HEIGHT - OBSTACLE_HEIGHT));
            obstacles.emplace_back(WINDOW_WIDTH, y, OBSTACLE_SPEED);
            spawnTimer = 0.0f;
        }

        // Move and remove obstacles
        for (auto& obstacle : obstacles) {
            obstacle.move();
        }
        obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
            [](const Obstacle& obs) { return obs.shape.getPosition().x + OBSTACLE_WIDTH < 0; }),
            obstacles.end());

        // Check collisions
        for (const auto& obstacle : obstacles) {
            if (player.getGlobalBounds().intersects(obstacle.shape.getGlobalBounds())) {
                // Collision detected, end game
                window.close();
            }
        }

        // Render
        window.clear();
        window.draw(player);
        for (const auto& obstacle : obstacles) {
            window.draw(obstacle.shape);
        }
        window.display();
    }

    return 0;
}
