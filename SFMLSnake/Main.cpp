#include <random>
#include <unordered_map>

#include "SFML/Graphics.hpp"

#include "Constants.h"
#include "GameObject.h"

bool checkCollision(sf::FloatRect object1, sf::FloatRect object2) {
    return object1.intersects(object2);
}

int main(int argc, char** argv) {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
    window.setFramerateLimit(60);
    sf::Event event;

    srand(time(NULL));

    std::uniform_int_distribution<int> randomXCell(0, WINDOW_WIDTH / CELL_SIZE - 1); //Remove 1 to avoid getting fruits right outside the edge of the window.
    std::uniform_int_distribution<int> randomYCell(0, WINDOW_HEIGHT / CELL_SIZE - 1);
    std::random_device rand;
    std::mt19937 randomNumbers(rand()); 

    sf::Clock clock;
    float lastTime = 0;

    Player* player = new Player();

    Fruit* fruit = new Fruit();
    float fruitX = randomXCell(randomNumbers) * CELL_SIZE;
    float fruitY = randomYCell(randomNumbers) * CELL_SIZE;
    fruit->setPosition(fruitX, fruitY);

    int score = 0;
    bool gameOver = false;

    sf::Font font;
    font.loadFromFile("OpenSans-Regular.ttf");
    sf::Text text("Game over! Score: " + std::to_string(score), font, 12);

    /*sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("images/Background.png");
    sf::Sprite background(backgroundTexture);*/

    while (window.isOpen()) {
        float newTime = clock.getElapsedTime().asSeconds();
        float dt = newTime - lastTime;
        lastTime = newTime;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
            }

            if (event.type == sf::Event::EventType::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    player->setDirection(LEFT);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    player->setDirection(RIGHT);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    player->setDirection(UP);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    player->setDirection(DOWN);
                }
            }
        }

        if (!gameOver) {
            player->move(dt);

            if (checkCollision(player->sprite.getGlobalBounds(), fruit->sprite.getGlobalBounds())) {
                score++;

                int randX = randomXCell(randomNumbers);
                int randY = randomYCell(randomNumbers);
                float newX = randX * CELL_SIZE;
                float newY = randY * CELL_SIZE;
                //text.setString("randX: " + std::to_string(randX) + "\n randY: " + std::to_string(randY) + "\n newX: " + std::to_string(newX) + "\n newY: " + std::to_string(newY));
                fruit->setPosition(newX, newY);
            }

            if (player->checkOutOfBounds()) {
                gameOver = true;
            }
        }

        window.clear(sf::Color(125, 155, 224, 255));
        //window.draw(background);
        window.draw(fruit->sprite);
        window.draw(player->body[0]);

        if (gameOver) {
            text.setString("Game over! Score: " + std::to_string(score));
            window.draw(text);
        }

        window.display();
    }
}