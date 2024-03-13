#pragma once
#include "Cat.h"

class SmartCat : public Cat
{
public:
	SmartCat() : Cat() {};

	void move(float passedTime, sf::Vector2f boardSize, const std::vector<std::vector<sf::Vector3i>>& Tree) override;

private:
	Direction getBfsMove(const sf::Vector2i& start,
		const sf::Vector2i& destination);
};

