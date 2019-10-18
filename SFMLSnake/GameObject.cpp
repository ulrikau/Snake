#include "GameObject.h"

GameObject::GameObject() {
    
}

GameObject::~GameObject() {
}


/*-- PLAYER --*/
Player::Player() {
    //this->texture.loadFromFile("images/Head.png");

    this->bodyTexture.loadFromFile("images/Body.png");

    for (int i = 0; i < PLAYER_START_SIZE; i++) {
        this->addBodyPiece(this->bodyTexture.getSize().x / BODY_PARTS_PER_CELL * i, 0);
    }

    this->setDirection(Direction::RIGHT); //Starting direction for the snake
}

Player::~Player() {
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
	float timestep = 1.f / PLAYER_SPEED;

	if (timeSinceLastMove >= timestep) {

		float movement = 1.f/BODY_PARTS_PER_CELL * (float)CELL_SIZE;

		switch (direction) {
		case Direction::LEFT:
			this->addBodyPiece(body.at(0).getPosition().x - movement, body.at(0).getPosition().y);
			break;
		case Direction::RIGHT:
			this->addBodyPiece(body.at(0).getPosition().x + movement, body.at(0).getPosition().y);
			break;
		case Direction::UP:
			this->addBodyPiece(body.at(0).getPosition().x, body.at(0).getPosition().y - movement);
			break;
		case Direction::DOWN:
			this->addBodyPiece(body.at(0).getPosition().x, body.at(0).getPosition().y + movement);
			break;
		default:
			break;
		}

        if (partsLeftToGrow > 0) {
            partsLeftToGrow--;
        } else {
            body.pop_back();
        } 
		
		timeSinceLastMove -= timestep;
	}
}

void Player::grow() {
    partsLeftToGrow += BODY_PARTS_PER_CELL;
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