#pragma once

#include "NonMovable.h"
#include "Mouse.h"

class Cheese : public NonMovable {
public:
    // Constructor
    Cheese() : NonMovable() {
        // Set up cheese sprite
        m_sprite.setTexture(*(Utilities::instance().getCharactersTexture(CHEESE)));
        m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
            ((float)P_SIZE / m_sprite.getGlobalBounds().height)));
    };

    // Override collide function for interacting with different types of icons
    virtual void collide(Icon* object) override { object->collide(this); };
    virtual void collide(Mouse* object) override { object->collide(this); };
    virtual void collide(Cat*) override {};

};
