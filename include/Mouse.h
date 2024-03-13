#pragma once
#include "Movable.h"

enum { INCREASE_TIME, STOP_CATS, ADD_LIFE };

class Mouse : public Movable
{
public:
	Mouse();

	
	void setDirection(sf::Keyboard::Key direction);


	void move(float passedTime, sf::Vector2f boardSize);
	bool getMouseState() const;
	void setMouseState();

	int getScore()const;
	void setScore(const int& score);

	int getLife()const;
	void setLife(const int& Life);

	int getKeysNumber()const;
	void setKeysNumber(const int& number);

	int getMoreTime()const;

	int getCheeseCounter()const;
	void setCheeseCounter(const int&);

	void decTimerCatsStop();
	int getTimerCatsStop()const;


	void setStoppingPower(const bool&);
	bool getStoppingPower()const;



	virtual void collide(Icon*) {};
	virtual void collide(Mouse*) {};
	virtual void collide(Cat* object);
	virtual void collide(Cheese* object);
	virtual void collide(Wall* object); 
	virtual void collide(Door* object);
	virtual void collide(Key* object); 
	virtual void collide(Gift* object); 

private:
	int m_score = 0;
	int m_life = 3;
	int m_numberKeys = 0;
	
	int m_moreTime = 0;
	int m_countCheese = 0;

	int m_timerCatsStop = 0;

	bool m_isArrested = false;
	bool m_stoppingPower = false;
	
};

