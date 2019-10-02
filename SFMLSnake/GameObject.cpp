#include "GameObject.h"

GameObject::GameObject() {
    
}

GameObject::~GameObject() {
}


/*-- PLAYER --*/
Player::Player() {
    /*this->texture.loadFromFile("images/Head.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(CELL_SIZE / 2, CELL_SIZE / 2);
    this->sprite.setPosition(CELL_SIZE / 2, CELL_SIZE / 2);*/

    this->bodyTexture.loadFromFile("images/Body.png");

    this->addBodyPiece(); //Add head
    this->addBodyPiece(); //Add first piece of body

    this->setDirection(RIGHT); //Starting direction for the snake
}

Player::~Player() {
}

void Player::addBodyPiece() {
    sf::Sprite sprite(this->bodyTexture);
    this->sprite.setOrigin(CELL_SIZE / 2, CELL_SIZE / 2); //Set origin to the middle of the body sprite
    this->body.push_back(sprite);
}

void Player::move(float dt) {
    float oldX = body[0].getPosition().x;
    float oldY = body[0].getPosition().y;

    float movement = PLAYER_SPEED * dt;

    switch (direction) {
        case LEFT:
            this->body[0].setPosition(oldX - movement, oldY);
            break;
        case RIGHT:
            this->body[0].setPosition(oldX + movement, oldY);
            break;
        case UP:
            this->body[0].setPosition(oldX, oldY - movement);
            break;
        case DOWN:
            this->body[0].setPosition(oldX, oldY + movement);
            break;
        default:
            break;
    }
}

void Player::setDirection(Direction newDir) {

    switch (newDir) {
        case LEFT:
            this->direction = newDir;
            //this->sprite.setRotation(90);
            break;
        case RIGHT:
            this->direction = newDir;
            //this->sprite.setRotation(-90);
            break;
        case UP:
            this->direction = newDir;
            //this->sprite.setRotation(180);
            break;
        case DOWN:
            this->direction = newDir;
            //this->sprite.setRotation(0);
            break;
        default:
            break;
    }
}

sf::Sprite Player::getHead() {
    return body[0];
}

bool Player::checkOutOfBounds() {
    bool outOfBounds = false;
    sf::FloatRect playerBounds = this->body[0].getGlobalBounds();

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