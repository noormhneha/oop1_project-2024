#pragma once

#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "NonMovable.h"
#include "Cat.h"
#include "Mouse.h"

// Symbols 
const char MOUSE_CH = '%';
const char CAT_CH = '^';
const char DOOR_CH = 'D';
const char WALL_CH = '#';
const char KEY_CH = 'F';
const char CHEESE_CH = '*';
const char REMOVE_CAT_GIFT_CH = '-';
const char ADD_HEART_GIFT_CH = '+';
const char ADD_TIME_GIFT_CH = '$';
const char ROAD_CH = ' ';

class Board {
public:
    // Constructor
    Board(Mouse& mouse, std::vector<std::unique_ptr<Cat>>& cats, const int& numberOfLevel);

    // Function to get the size of the board
    sf::Vector2f getBoardSize();

    // Function to draw the board on a render window
    void drawBoard(sf::RenderWindow& window);

    // Function to read the level from a file
    void readLevel(Mouse& mouse, std::vector<std::unique_ptr<Cat>>& cats, const int& numberOfLevel);

    // Function to set the mouse position on the board
    void setMouse(Mouse& mouse, sf::Vector2f position);

    // Function to set the cat position on the board
    void setCat(std::vector<std::unique_ptr<Cat>>& cats, sf::Vector2f position);

    // Function to get the cheese counter
    int getCheeseCounter() const;

    // Function to get the number of cats
    int getCatsNumber() const;

    // Function to get the character at a specific position on the board
    NonMovable* getCharacters(sf::Vector2f position, Direction direction);

    // Function to get a reference to the board map
    std::vector<std::vector<std::unique_ptr<NonMovable>>>& getMap();

    // Function to check if a position is out of the map bounds
    bool checkOutOfMap(sf::Vector2f position);

    // Function to get the time
    sf::Time getTime() const;

    // Function to get the number of the current level
    int getNumberOfLevel() const;

    // Function to perform a breadth-first search algorithm
    std::vector<std::vector<sf::Vector3i>> bfsAlgo(sf::Vector2i start);

private:
    // Function to search for characters around a center position
    std::vector<sf::Vector2i> search(const sf::Vector2i center);

    // Function to open the level file
    void openFile();

    // Function to set the board size
    void setBoardSize();

    // Function to push characters to the map
    void pushToMap(const char&, size_t&, size_t&, Mouse&, std::vector<std::unique_ptr<Cat>>&);

    // Vector to store the board map
    std::vector<std::vector<std::unique_ptr<NonMovable>>> m_board;

    // Input file stream for reading the level file
    std::ifstream m_file;

    // Variables to store the number of rows and columns in the board
    int m_row, m_col;

    // Variable to store the time
    sf::Time m_time;

    // Variables to store the number of the current level, the number of cats, and the number of cheese
    int m_numberOfLevel;
    int m_numberOfCats;
    int m_numberOfCheese;
};
