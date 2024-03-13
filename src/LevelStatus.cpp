#include "LevelStatus.h"

// Constructor to initialize the level status
LevelStatus::LevelStatus() {
	// Load the life texture from file
	m_lifeTexture.loadFromFile("life.png");
	// Set the texture for the life sprite
	m_lifeSprite.setTexture(m_lifeTexture);
	// Scale the life sprite to fit the display size
	m_lifeSprite.setScale(28.f / m_lifeTexture.getSize().x, 28.f / m_lifeTexture.getSize().y);
}

// Draw the level status on the window
void LevelStatus::draw(sf::RenderWindow& window, int life, int score, int level, int timer, sf::Vector2f BoardSize, sf::Font font) {
	// Construct the status string with relevant information
	std::string status = "Lives: \nScore " + std::to_string(score) +
		" in level " + std::to_string(level) + "\nTime Left " +
		std::to_string(timer) + "  Seconds";

	// Set up the status bar text
	m_statusBar.setPosition(20, BoardSize.x + 5.f);
	m_statusBar.setString(status);
	m_statusBar.setCharacterSize(20);
	m_statusBar.setFont(font);
	m_statusBar.setFillColor(sf::Color::Black);
	// Draw the status bar text on the window
	window.draw(m_statusBar);

	// Calculate the width of the status bar text
	float textWidth = m_statusBar.getLocalBounds().width;

	// Set the position of the life icon next to the status text
	m_lifeSprite.setPosition(textWidth, BoardSize.x + 2.f);

	// Draw the life icons based on the remaining lives
	for (int i = 0; i < life; i++) {
		window.draw(m_lifeSprite);
		m_lifeSprite.move(32 + 5, 0); // Move the life sprite to the right for the next life
	}
}
