#include <iostream>
#include <SFML/Graphics.hpp>

#include "modules/Vec2.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(512, 512), "cpp-bouncy-balls", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
    player.setFillColor(sf::Color{ 0xff6660 });

    // while the window is open
    while (window.isOpen()) {
        sf::Event evnt{};
        // allows the user to move the window
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    std::cout << evnt.size.width << "x" << evnt.size.height << std::endl;
                    break;
                case sf::Event::TextEntered:
                    if (evnt.text.unicode < 128) {
                        // printf("%c", evnt.text.unicode);
                        std::cout << (char)evnt.text.unicode;
                    }
                    break;
                default:
                    break;
            }
        }

        std::cout << Vec2(1, 2).x << std::endl;

        window.draw(player);
        window.display();
    }

    return 0;
}