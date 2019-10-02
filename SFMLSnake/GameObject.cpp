#include "GameObject.h"

GameObject::GameObject() {
    
}

GameObject::GameObject(int x, int y) {
    this->x = x;
    this->y = y;
}

GameObject::~GameObject() {
}


/*-- PLAYER --*/
Player::Player() {
    this->texture.loadFromFile("images/Head.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(CELL_SIZE / 2, CELL_SIZE / 2);
    this->sprite.setPosition(CELL_SIZE / 2, CELL_SIZE / 2);

    this->bodyTexture.loadFromFile("images/Body.png");
    this->addBodyPiece();

    this->setDirection(RIGHT); //Starting direction for the snake
}

Player::~Player() {
}

void Player::addBodyPiece() {
    sf::Sprite sprite(this->bodyTexture);
    this->body.push_back(sprite);
}

void Player::move(float dt) {
    float oldX = this->sprite.getPosition().x;
    float oldY = this->sprite.getPosition().y;

    float movement = PLAYER_SPEED * dt;

    float newPos = 0;

    switch (direction) {
        case LEFT:
            newPos = oldX - movement;
            this->sprite.setPosition(oldX - movement, oldY);
            //this->x += movement;
            break;
        case RIGHT:
            this->sprite.setPosition(oldX + movement, oldY);
            //this->x -= movement;
            break;
        case UP:
            this->sprite.setPosition(oldX, oldY - movement);
            //this->y -= movement;
            break;
        case DOWN:
            this->sprite.setPosition(oldX, oldY + movement);
            //this->y += movement;
            break;
        default:
            break;
    }
    //this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

void Player::setDirection(Direction newDir) {

    switch (newDir) {
        case LEFT:
            this->direction = newDir;
            this->sprite.setRotation(90);
            break;
        case RIGHT:
            this->direction = newDir;
            this->sprite.setRotation(-90);
            break;
        case UP:
            this->direction = newDir;
            this->sprite.setRotation(180);
            break;
        case DOWN:
            this->direction = newDir;
            this->sprite.setRotation(0);
            break;
        default:
            break;
    }
}

bool Player::checkOutOfBounds() {
    bool outOfBounds = false;
    sf::FloatRect playerBounds = this->sprite.getGlobalBounds();

    if (playerBounds.left < 0) { //Outside left bound of the window
        outOfBounds = true;
    } else if (playerBounds.left + playerBounds.width > WINDOW_WIDTH) { //Outside right bound of the window
        outOfBounds = true;
    } else if (playerBounds.top < 0) { //Outside top bound of the window
        outOfBounds = true;
    } else if (playerBounds.top + playerBounds.height > WINDOW_HEIGHT) { //Outside bottom bound of the window
        outOfBounds = true;
    }

    return outOfBounds;
}

/*-- FRUIT --*/
Fruit::Fruit() {
    this->texture.loadFromFile("images/Fruit.png");
    this->sprite.setTexture(this->texture);
}

Fruit::~Fruit() {
}

void Fruit::setPosition(float newX, float newY) {
    this->sprite.setPosition(newX, newY);
}