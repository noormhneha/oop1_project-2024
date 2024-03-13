#pragma once
#include "Icon.h"

// Enumeration for directions
enum Direction { RIGHT, DOWN, LEFT, UP };

// Constants for collision size and movement speed
const int COLLISION_SIZE = 30;
const float SWITCH_FRAME = 15;
const float REGULAR_SPEED = 700;
const float CAT_SPEED = 50;

class Movable : public Icon {
public:
    Movable(); // Constructor

    // Function to draw the movable object
    void draw(sf::RenderWindow& window, float passedTime) const;

    // Getter and setter for position
    sf::Vector2f getPosition() const;
    void SetPosition(sf::Vector2f newPosition);

    // Getter and setter for starting position
    sf::Vector2f getStartPosition() const;
    void setStartPosition(sf::Vector2f position);

    // Getter for direction
    Direction getDirection() const;

    // Function to get the next direction based on input
    sf::Vector2f getNextDirection(Direction direction);

protected:
    sf::Vector2f m_startPosition = { 0, 0 }; // Starting position
    sf::Vector2f m_position = { 0, 0 }; // Current position
    Direction m_direction = RIGHT; // Current direction
    Direction m_newDirection = RIGHT; // New direction
    sf::Vector2f m_previousPostion = { 0, 0 }; // Previous position

    // Function to calculate the center of a position
    sf::Vector2f getCenter(sf::Vector2f position) const;

    // Function to check if a position is centered at a specific point
    bool isCentered(sf::Vector2f position, sf::Vector2f centerPosition) const;

    // Function to check if a position is out of the board's bounds
    bool outOfBoard(sf::Vector2f size);

    // Function to move the object in a specific direction
    void moveDirection(float moveDistance);
};
