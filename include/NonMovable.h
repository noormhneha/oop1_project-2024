#pragma once
#include "Icon.h"

class NonMovable : public Icon {
public:
    // Constructor for NonMovable
    NonMovable() : m_status(true) {}

    // Getter for status
    bool getStatus() const;

    // Setter for status
    void setStatus(bool status);

    // Getter for position
    sf::Vector2f getPosition() const;

    // Setter for position
    void setPosition(sf::Vector2f position);

    // Virtual function to draw the non-movable object
    virtual void draw(sf::RenderWindow& window, sf::Vector2f pos);

    // Virtual function to get the global bounds of the object
    virtual sf::FloatRect getGlobalBounds() const;

    // Virtual functions to handle collisions with different objects
    virtual void collide(Cheese*) {};
    virtual void collide(Wall*) {};
    virtual void collide(Door*) {};
    virtual void collide(Key*) {};
    virtual void collide(Gift*) {};

protected:
    bool m_status; // Status of the non-movable object
    sf::Vector2f m_position; // Position of the non-movable object
};
