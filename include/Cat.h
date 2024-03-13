#pragma once

#include "Movable.h"
#include <vector>
#include <memory>

class Cat : public Movable {
public:
    // Constructor
    Cat();

    // Virtual function for moving the cat
    virtual void move(float passedTime, sf::Vector2f boardSize, const std::vector<std::vector<sf::Vector3i>>& Tree) = 0;

    // Virtual functions for collision handling with different types of icons
    virtual void collide(Icon*) {};
    virtual void collide(Mouse*) {};
    virtual void collide(Cat*) {};
    virtual void collide(Cheese*) {};
    virtual void collide(Wall*);
    virtual void collide(Door*);
    virtual void collide(Key*) {};
    virtual void collide(Gift*) {};

protected:
    bool m_moving;           // Flag to indicate if the cat is moving
    bool m_wallCollision;    // Flag to indicate if the cat collided with a wall
    bool m_doorCollision;    // Flag to indicate if the cat collided with a door
};
