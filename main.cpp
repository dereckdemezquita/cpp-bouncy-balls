
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "modules/Vec2.h"
#include "modules/Ball.h"

int main() {
    // create struct with width and height for storing dimensions
    struct {
        uint width = 800;
        uint height = 800;
    } window_dim;

    sf::RenderWindow window(sf::VideoMode(window_dim.width, window_dim.height), "cpp-bouncy-balls", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    window.setFramerateLimit(200);

    struct {
        float radius = 5;
        float elasticity = 0.75;
        float energyNoise = 0.5;
    } ballParams;

    Ball centreBall = Ball((float)window_dim.width / 2.0f, (float)window_dim.height / 2.0f, ballParams.radius);

    std::vector<Ball> balls;

    // while the window is open
    while (window.isOpen()) {
        sf::Event evnt{};
        // allows the user to move the window
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized: {
                    // std::cout << evnt.size.width << "x" << evnt.size.height << std::endl;
                    sf::FloatRect visibleArea(0, 0, (float)evnt.size.width, (float)evnt.size.height);
                    window.setView(sf::View(visibleArea));
                    break;
                }
                case sf::Event::TextEntered:
                    if (evnt.text.unicode < 128) {
                        // printf("%c", evnt.text.unicode);
                        // std::cout << (char)evnt.text.unicode;
                    }
                    break;
                default:
                    break;
            }
        }

        if (evnt.type == sf::Event::MouseButtonPressed) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                Vec2 mousePos = Vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

                Vec2 spawnPos = Vec2((double) window.getSize().x / 2, (double) window.getSize().y / 2);
                Vec2 vel = (mousePos - spawnPos) * 0.005;
                Ball newBall = Ball((float) spawnPos.x, (float) spawnPos.y, ballParams.radius, vel.x, vel.y,ballParams.elasticity);
                // set random colour for newBall
                newBall.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
                balls.emplace_back(newBall);
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            Vec2 mousePos = Vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            Vec2 spawnPos = Vec2((double) window.getSize().x / 2, (double) window.getSize().y / 2);
            Vec2 vel = (mousePos - spawnPos) * 0.005;
            Ball newBall = Ball((float) spawnPos.x, (float) spawnPos.y, ballParams.radius, vel.x, vel.y,ballParams.elasticity);
            // set random colour for newBall
            newBall.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
            balls.emplace_back(newBall);
        }

        // recentre the ball with current window size
        centreBall.setPosition((float)window.getSize().x / 2.0f, (float)window.getSize().y / 2.0f);

        window.clear();
        window.draw(centreBall);

        // draw the balls and physics updates
        for (int i = 0; i < balls.size(); i++) {
            // https://stackoverflow.com/questions/64519677/c-function-not-updating-variables
            // we want a reference to the object not a copy
            Ball& ball = balls[i];

            ball.position += ball.velocity;
            ball.setPosition((float)ball.position.x, (float)ball.position.y);

            if (ball.position.x > window.getSize().x || ball.position.x < 0 || ball.position.y > window.getSize().y || ball.position.y < 0) {
                balls.erase(balls.begin() + i);
            }

            // check for wall collisions
            bool xWallsCollide = (ball.position.x > (double)window.getSize().x - ball.getRadius()) || (ball.position.x < ball.getRadius());
            bool yWallsCollide = (ball.position.y > (double)window.getSize().y - ball.getRadius()) || (ball.position.y < ball.getRadius());

            if (xWallsCollide) {
                if (!ball.xColliding) {
                    ball.velocity.x *= -1;
                    ball.xColliding = true;
                    // TODO: remove some random amount of energy
                    ball.removeEnergy(ball.energy * (1 - ball.elasticity));
                } else {
                    ball.xColliding = false;
                }
            }

            if (yWallsCollide) {
                if (!ball.yColliding) {
                    ball.velocity.y *= -1;
                    ball.yColliding = true;
                    ball.removeEnergy(ball.energy * (1 - ball.elasticity));
                } else {
                    ball.yColliding = false;
                }
            }

            // gravity
            float gravity = yWallsCollide ? 0 : 0.1;
            ball.applyForce(Vec2(0, gravity));

            window.draw(ball);
        }

        std::cout << balls.size() << std::endl;

        window.display();
    }

    return 0;
}