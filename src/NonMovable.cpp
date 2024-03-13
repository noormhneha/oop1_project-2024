#include "NonMovable.h"

// Get the status of the non-movable object
bool NonMovable::getStatus() const
{
	return m_status;
}

// Set the status of the non-movable object
void NonMovable::setStatus(bool status)
{
	m_status = status;
}

// Get the position of the non-movable object
sf::Vector2f NonMovable::getPosition() const
{
	return m_position;
}

// Set the position of the non-movable object
void NonMovable::setPosition(sf::Vector2f position)
{
	m_position = position;
}

// Draw the non-movable object on the window at a specific position
void NonMovable::draw(sf::RenderWindow& window, sf::Vector2f pos)
{
	if (m_status) {
		m_sprite.setPosition(pos);
		window.draw(m_sprite);
	}
}

// Get the global bounds of the non-movable object
sf::FloatRect NonMovable::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}
