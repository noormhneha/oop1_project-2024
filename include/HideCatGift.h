#pragma once

#include "Gift.h"

class HideCatGift : public Gift {
public:
	HideCatGift() : Gift() {
		m_typegift = HIDE_CAT_GIFT;
		m_sprite.setTexture(*(Utilities::instance().getCharactersTexture(CAT_GIFT)));
		m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
			((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	};

};