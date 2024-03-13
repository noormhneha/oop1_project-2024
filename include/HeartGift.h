#pragma once
#include "Gift.h"

class HeartGift : public Gift {
public:
    // Constructor for HeartGift
    HeartGift() : Gift() {
        // Set the type of the gift
        m_typegift = ADD_HEART_GIFT;
        // Set the texture and scale of the sprite
        m_sprite.setTexture(*(Utilities::instance().getCharactersTexture(HEART_GIFT)));
        m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
            ((float)P_SIZE / m_sprite.getGlobalBounds().height)));
    }
};
