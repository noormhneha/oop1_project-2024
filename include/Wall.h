#pragma once
#include "NonMovable.h"
#include "Mouse.h"
#include "Cat.h"

class Wall : public NonMovable
{
public:
	Wall() : NonMovable() {
		m_sprite.setTexture(*(Utilities::instance().getCharactersTexture(WALL)));
		m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
			((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	};

	virtual void collide(Icon* object) { object->collide(this); };
	virtual void collide(Mouse* object) { object->collide(this); };
	virtual void collide(Cat* object) { object->collide(this); };

	void draw(sf::RenderWindow& window, sf::Vector2f pos) override {
		m_sprite.setPosition(pos);
		window.draw(m_sprite);
	};

private:

};

