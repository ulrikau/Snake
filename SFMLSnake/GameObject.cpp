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

    this->addBodyPiece(0, 0); //Add second piece of body
    this->addBodyPiece(this->bodyTexture.getSize().x, 0); //Add first piece of body
    this->addBodyPiece(this->bodyTexture.getSize().x * 2, 0); //Add head

    this->setDirection(RIGHT); //Starting direction for the snake
}

Player::~Player() {
}

void Player::addBodyPiece() {
    addBodyPiece(0, 0);
}

void Player::addBodyPiece(float x, float y) {
    sf::Sprite sprite(this->bodyTexture);
    sprite.setPosition(x, y);
    //sprite.setOrigin(this->bodyTexture.getSize().x / 2, this->bodyTexture.getSize().y / 2); //Set origin to the middle of the body sprite
    this->body.insert(this->body.begin(), sprite);
}

void Player::updateBodyPosition(float dx, float dy) {
    /*for (int i = 0; i < this->body.size(); i++) {
        this->body.at(i).setPosition(this->body.at(i).getPosition().x + dx, this->body.at(i).getPosition().y + dy);
    }*/

    //this->body.at(0).setPosition(this->body.at(i).getPosition().x + dx, this->body.at(i).getPosition().y + dy);

    for (auto& part : this->body) {
        part.setPosition(part.getPosition().x + dx, part.getPosition().y + dy);
    }

    /*for (sf::Sprite part : this->body) {
        part.setPosition(part.getPosition().x + dx, part.getPosition().y + dy);
    }*/
}

void Player::move(float dt) {
    float oldX = body[0].getPosition().x;
    float oldY = body[0].getPosition().y;

    float movement = PLAYER_SPEED * dt;

    switch (direction) {
        case LEFT:
            updateBodyPosition(-movement, 0);
            //this->body[0].setPosition(oldX - movement, oldY);
            break;
        case RIGHT:
            updateBodyPosition(movement, 0);
            /*this->body[0].setPosition(oldX + movement, oldY);
            this->body[1].setPosition(body[1].getPosition().x + movement, oldY);*/
            break;
        case UP:
            updateBodyPosition(0, -movement);
            //this->body[0].setPosition(oldX, oldY - movement);
            break;
        case DOWN:
            updateBodyPosition(0, movement);
            //this->body[0].setPosition(oldX, oldY + movement);
            break;
        default:
            break;
    }
}

void Player::setDirection(Direction newDir) {

    switch (newDir) {
        case LEFT:
            this->direction = newDir;
            break;
        case RIGHT:
            this->direction = newDir;
            break;
        case UP:
            this->direction = newDir;
            break;
        case DOWN:
            this->direction = newDir;
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

    return false;// outOfBounds;
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