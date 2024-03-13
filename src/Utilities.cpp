#include "Utilities.h"

Utilities::Utilities() {
    iconNames("Names_images.txt");
}

void Utilities::iconNames(std::string str) {
    std::ifstream inputFile(str);
    checkIfValid(inputFile);
    std::string line;
    while (std::getline(inputFile, line)) {
        sf::Texture texture;
        texture.loadFromFile(line);
        m_CharactersTexture.push_back(texture); // Add texture to the vector
    }
}

void Utilities::checkIfValid(std::ifstream& inputFile) {
    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file 'Names_images.txt'" << std::endl;
        exit(EXIT_FAILURE);
    }
}

sf::Texture* Utilities::getCharactersTexture(size_t shape) {
    if (shape < m_CharactersTexture.size()) {
        return &m_CharactersTexture[shape];
    }
    else {
        // Handle out-of-bounds access gracefully
        return nullptr;
    }
}

sf::Texture* Utilities::getLifeTexture() {
    return  &m_lifeCounter;
}

Utilities& Utilities::instance() {
    static Utilities instance;
    return instance;
}
