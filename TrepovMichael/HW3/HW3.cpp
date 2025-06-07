#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <ctime>
#include <thread>
#include <chrono>

void shutdownComputerWithDelay() {
    std::srand(std::time(nullptr));
    int delay = 10 + std::rand() % 51;
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    system("shutdown -s -t 0");
}

int main() {
    sf::RenderWindow window(sf::VideoMode({static_cast <unsigned int> (400),
                                           static_cast <unsigned int> (200)}), "POWER BUTTON");
    sf::Font font("arial.ttf");
    sf::Text buttonText(font);
    buttonText.setString("Shutdown");
    buttonText.setFont(font);
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(sf::Vector2f(130.f, 80.f));

    sf::RectangleShape button(sf::Vector2f(140.f, 50.f));
    button.setFillColor(sf::Color::Blue);
    button.setPosition(sf::Vector2f (130.f, 80.f));

    bool mousePressed = false;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                mousePressed = false;
            }

            if (!mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                mousePressed = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (button.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    std::thread(shutdownComputerWithDelay).detach();
                }

            }
        }

        window.clear();
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}
