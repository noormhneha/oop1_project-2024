#include "Mouse.h"
#include "Cheese.h"
#include "Door.h"
#include "Key.h"
#include "Gift.h"

Mouse::Mouse()
{
	// Initialize mouse sprite and position
	m_sprite.setTexture(*(Utilities::instance().getCharactersTexture(MOUSE)));
	m_sprite.setOrigin(m_sprite.getPosition());
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / (m_sprite.getGlobalBounds().height + P_SIZE)),
		((float)P_SIZE / (m_sprite.getGlobalBounds().width + P_SIZE))));
	SetPosition(m_sprite.getOrigin());
}

// Function to set direction of the mouse
void Mouse::setDirection(sf::Keyboard::Key direction) {
	switch (direction)
	{
	case sf::Keyboard::Left:
		m_newDirection = LEFT;
		break;
	case sf::Keyboard::Right:
		m_newDirection = RIGHT;
		break;
	case sf::Keyboard::Up:
		m_newDirection = UP;
		break;
	case sf::Keyboard::Down:
		m_newDirection = DOWN;
		break;
	}
}

// Function to move the mouse
void Mouse::move(float passedTime, sf::Vector2f boardSize)
{
	m_previousPostion = m_sprite.getPosition();

	float moveDistance = (REGULAR_SPEED * passedTime);

	if (isCentered(m_sprite.getPosition(), getCenter(m_sprite.getPosition())))
		m_direction = m_newDirection;
	moveDirection(moveDistance);

	if (!outOfBoard(boardSize))
		m_sprite.setPosition(getCenter(m_previousPostion));

	m_position = m_sprite.getPosition();
}

// Function to return the state of the mouse
bool Mouse::getMouseState() const
{
	return m_isArrested;
}

// Function to set the state of the mouse
void Mouse::setMouseState()
{
	m_isArrested = false;
}

// Function to get the score of the mouse
int Mouse::getScore() const
{
	return m_score;
}

// Function to set the score of the mouse
void Mouse::setScore(const int& score)
{
	m_score += score;
}

// Function to get the life of the mouse
int Mouse::getLife() const
{
	return m_life;
}

// Function to set the life of the mouse
void Mouse::setLife(const int& Life)
{
	m_life = Life;
}

// Function to get the number of keys held by the mouse
int Mouse::getKeysNumber() const
{
	return m_numberKeys;
}

// Function to set the number of keys held by the mouse
void Mouse::setKeysNumber(const int& number)
{
	m_numberKeys = number;
}

// Function to get the additional time
int Mouse::getMoreTime() const
{
	return m_moreTime;
}

// Function to get the timer for cat stoppage
int Mouse::getTimerCatsStop() const {
	return m_timerCatsStop;
}

// Function to decrease the timer for cat stoppage
void Mouse::decTimerCatsStop() {
	m_timerCatsStop--;
}

// Function to get the cheese counter
int Mouse::getCheeseCounter() const
{
	return m_countCheese;
}

// Function to set the cheese counter
void Mouse::setCheeseCounter(const int& s)
{
	m_countCheese = s;
}

// Function to set the stopping power of the mouse
void Mouse::setStoppingPower(const bool& s)
{
	m_stoppingPower = s;
}

// Function to check the stopping power of the mouse
bool Mouse::getStoppingPower() const
{
	return m_stoppingPower;
}

// Function to handle collision with cat
void Mouse::collide(Cat*)
{
	m_life--;
	m_isArrested = true;
	m_position = m_startPosition;
	//sound catch
}

// Function to handle collision with cheese
void Mouse::collide(Cheese* object)
{
	if (object->getStatus()) {
		setScore(SCORE_CHEESE);
		object->setStatus(false);
		m_countCheese++;
		// sound eat
	}
}

// Function to handle collision with wall
void Mouse::collide(Wall*)
{
	m_sprite.setPosition(m_previousPostion);
	//sound ouch
}

// Function to handle collision with door
void Mouse::collide(Door* object)
{
	if (m_numberKeys > 0 && object->getStatus()) {
		setScore(SCORE_OREN_DOOR);
		object->setStatus(false);
		m_numberKeys--;
	}
	if (object->getStatus())
		m_sprite.setPosition(m_previousPostion);
}

// Function to handle collision with key
void Mouse::collide(Key* object)
{
	if (object->getStatus()) {

		object->setStatus(false);
		m_numberKeys++;
	}
}

// Function to handle collision with gift
void Mouse::collide(Gift* object)
{
	TypeGift whichGift = object->getType();

	if (object->getStatus()) {
		switch (whichGift)
		{
		case ADD_HEART_GIFT:
			if (m_life < 3)
				m_life++;
			break;
		case HIDE_CAT_GIFT:
			m_timerCatsStop += 10;
			m_stoppingPower = true;
			break;
		case ADD_TIME_GIFT:
			m_moreTime += 10;
			break;
		default:
			break;
		}
		setScore(SCORE_GIFT);
		object->setStatus(false);
		//add sound
	}
}
