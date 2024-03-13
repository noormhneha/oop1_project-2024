#include "Screens.h"

// Constructor to initialize the screen elements
Screens::Screens() {
    setOpeningGame();
    setCounters();
    setBackground();
    setSoundTexture();
    setSoundBuffers();
    setMenu();
    setInformation();
    setStory();
}

// Function to set the background image
void Screens::setBackground() {
    m_backgroundTexture.loadFromFile("Tom&Jerry.png");
    m_backgroundSprite.setScale((float)(40 * P_SIZE) / m_backgroundTexture.getSize().x,
        (float)(22 * P_SIZE) / m_backgroundTexture.getSize().y);
    m_backgroundSprite.setTexture(m_backgroundTexture);
}

// Function to set the counters
void Screens::setCounters() {
    for (size_t i = 0; i < 5; i++) {
        m_countersTexture[i].loadFromFile(std::to_string(i + 1) + ".png");
        m_countersSprite[i].setTexture(m_countersTexture[i]);
        m_countersSprite[i].setScale(64.0f / m_countersTexture[i].getSize().x, 64.0f / m_countersTexture[i].getSize().y);
        m_countersSprite[i].setPosition(620, 600);
    }
}

// Function to set the opening game image
void Screens::setOpeningGame() {
    m_startTheGame.loadFromFile("startGame.png");
    m_startTheGameSprite.setTexture(m_startTheGame);
    m_startTheGameSprite.setOrigin(m_startTheGameSprite.getLocalBounds().width / 2, m_startTheGameSprite.getLocalBounds().height / 2);
    m_startTheGameSprite.setPosition(640, 350);
}

// Function to set the menu texts
void Screens::setMenu() {
    m_font.loadFromFile("sectionFont.ttf");
    if (!m_font.loadFromFile("sectionFont.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        exit(EXIT_FAILURE);
    }

    unsigned int fontSize = 40;
    m_newGameText = createText("New Game", m_font, fontSize);
    m_tableText = createText("Scores", m_font, fontSize);
    m_exitText = createText("Exit", m_font, fontSize);
}

// Function to set the information text
void Screens::setInformation() {
    std::ifstream file("information.txt");
    if (!file.is_open()) {
        std::cerr << "Cannot open Information file\n";
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        m_informationTextStr += line + "\n";
    }

    m_skipTexture.loadFromFile("skip.png");
    m_skipSprite.setTexture(m_skipTexture);
    m_skipSprite.setPosition(1200, 40);
    m_skipSprite.setScale(32 / m_skipSprite.getGlobalBounds().width, 32 / m_skipSprite.getGlobalBounds().height);
}

// Function to set the sound textures
void Screens::setSoundTexture() {
    m_soundOn.loadFromFile("soundOn.png");
    m_soundOnSprite.setTexture(m_soundOn);
    m_soundOff.loadFromFile("soundOff.png");
    m_soundOffSprite.setTexture(m_soundOff);

    m_soundOnSprite.setScale(sf::Vector2f(((float)P_SIZE / m_soundOnSprite.getGlobalBounds().width),
        ((float)P_SIZE / m_soundOnSprite.getGlobalBounds().height)));
    m_soundOnSprite.setPosition(20, 20);

    m_soundOffSprite.setScale(sf::Vector2f(((float)P_SIZE / m_soundOffSprite.getGlobalBounds().width),
        ((float)P_SIZE / m_soundOffSprite.getGlobalBounds().height)));

    m_soundOffSprite.setPosition(20, 20);
}

// Function to create text with given parameters
sf::Text Screens::createText(const std::string& str, const sf::Font& font, unsigned int fontSize) {
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(fontSize);
    return text;
}

// Function to set sound buffers
void Screens::setSoundBuffers() {
    std::vector<std::string> sounds = { "opening.wav" , "click.wav",  "tomRunning.wav" , "catch.wav" , "tom-lose.wav" };
    for (size_t i = 0; i < SOUNDS; i++) {
        m_soundBuffer[i].loadFromFile(sounds.at(i));
        m_sound[i].setBuffer(m_soundBuffer[i]);
    }
}

// Function to set the story images
void Screens::setStory() {
    for (size_t i = 0; i < STORY_SCREENS; i++) {
        m_storyTexture[i].loadFromFile("story" + std::to_string(i + 1) + ".png");
        m_storySprite[i].setScale((float)(40 * P_SIZE) / m_storyTexture[i].getSize().x,
            (float)(22 * P_SIZE) / m_storyTexture[i].getSize().y);
        m_storySprite[i].setTexture(m_storyTexture[i]);
    }
    m_storyInfoIconTexture.loadFromFile("story.png");
    m_storyInfoIconSprite.setTexture(m_storyInfoIconTexture);
    m_storyInfoIconSprite.setScale(sf::Vector2f(((float)P_SIZE / m_storyInfoIconSprite.getGlobalBounds().width),
        ((float)P_SIZE / m_storyInfoIconSprite.getGlobalBounds().height)));
    m_storyInfoIconSprite.setPosition(20, 645);
}

// Function to handle the opening background
void Screens::OpeningBackground(sf::RenderWindow& window) {
    sf::Clock clock;
    int spriteIndex = 0;
    m_sound[0].play();
    while (true) {
        float elapsedTime = clock.getElapsedTime().asSeconds();
        drawStarter(window, spriteIndex);
        if (elapsedTime >= 1.0f) {
            spriteIndex++;
            clock.restart();
        }
        if (spriteIndex == 5) {
            break;
        }
    }
}

// Function to get the font
sf::Font Screens::getFont() const {
    return m_font;
}

// Function to draw information on the screen
void Screens::drawInformation(sf::RenderWindow& window) const {
    sf::Text text;
    text.setFont(m_font);
    text.setString(m_informationTextStr);
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::Black);
    text.setPosition(20, 20);
    window.draw(m_skipSprite);
    window.draw(text);
}

