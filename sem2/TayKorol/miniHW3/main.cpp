#include <SFML/Graphics.hpp>

#include <functional>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32

#include <windows.h>

#define SLEEP_SEC(sec) Sleep((sec) * 1000)
#define SHUTDOWN_CMD "shutdown /s /t 0"
#else
#include <unistd.h>
#define SLEEP_SEC(sec) sleep(sec)
#define SHUTDOWN_CMD "shutdown now"
#endif

class Button : public sf::Drawable {
public:
    Button(const sf::Vector2f &position, const sf::Vector2f &size,
           const sf::Color &normalColor, const sf::Color &pressedColor)
            : m_normalColor(normalColor), m_pressedColor(pressedColor), m_isPressed(false) {
        m_shape.setPosition(position);
        m_shape.setSize(size);
        m_shape.setFillColor(normalColor);
    }

    void setOnClick(std::function<void()> callback) {
        m_callback = std::move(callback);
    }

    void handleEvent(const sf::Event &event, const sf::RenderWindow &window) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            const sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
            const sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);

            if (m_shape.getGlobalBounds().contains(mousePos)) {
                m_isPressed = true;
                m_shape.setFillColor(m_pressedColor);
            }
        } else if (event.is<sf::Event::MouseButtonReleased>() &&
                   (event.getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)) {
            if (m_isPressed) {
                m_isPressed = false;
                m_shape.setFillColor(m_normalColor);

                if (m_callback)
                    m_callback();
            }
        }
    }

private:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(m_shape, states);
    }

    sf::RectangleShape m_shape;
    sf::Color m_normalColor;
    sf::Color m_pressedColor;
    bool m_isPressed;
    std::function<void()> m_callback;
};


void shutDown() {
    srand(time(0));
    int delay = 10 + (rand() % 51);  // 10-60 секунд

    std::cout << "Computer shoutdown in " << delay << " seconds..." << std::endl;
    SLEEP_SEC(delay);

    std::cout << "Turning off!" << std::endl;
    system(SHUTDOWN_CMD);

}

int main() {
    system("cmd /c echo test");
    sf::Clock timer;
    std::string name = "Shutdown Button";
    bool isShutdownTriggered = false;
    srand(time(0));
    int randomDelay = 10 + (rand() % 51);



    sf::RenderWindow window(sf::VideoMode({800, 600}), name, sf::Style::Default);

    Button button({100, 100}, {200, 50}, sf::Color::Green, sf::Color::Red);
    button.setOnClick([&isShutdownTriggered, &timer]() {
        std::cout << "Button clicked!" << std::endl;
        if (!isShutdownTriggered) {
            std::cout << "!!!";
            isShutdownTriggered = true;
            timer.start();
        }

    });
    timer.stop();
    float last_tick = randomDelay;
    while (window.isOpen()) {
        while (const std::optional _event = window.pollEvent()) {
            if (_event->is<sf::Event::Closed>())
                window.close();
            button.handleEvent(_event.value(), window);
        }

        if (isShutdownTriggered) {
            float elapsedSeconds = timer.getElapsedTime().asSeconds();
            if (elapsedSeconds >= randomDelay) {
                std::cout << "Turning off!" << std::endl;
                system(SHUTDOWN_CMD);
            }

            int remainingTime = static_cast<int>(randomDelay - elapsedSeconds);
            if (remainingTime < 0) remainingTime = 0;
            if (remainingTime <= last_tick - 1){
                std::cout << ("Before turning off: " + std::to_string(remainingTime) + " seconds\n");
                last_tick = remainingTime;
            }


        }


        window.clear(sf::Color::Black);
        window.draw(button);
        window.display();
    }
}