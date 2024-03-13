#include "Controller.h"             // Including necessary header file
#include <memory>

// Constructor for Controller class
Controller::Controller() {
    // Initialize count of levels and create the main game window
    m_count_levels = levelsInGame("Levels.txt");
    m_window.create(sf::VideoMode(40 * P_SIZE, 22 * P_SIZE), "Tom&Jerry - Catch me if you CAN!");

    m_screens.OpeningBackground(m_window);

    // Main game loop
    while (m_window.isOpen()) {
        m_window.clear();
        startTheGame();
        openInformation();
        openLevel();
        m_window.display();
        handleMainEvents();
    }
}

// Destructor for Controller class
Controller::~Controller() {
    m_window.close();      // Close main game window
    m_levelWindow.close(); // Close level window
}

// Function to run the game
void Controller::runGame()
{
    int level = 1;
    // Loop through levels until game ends or all levels completed
    for (; level <= m_count_levels && !m_mainPage; level++) {

        // Create board for current level
        Board board(m_mouse, m_cats, level);
        sf::Vector2f boardSize = board.getBoardSize();

        // Create level window based on board size
        m_levelWindow.create(sf::VideoMode(static_cast<unsigned int>(boardSize.y),
            static_cast<unsigned int>(boardSize.x + P_SIZE * 3)),
            "Level" + std::to_string(level));

        // Initialize clocks and timer for game time
        static sf::Clock clock;
        static sf::Clock timer;
        timer.restart();
        static sf::Time allottedTime = board.getTime();

        // Loop until level window closes or mouse dies
        while (m_levelWindow.isOpen() && !isMouseDied()) {
            m_levelWindow.clear(sf::Color(238, 232, 170)); // Clear level window

            // Calculate remaining game time
            m_gameTime = static_cast<int>(allottedTime.asSeconds() - timer.getElapsedTime().asSeconds()) + m_mouse.getMoreTime();

            // Check if level ended
            if (levelEnded(board, level)) break;

            // Handle events for level window
            handleLevelEvents();

            // Move movable objects and draw board
            sf::Time passedTime = clock.restart();
            float time = passedTime.asSeconds();
            moveMovable(time, board);
            board.drawBoard(m_levelWindow);

            // Draw player status
            m_player.draw(m_levelWindow, m_mouse.getLife(), m_mouse.getScore(), level, m_gameTime, board.getBoardSize(), m_screens.getFont());

            // Draw movable objects and display level window
            movableDraw(time);
            m_levelWindow.display();
        }

        // Check if level ended due to completion or time out
        if ((!isMouseDied()) && m_gameTime > 0) {
            m_mouse.setScore(SCORE_LEVEL + SCORE_CAT * board.getCatsNumber());
            m_mouse.setCheeseCounter(0);
        }
    }

    // If levels are not completed, return to main page
    if (level < m_count_levels) {
        m_window.create(sf::VideoMode(40 * P_SIZE, 22 * P_SIZE), "Tom&Jerry - Catch me if you CAN!");
        m_mainPage = true;
    }
}

// Function to open level
void Controller::openLevel() {
    if (m_newGame) {
        gameStory();
        m_window.close();
        runGame();
        m_newGame = false;
    }
}

// Function to handle main game events
void Controller::handleMainEvents() {
    if (auto event = sf::Event{}; m_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            // Close the window if 'X' button is clicked
            m_window.close();
            break;
        case sf::Event::MouseButtonReleased:
            // Handle mouse button release events
            buttonReleased(event);
            break;
        }
    }
}

// Function to handle level events
void Controller::handleLevelEvents() {
    if (auto event = sf::Event{}; m_levelWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            // Close level window and return to main page
            m_mainPage = true;
            m_levelWindow.close();
            break;
        case sf::Event::KeyReleased:
            // Handle key release events for movement
            if ((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::Right) ||
                (event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Down)) {

                if (!m_nowMove) {
                    m_mouse.setDirection(event.key.code);
                    m_nowMove = true;
                }

            }
            break;
        }
    }
}

// Function to check if level ended due to completion or time out
bool Controller::levelEnded(const Board& board, int levelNum) {
    if (m_mouse.getCheeseCounter() == board.getCheeseCounter()) {
        // If all cheese collected, end level and open next level
        m_levelWindow.clear();
        m_cats.clear();
        m_levelWindow.display();
        m_newGame = true;
        m_mainPage = false;
        m_screens.playPauseSound(4, false);
        m_levelWindow.close();
        return true;
    }
    else if (m_gameTime <= 0) {
        // If time out, return to main page
        m_newGame = false;
        m_mainPage = true;
        m_cats.clear();
        m_levelWindow.close();
        return true;
    }
    return false;
}

// Function to display starting game screen
void Controller::startTheGame() {
    if (m_window.isOpen() && m_mainPage && !m_information) {
        // Draw background and starter section on main window
        m_screens.drawBackground(m_window);
        m_screens.drawStarterSection(m_window);
        m_screens.drawSoundButton(m_window, m_mute);
    }
    if (m_storyShowed == true) {
        m_screens.drawInfoButton(m_window);   // Draw information button
    }
}

// Function to count levels in the game from a file
int Controller::levelsInGame(std::string str) {
    std::ifstream file(str);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    int lineCount = 0;
    while (std::getline(file, line)) {
        ++lineCount;
    }

    file.close();
    return lineCount;
}