// Function to draw the story images
void Screens::drawStory(sf::RenderWindow& window, unsigned int i, float interpolation, int animationIndex) {
    if (interpolation >= 1.0f) {
        interpolation = 1.0f;
    }

    sf::Uint8 alpha = static_cast<sf::Uint8>(255 * interpolation);
    float rotation = 360.0f * interpolation;

    switch (animationIndex) {
    case 0:
        m_storySprite[i].setColor(sf::Color(255, 255, 255, alpha));
        break;
    case 1:
        m_storySprite[i].setRotation(rotation);
        break;
    default:
        m_storySprite[i].setColor(sf::Color(255, 255, 255, alpha));
        break;
    }
    if (i < STORY_SCREENS) window.draw(m_storySprite[i]);
}

// Function to draw the information button
void Screens::drawInfoButton(sf::RenderWindow& window) const {
    window.draw(m_storyInfoIconSprite);
}

// Function to draw the starter screen
void Screens::drawStarter(sf::RenderWindow& window, int spriteIndex) const {
    window.clear();
    window.draw(m_startTheGameSprite);
    if (spriteIndex < 5) {
        window.draw(m_countersSprite[4 - spriteIndex]);
    }
    window.display();
}

// Function to draw the background
void Screens::drawBackground(sf::RenderWindow& window) {
    window.draw(m_backgroundSprite);
}

// Function to draw the starter section
void Screens::drawStarterSection(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("sectionFont.ttf");
    if (!font.loadFromFile("sectionFont.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    unsigned int fontSize = 40;
    m_newGameText = createText("New Game", font, fontSize);
    m_tableText = createText("Information", font, fontSize);
    m_exitText = createText("Exit", font, fontSize);

    drawTextInStarter(m_newGameText, window, 1);
    drawTextInStarter(m_tableText, window, 2);
    drawTextInStarter(m_exitText, window, 3);
}

// Function to draw the sound button
void Screens::drawSoundButton(sf::RenderWindow& window, bool flag) {
    if (flag) {
        window.draw(m_soundOffSprite);
    }
    else {
        window.draw(m_soundOnSprite);
    }
}

// Function to draw text in the starter section
void Screens::drawTextInStarter(sf::Text& text, sf::RenderWindow& window, int i) {
    sf::Vector2u windowSize = window.getSize();
    float xPos = (windowSize.x - text.getLocalBounds().width) / 2;
    text.setPosition(xPos, 100 + float(120 * i));
    window.draw(text);
}

// Function to play or pause sound
void Screens::playPauseSound(int i, bool mute) {
    mute ? m_sound[i].stop() : m_sound[i].play();
}

// Function to check which button is pressed
Buttons Screens::checkButtons(int x, int y) {
    if (y >= 20 && y <= 55) {
        if (x >= 15 && x <= 55) {
            return SOUND;
        }
        else if (x >= 1180 && x <= 1220) {
            return SKIP;
        }
    }
    else if (y >= 220 && y <= 260) {
        if (x >= 550 && x <= 725) {
            return NEW_GAME;
        }
    }
    else if (y >= 340 && y <= 380) {
        if (x >= 540 && x <= 740) {
            return INFORMATION;
        }
    }
    else if (y >= 460 && y <= 500) {
        if (x >= 605 && x <= 670) {
            return EXIT;
        }
    }
    else if (y >= 640 && y <= 680) {
        if (x >= 15 && x <= 55) {
            return STORY;
        }
    }
    return NILL;
}
