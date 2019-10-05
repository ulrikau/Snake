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

    this->setDirection(Direction::RIGHT); //Starting direction for the snake
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
    for (auto& part : this->body) {
        part.setPosition(part.getPosition().x + dx, part.getPosition().y + dy);
    }
}

void Player::move(float dt) {

	timeSinceLastMove += dt;
	float timestep = 1.f/20.f;// 1.f / (float)PLAYER_SPEED;

	if (timeSinceLastMove >= timestep) {

		float movement = 1.f/2.f * (float)CELL_SIZE;

		switch (direction) {
		case Direction::LEFT:
			this->addBodyPiece(body.at(0).getPosition().x - movement, body.at(0).getPosition().y);
			//updateBodyPosition(-movement, 0);
			break;
		case Direction::RIGHT:
			this->addBodyPiece(body.at(0).getPosition().x + movement, body.at(0).getPosition().y);
			//updateBodyPosition(movement, 0);
			break;
		case Direction::UP:
			this->addBodyPiece(body.at(0).getPosition().x, body.at(0).getPosition().y - movement);
			//updateBodyPosition(0, -movement);
			break;
		case Direction::DOWN:
			this->addBodyPiece(body.at(0).getPosition().x, body.at(0).getPosition().y + movement);
			//updateBodyPosition(0, movement);
			break;
		default:
			break;
		}

		body.pop_back();
		timeSinceLastMove -= timestep;
	}
}

void Player::setDirection(Direction newDir) {

    switch (newDir) {
        case Direction::LEFT:
            this->direction = newDir;
            break;
        case Direction::RIGHT:
            this->direction = newDir;
            break;
        case Direction::UP:
            this->direction = newDir;
            break;
        case Direction::DOWN:
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