// Function to check collision between movable object and other icons
void Controller::checkCollision(Movable* character, Direction direction, Board& board)
{
    Icon* icon = board.getCharacters(character->getNextDirection(direction), character->getDirection());
    if (icon != nullptr)
        icon->collide(character);
}

void Controller::stopCat() {
    // Use a static clock to measure real-time seconds
    static sf::Clock realTimeClock;
    static float realTimePassed = 0.0f;

    // Update real-time passed
    realTimePassed += realTimeClock.restart().asSeconds();

    // Decrease the timer every second
    while (realTimePassed >= 1.0f) {
        if (m_mouse.getTimerCatsStop() > 0)
            m_mouse.decTimerCatsStop();

        realTimePassed -= 1.0f; // Subtract one second
    }
}

// Function to move movable objects in the game
void Controller::moveMovable(float passedTime, Board& board)
{
    checkCollision(&m_mouse, m_mouse.getDirection(), board);
    if (m_nowMove) {
        m_mouse.move(passedTime, board.getBoardSize());
        m_nowMove = false;
    }

    // If mouse is caught, return all movable objects to starting position
    if (m_mouse.getMouseState()) {
        returnStartingPosition();
    }

    // Generate BFS tree for mouse movement
    std::vector<std::vector<sf::Vector3i>> Tree = board.bfsAlgo(sf::Vector2i((int)(m_mouse.getPosition().x / P_SIZE),
        (int)(m_mouse.getPosition().y / P_SIZE)));

    stopCat();

    // If stopping power is activated, check if timer expired
    if (m_mouse.getStoppingPower()) {
        if (m_mouse.getTimerCatsStop() <= 0)
            m_mouse.setStoppingPower(false);
    }
    else {
        // Move cats and check collision with mouse
        for (size_t i = 0; i < m_cats.size(); i++) {
            m_cats[i]->move(passedTime, board.getBoardSize(), Tree);
            m_screens.playPauseSound(2, false);
            checkCollision(m_cats[i].get(), m_cats[i].get()->getDirection(), board);
            if (catchMouse(m_cats[i].get()))
                m_mouse.collide(m_cats[i].get());
        }
    }
}

// Function to check if mouse is caught by a cat
bool Controller::catchMouse(Cat* cat)
{
    return (abs(m_mouse.getPosition().x - cat->getPosition().x) < P_SIZE &&
        abs(m_mouse.getPosition().y - cat->getPosition().y) < P_SIZE);
}

// Function to return all movable objects to starting position
void Controller::returnStartingPosition()
{
    for (size_t i = 0; i < m_cats.size(); i++)
        m_cats[i]->SetPosition(m_cats[i]->getStartPosition());

    m_mouse.SetPosition(m_mouse.getStartPosition());
    m_mouse.setMouseState();
}

// Function to check if mouse is dead
bool Controller::isMouseDied()
{
    return m_mouse.getLife() <= 0 ? true : false;
}

// Function to draw movable objects
void Controller::movableDraw(float passedTime)
{
    m_mouse.draw(m_levelWindow, passedTime);
    for (size_t i = 0; i < m_cats.size(); i++)
    {
        m_cats[i]->draw(m_levelWindow, passedTime);
    }
}

// Function to handle button releases
void Controller::buttonReleased(sf::Event event) {
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;

    Buttons buttonId = m_screens.checkButtons(x, y);

    switch (buttonId) {
    case SOUND:
        // Toggle sound button
        m_screens.playPauseSound(1, false); // play click
        m_mute = !m_mute;
        m_screens.drawSoundButton(m_window, m_mute);
        m_screens.playPauseSound(0, m_mute);
        break;
    case NEW_GAME:
        // Start new game
        m_screens.playPauseSound(1, false); // play click
        m_mainPage = false;
        m_newGame = true;
        break;
    case INFORMATION:
        // Display information screen
        m_screens.playPauseSound(1, false); // play click
        m_information = true;
        break;
    case EXIT:
        // Exit game
        m_screens.playPauseSound(1, false); // play click
        m_mainPage = true;
        m_window.close();
        break;
    case STORY:
        // Display game story
        if (m_storyShowed) {
            m_screens.playPauseSound(1, false); // play click
            m_storyShowed = false;
            gameStory();
        }
        break;
    case SKIP:
        // Skip information screen
        if (m_information) {
            m_screens.playPauseSound(1, false); // play click
            startTheGame();
            m_information = false;
            m_mainPage = true;
        }
        break;
    case NILL: default:
        break;
    }
}

// Function to display game story
void Controller::gameStory() {
    int i = 0;
    float transitionDuration = 0.5f; // Transition duration in seconds
    sf::Clock transitionClock;

    while (m_window.isOpen() && i != STORY_SCREENS && !m_storyShowed) {
        m_window.clear();
        if (auto event = sf::Event{}; m_window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonReleased) {
                m_screens.playPauseSound(1, false); // play click
                i++; // Move to the next screen after transition
                transitionClock.restart();
            }
        }
        float interpolation = transitionClock.getElapsedTime().asSeconds() / transitionDuration;
        // Draw the current story screen
        m_screens.drawStory(m_window, i, interpolation, i % 2);
        m_window.display();
    }
    m_storyShowed = true;
}

// Function to display information screen
void Controller::openInformation() {
    if (m_information && m_mainPage) {
        m_screens.drawBackground(m_window);
        m_screens.drawInformation(m_window);
    }
}
