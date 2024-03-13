#include "Cat.h"             // Including necessary header file

// Constructor for Cat class, initializes member variables
Cat::Cat() : m_doorCollision(false), m_wallCollision(false), m_moving(false) {
    // Setting texture and origin for sprite
    m_sprite.setTexture(*(Utilities::instance().getCharactersTexture(CAT)));
    m_sprite.setOrigin(getCenter(m_sprite.getPosition()));
    // Scaling sprite to fit the grid size
    m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
        ((float)P_SIZE / m_sprite.getGlobalBounds().height)));
    // Setting initial position and direction
    SetPosition(m_sprite.getOrigin());
    m_direction = RIGHT;
}

// Function to handle collision with a wall
void Cat::collide(Wall*) {
    // Resetting position to previous position
    m_sprite.setPosition(m_previousPostion);
    m_wallCollision = true;
}

// Function to handle collision with a door
void Cat::collide(Door*) {
    // Resetting position to previous position
    m_sprite.setPosition(m_previousPostion);
    m_doorCollision = true;
}
