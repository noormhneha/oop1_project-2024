#pragma once
#include <SFML\Graphics.hpp>
//#include "Utilities.h"

class LevelStatus
{
public:
	LevelStatus();
	void draw(sf::RenderWindow& window, int life, int score, int level, int timer, sf::Vector2f BoardSize, sf::Font);

private:
	sf::Text m_statusBar;
	//sf::Font m_font; //????
	sf::Texture m_lifeTexture;
	sf::Sprite m_lifeSprite;
};
