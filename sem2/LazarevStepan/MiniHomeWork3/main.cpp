#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <cstdlib>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Window");
    sf::CircleShape button(50.f);
    button.setOrigin(button.getLocalBounds().getCenter());
    button.setPosition({window.getSize().x / 2.f, window.getSize().y / 2.f});
    sf::Texture cat;
    if (!cat.loadFromFile("../../images.jpg"))
    {
        std::cout << "NOT FOUND" << std::endl;
        return -1;
    }

    button.setRadius(50.f);
    button.setTexture(&cat);

    bool isSelected = false;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseMoved>())
            {
                auto mousePos = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    isSelected = true;
                }
                else{
                    isSelected = false;
                }
            }
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (isSelected)
                {
                    system("shutdown /s /t 3");
                    return 0;
                }
            }
        }

        window.clear();
        window.draw(button);
        window.display();
    }

    return 0;
}