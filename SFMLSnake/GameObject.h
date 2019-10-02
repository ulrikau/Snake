#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Constants.h"

enum Direction
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
    const unsigned int PLAYER_SPEED = CELL_SIZE * 4;

public:
    sf::Texture bodyTexture;
    std::vector<sf::Sprite> body;
    Direction direction;

    Player();
    ~Player();

    void addBodyPiece();
    void move(float dt);
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