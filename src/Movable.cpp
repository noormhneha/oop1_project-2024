#include "Movable.h"
#include <math.h>

Movable::Movable() {}

void Movable::draw(sf::RenderWindow& window, float) const {
	window.draw(m_sprite);
}

// Get the starting position of the movable object
sf::Vector2f Movable::getStartPosition() const {
	return m_startPosition;
}

// Get the current position of the movable object
sf::Vector2f Movable::getPosition() const {
	return m_position;
}

// Set the starting position of the movable object
void Movable::setStartPosition(sf::Vector2f position) {
	m_startPosition = position;
}

// Get the direction of the movable object
Direction Movable::getDirection() const {
	return m_direction;
}

// Get the next position of the movable object based on a given direction
sf::Vector2f Movable::getNextDirection(Direction direction) {
	sf::Vector2f nextPosition = m_sprite.getPosition();

	switch (direction)
	{
	case UP:
		nextPosition.y -= 0.1f;
		break;
	case DOWN:
		nextPosition.y += 0.1f;
		break;
	case RIGHT:
		nextPosition.x += 0.1f;
		break;
	case LEFT:
		nextPosition.x -= 0.1f;
		break;
	}
	return nextPosition;
}

// Set the position of the movable object
void Movable::SetPosition(sf::Vector2f newPosition)
{
	m_sprite.setPosition(newPosition);
}

// Check if the movable object is centered at a given position
bool Movable::isCentered(sf::Vector2f position, sf::Vector2f centerPosition) const {
	return abs(position.x - centerPosition.x) < COLLISION_SIZE && abs(position.y - centerPosition.y) < COLLISION_SIZE;
}

// Get the centered position of a given position
sf::Vector2f Movable::getCenter(sf::Vector2f position) const {
	sf::Vector2f newPosition;
	newPosition.x = (position.x - ((int)position.x % P_SIZE));
	newPosition.y = (position.y - ((int)position.y % P_SIZE));
	return newPosition;
}

// Check if the movable object is out of the board boundaries
bool Movable::outOfBoard(sf::Vector2f BoardSize)
{
	return m_sprite.getPosition().x < BoardSize.x - P_SIZE && m_sprite.getPosition().y < BoardSize.y - P_SIZE &&
		m_sprite.getPosition().x > 0 && m_sprite.getPosition().y > 0;
}

// Move the movable object in a specific direction by a certain distance
void Movable::moveDirection(float moveDistance)
{
	switch (m_direction)
	{
	case UP:
		m_sprite.move(0, -moveDistance);
		//m_sprite.setRotation(270); // Or use setScale for flipping
		break;
	case DOWN:
		m_sprite.move(0, moveDistance);
		//m_sprite.setRotation(90); // Adjust accordingly
		break;
	case RIGHT:
		m_sprite.move(moveDistance, 0);
		//m_sprite.setScale(1.f, 1.f); // Original orientation
		break;
	case LEFT:
		m_sprite.move(-moveDistance, 0);
		//m_sprite.setScale(-1.f, 1.f); // Flipped orientation
		break;
	}
}
