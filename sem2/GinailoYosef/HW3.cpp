#include <SFML/Graphics.hpp>
#include <windows.h>
#include <random>
#include <thread>
#include <chrono>

int main() {
    sf::RenderWindow window(
        sf::VideoMode({ 400, 150 }),
        "Button", 
        sf::Style::None,
        sf::State::Windowed
    );

    //4 random
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(10, 60);

    bool mousePressed = false;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { window.close(); }
        }

        if (!window.hasFocus()) { continue; };

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (!mousePressed) {
                mousePressed = true;

                std::this_thread::sleep_for(std::chrono::seconds(distribution(generator)));

                ExitWindows(0, 0); //soft reboot
            };
        }
        else { 
            mousePressed = false; 
        }

        window.clear(sf::Color::Red);

        window.display();
    }
}