#pragma once

#include "NonMovable.h"
#include "Mouse.h"

class HeartGift;
class HideCatGift;
class TimeGift;

enum TypeGift {
    ADD_HEART_GIFT,
    HIDE_CAT_GIFT,
    ADD_TIME_GIFT
};

class Gift : public NonMovable {
public:
    Gift() : NonMovable() {}; // Constructor

    virtual void collide(Icon* object) { object->collide(this); }; // Method to handle collision with an icon
    virtual void collide(Mouse* object) { object->collide(this); }; // Method to handle collision with a mouse
    virtual void collide(Cat*) {}; // Method to handle collision with a cat

    TypeGift getType() const { return m_typegift; }; // Method to get the type of gift

protected:
    TypeGift m_typegift; // Type of gift
};
