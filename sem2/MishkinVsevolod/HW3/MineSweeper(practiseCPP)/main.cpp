#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Audio/Music.hpp>
#include <optional>
#include <chrono>
#include <iostream>
#include <sstream>
#include <random>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1280, 720)), "Shutdown Button", sf::State::Windowed);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("background.png");
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("SecretButton.png");

    sf::Sprite buttonSprite(buttonTexture);
    buttonSprite.setScale(sf::Vector2f(4, 4));
    buttonSprite.setPosition(sf::Vector2f(540, 210));

    sf::Font font("arial.ttf");
    sf::Music music("tetris.mp3");

    sf::Text countdownText(font);
    countdownText.setFont(font);    
    
    sf::Text counterText(font);
    counterText.setFont(font);
    counterText.setCharacterSize(50);
    counterText.setFillColor(sf::Color::Black);
    counterText.setPosition(sf::Vector2f(10, 10));

    bool countdownActive = false;
    sf::Clock countdownClock;
    int shutdownTime = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(10, 60);

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseEvent->button == sf::Mouse::Button::Left) {

                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    if (buttonSprite.getGlobalBounds().contains(worldPos)) {
                        shutdownTime = distr(gen);
                        countdownClock.restart();
                        countdownActive = true;

                        music.play();
                    }
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(buttonSprite);

        if (countdownActive) {
            int secondsPassed = static_cast<int>(countdownClock.getElapsedTime().asSeconds());
            std::ostringstream ss;
            ss << "Time passed: " << secondsPassed << " sec.";
            counterText.setString(ss.str());
            window.draw(counterText);

            if (secondsPassed >= shutdownTime) {
#ifdef _WIN32
                system("shutdown /s /t 0");
#else
                system("shutdown -h now");
#endif
                window.close();
            }
        }

        window.display();
}
    return 0;
}
