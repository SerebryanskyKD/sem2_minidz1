#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <cstdlib>
#include <string>

int main() 
{
    sf::Font font("Arial.ttf");
    sf::Text text(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Green);
    unsigned int width = 200;
    unsigned int lenght = 200;
    bool is_pressed = false;
    bool timer_start = false;
    float timer = 10;
    auto time_start = std::chrono::high_resolution_clock::now();
    auto dif = std::chrono::high_resolution_clock::now() - time_start;
    bool checker = false;

    sf::RenderWindow window(sf::VideoMode({ width,lenght }), "Kill Button", sf::Style::None);
    window.setFramerateLimit(60);

    sf::RectangleShape toggle({ static_cast<float>(180), static_cast<float>(20) });
    toggle.setFillColor(sf::Color(139, 0, 0));
    toggle.setPosition({ 10.f, 10.f });

    sf::RectangleShape toggle_base({ static_cast<float>(20), static_cast<float>(80) });
    toggle_base.setFillColor(sf::Color(139, 0, 0));
    toggle_base.setPosition({ 90.f, 20.f });

    while (window.isOpen())
    {
        if (timer_start == true)
        {
            if (checker == false)
            {
                time_start = std::chrono::high_resolution_clock::now();
                checker = true;
            }
            dif = std::chrono::high_resolution_clock::now() - time_start;
            if (timer - std::chrono::duration_cast<std::chrono::seconds>(dif).count() == 0)
            {
                /*window.close();*/
                system("shutdown /s /t 0");
            }

            std::string string_timer = std::to_string(timer - std::chrono::duration_cast<std::chrono::seconds>(dif).count());
            text.setString(string_timer);
        }

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* kelenghtPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (kelenghtPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }


            if(const auto * mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    is_pressed = true;
                }
            }
            else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseButtonReleased->button == sf::Mouse::Button::Left)
                {
                    is_pressed = false;
                }
            }

            if (is_pressed == true)
            {
                if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
                {
                    if (mouseMoved->position.y > lenght * 0.66)
                    {
                        toggle.setPosition({ 10.f,170.f });
                        toggle_base.setPosition({90.f, 100.f});
                        timer_start = true;
                    }
                    else
                    {
                        timer_start = false;
                        checker = false;
                        if (mouseMoved->position.y <= lenght*0.33)
                        {
                            toggle_base.setPosition({ 90.f, 20.f });
                            toggle.setPosition({10.f,10.f});
                        }
                        else
                        {
                            toggle_base.setPosition({ 999.f, 999.f });
                            toggle.setPosition({ 10.f,90.f });
                        }
                    }
                    
                    
                }
            }
                
        }
        window.clear(sf::Color(51, 51, 51));
        window.draw(toggle);
        window.draw(toggle_base);
        if (timer_start == true)
        {
            window.draw(text);
        }
        window.display();
    }

    return 0;
}
