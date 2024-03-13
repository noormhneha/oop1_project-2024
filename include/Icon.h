#pragma once

#include <vector>
#include "Utilities.h"


class Mouse;
class Cat;
class Cheese;
class Wall;
class Door;
class Key;
class Gift;


const int P_SIZE = 32; 
const int SCORE_CHEESE = 10;
const int SCORE_OREN_DOOR = 2;
const int SCORE_GIFT = 5;
const int SCORE_LEVEL = 25;
const int SCORE_CAT = 5;

enum Characters { MOUSE, CAT, CHEESE, WALL, KEY, DOOR, HEART_GIFT, CAT_GIFT, TIME_GIFT};

class Icon {
public:
	Icon() {};
	virtual ~Icon(){};

	virtual void collide(Icon* object)	=	0;
	virtual void collide(Mouse* object)	=	0;
	virtual void collide(Cat* object)	=	0;
	virtual void collide(Cheese*object) =	0;
	virtual void collide(Wall* object)	=	0;
	virtual void collide(Door* object)	=	0;
	virtual void collide(Key* object)	=	0;
	virtual void collide(Gift* object)	=	0;

	//virtual void draw(sf::RenderWindow& window) = 0;//??

protected:

	sf::Sprite m_sprite;
	//Characters m_Character; //?
};

