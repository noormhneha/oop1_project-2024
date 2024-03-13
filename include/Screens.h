#pragma once

#include "Board.h"

const int SOUNDS = 5;
const int STORY_SCREENS = 8;

enum Sounds {OPEN , CLICK, TOMRUN, CATCH};

enum Buttons {
	NILL,
	SOUND,
	NEW_GAME,
	INFORMATION,
	EXIT,
	STORY, 
	SKIP
};

class Screens
{
public:
	Screens();

	//void draw(sf::RenderWindow&) const;
	void drawBackground(sf::RenderWindow&);
	void drawStarterSection(sf::RenderWindow&);
	void drawSoundButton(sf::RenderWindow&, bool);
	void drawInformation(sf::RenderWindow&) const;
	void drawStory(sf::RenderWindow&, unsigned int, float, int);
	void drawInfoButton(sf::RenderWindow& window) const;

	void playPauseSound(int, bool);
	Buttons checkButtons(int x, int y);
	void OpeningBackground(sf::RenderWindow&);

	sf::Font getFont() const;


private:
	void drawStarter(sf::RenderWindow& window, int spriteIndex) const;
	sf::Text createText(const std::string&, const sf::Font&, unsigned int);
	void drawTextInStarter(sf::Text&, sf::RenderWindow&, int);

	void setBackground();
	void setCounters();
	void setOpeningGame();
	void setMenu();
	void setInformation();
	void setSoundTexture();
	void setSoundBuffers();
	void setStory();

	sf::Texture m_countersTexture[5];
	sf::Sprite m_countersSprite[5];

	sf::Texture m_backgroundTexture; // Texture for the background
	sf::Sprite m_backgroundSprite; // Sprite for the background

	sf::Texture m_startTheGame;
	sf::Sprite m_startTheGameSprite;

	sf::Text m_newGameText, m_tableText, m_exitText;

	std::string m_informationTextStr;
	sf::Text m_informationText;

	sf::Texture m_soundOn, m_soundOff;
	sf::Sprite m_soundOnSprite, m_soundOffSprite;

	sf::Texture m_skipTexture;
	sf::Sprite m_skipSprite;

	sf::SoundBuffer m_soundBuffer[SOUNDS];
	sf::Sound m_sound[SOUNDS];

	sf::Font m_font;

	sf::Texture m_storyTexture[STORY_SCREENS];
	sf::Sprite m_storySprite[STORY_SCREENS];

	sf::Texture m_storyInfoIconTexture;
	sf::Sprite m_storyInfoIconSprite;
};

