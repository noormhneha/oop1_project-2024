#pragma once

#include "Gift.h"

class TimeGift : public Gift {
public:
	TimeGift() : Gift() {
		m_typegift = ADD_TIME_GIFT;
		m_sprite.setTexture(*(Utilities::instance().getCharactersTexture(TIME_GIFT)));
		m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
			((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	};
};