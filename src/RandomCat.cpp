#include "RandomCat.h"

// Function to move the random cat
void RandomCat::move(float passedTime, sf::Vector2f boardSize, const std::vector<std::vector<sf::Vector3i>>&)
{
    // Store the previous position of the cat
    m_previousPostion = m_sprite.getPosition();
    // Calculate the distance to move based on time passed
    float moveDistance = CAT_SPEED * passedTime;

    // Generate a random number to decide whether to change direction
    int randomSwitch = (rand() % 10);

    // Check if it's time to change direction or if there was a wall collision
    if (passedTime > randomSwitch || m_wallCollision)
    {
        m_wallCollision = false; // Reset wall collision flag
        m_moving = true; // Set moving flag
        // Get a random direction for the cat
        m_direction = getRandomDirection();
    }

    // Move the cat in the current direction
    moveDirection(moveDistance);

    // Check if the cat is out of the board boundaries
    if (!outOfBoard(boardSize))
        m_sprite.setPosition(m_previousPostion); // Move back to previous position
    m_position = m_sprite.getPosition(); // Update the current position
}

// Function to get a random direction for the cat
Direction RandomCat::getRandomDirection()
{
    // Array of possible directions
    Direction arrayOfDirection[] = { LEFT, RIGHT, UP, DOWN };
    // Generate a random index and return the corresponding direction
    return arrayOfDirection[rand() % 4];
}
