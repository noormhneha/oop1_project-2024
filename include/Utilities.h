#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>
#include "Icon.h"
#include <vector>

const int NUM_OF_CHARACTERS = 7;

class Utilities {
public:
    // Function to retrieve the texture corresponding to a character shape
    sf::Texture* getCharactersTexture(size_t shape);

    // Function to retrieve the texture for the life counter
    sf::Texture* getLifeTexture();

    // Function to get the instance of the Utilities class (singleton pattern)
    static Utilities& instance();

private:
    // Constructor (private to enforce singleton pattern)
    Utilities();

    // Function to load icon names from a file
    void iconNames(std::string str);

    // Function to check if a file is valid
    void checkIfValid(std::ifstream& inputFile);

    // Vector to store character textures
    std::vector<sf::Texture> m_CharactersTexture;

    // Texture for the life counter
    sf::Texture m_lifeCounter;

    // Vector to store level information
    std::vector<std::string> m_levels;
};
