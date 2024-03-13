#pragma once
#include "Cat.h"

class RandomCat : public Cat
{
public:
	RandomCat() : Cat() {};
	
	void move(float passedTime, sf::Vector2f boardSize, const std::vector<std::vector<sf::Vector3i>>& Tree) override;
private:
	Direction getRandomDirection();
};

