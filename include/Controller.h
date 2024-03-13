#pragma once

#include "Screens.h"
#include "LevelStatus.h"
#include <thread>

class Controller {
public:
    Controller();  // Constructor
    ~Controller(); // Destructor

private:
    void runGame();                // Method to run the game loop
    void startTheGame();           // Method to start the game
    void handleMainEvents();       // Method to handle events on the main page
    void handleLevelEvents();      // Method to handle events during gameplay
    bool levelEnded(const Board& board, int levelNum); // Method to check if the level has ended
    void buttonReleased(sf::Event); // Method to handle button releases
    void openLevel();              // Method to open a level
    void gameStory();              // Method to display the game story
    void openInformation();        // Method to open the information screen
    int levelsInGame(std::string str); // Method to determine the number of levels in the game
    void checkCollision(Movable* character, Direction direction, Board& board); // Method to check collisions between objects
    void stopCat();                // Method to stop the cat
    void moveMovable(float passedTime, Board& board); // Method to move movable objects
    bool catchMouse(Cat* cat);     // Method to catch the mouse
    void returnStartingPosition(); // Method to return to the starting position
    bool isMouseDied();            // Method to check if the mouse has died
    void movableDraw(float passedTime); // Method to draw movable objects

    bool m_mainPage = true;        // Flag for the main page
    bool m_newGame = false;        // Flag for starting a new game
    bool m_scoreTable = false;     // Flag for displaying the score table
    bool m_mute = false;           // Flag for muting/unmuting the game
    bool m_information = false;    // Flag for displaying information
    bool m_storyShowed = false;    // Flag for displaying the game story
    bool m_nowMove = false;        // Flag for indicating movement

    sf::RenderWindow m_window;     // Main window
    sf::RenderWindow m_levelWindow; // Level window
    Screens m_screens;              // Screens object
    Mouse m_mouse;                  // Mouse object
    std::vector<std::unique_ptr<Cat>> m_cats; // Vector of cats
    LevelStatus m_player;           // Level status object
    int m_gameTime;                 // Game time
    int m_count_levels = 0;         // Number of levels
};

