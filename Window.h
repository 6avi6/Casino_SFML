#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "GraphicalObject.h"
#include <vector>
#include <filesystem>
#include <iostream>

// Base class for a graphical application window
class Window {
public:
    // Shared pointer to an SFML RenderWindow
    std::shared_ptr<sf::RenderWindow> window;

    // Pure virtual functions to be implemented by derived classes
    virtual void runWindow() = 0;
    virtual void clear() = 0;
    virtual void close() = 0;
    virtual void display() = 0;
    bool isOpen;
    // Method to read and load a font from a file
    sf::Font readFont(const std::string& fontPath) {
        // Check if the file exists
        if (!std::filesystem::exists(fontPath)) {
            throw std::runtime_error("Font file does not exist: " + fontPath);
        }

        sf::Font font;
        // Load the font from the file
        if (!font.loadFromFile(fontPath)) {
            // Handle error if the font fails to load
            throw std::runtime_error("Failed to load font from path: " + fontPath);
        }
        return font;
    }

    // Method to read and load a texture from a file
    sf::Texture readTexture(const std::string& texturePath) {
        // Check if the file exists
        if (!std::filesystem::exists(texturePath)) {
            throw std::runtime_error("Texture file does not exist: " + texturePath);
        }

        sf::Texture texture;
        // Load the texture from the file
        if (!texture.loadFromFile(texturePath)) {
            // Handle error if the texture fails to load
            throw std::runtime_error("Failed to load texture from path: " + texturePath);
        }
        return texture;
    }

    // Method to read and load an image from a file
    sf::Image readImage(const std::string& imagePath) {
        // Check if the file exists
        if (!std::filesystem::exists(imagePath)) {
            throw std::runtime_error("Image file does not exist: " + imagePath);
        }

        sf::Image image;
        // Load the image from the file
        if (!image.loadFromFile(imagePath)) {
            // Handle error if the image fails to load
            throw std::runtime_error("Failed to load image from path: " + imagePath);
        }
        return image;
    }

    sf::Sprite background;
    sf::Texture backgroundTexture;
    void loadBackground(const std::string& fontPath) {
        // Initialize background texture and sprite
        backgroundTexture = readTexture(fontPath);
        background.setTexture(backgroundTexture);
    }
    std::string to_string_with_precision(float value, int precision = 2) {
        std::ostringstream out;
        out << std::fixed << std::setprecision(precision) << value;
        return out.str();
    }

protected:
    // Vector to hold drawable objects
    std::vector<std::shared_ptr<GraphicalObject>> drawableObjects;
};

#endif // !WINDOW_H
