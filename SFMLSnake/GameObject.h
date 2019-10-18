#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Constants.h"

enum class Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class GameObject
{
protected:
    sf::Texture texture;

public:
    sf::Sprite sprite;

    GameObject();
    ~GameObject();
};

/* Class for the player snake */
class Player : public GameObject {
private:
    const int PLAYER_START_SIZE = 6;
    const int PLAYER_SPEED = 60; //Number of movements per second
    const int BODY_PARTS_PER_CELL = 6;
	float timeSinceLastMove = 0; //Time in seconds since the last move
    int partsLeftToGrow = 0;

public:
    sf::Texture bodyTexture;
    std::vector<sf::Sprite> body;
    Direction direction;

    Player();
    ~Player();

    void addBodyPiece(float x, float y);
    void updateBodyPosition(float dx, float dy);
    void move(float dt);
    void grow();
    void setDirection(Direction newDir);
    sf::Sprite getHead();
    bool checkOutOfBounds();
};

class Fruit : public GameObject {
public:
    Fruit();
    ~Fruit();

    void setPosition(float newX, float newY);
};