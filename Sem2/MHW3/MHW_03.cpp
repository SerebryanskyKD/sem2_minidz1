#include <chrono>
#include <thread>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>


class OffPC : public sf::Drawable
{
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {

        target.draw(kvadrat);

        target.draw(*txt);
    };
    sf::Text* txt;
    sf::Font* font;
    sf::RectangleShape kvadrat;
    sf::RenderWindow* window;
    sf::Vector2f position;
    sf::Texture* texture;
    
public:
    OffPC(sf::RenderWindow* window ) {
        this->window = window;
        position = {250, 250};

        font = new sf::Font("arial.ttf");
        txt = new sf::Text(*font,"Click to Off your PC",24);
        txt->setPosition({500,500});
        texture = new sf::Texture("image.png");
        txt->setOrigin({ 50,50 });

        kvadrat.setSize(sf::Vector2f(500, 500));
        kvadrat.setTexture(texture);
        kvadrat.setPosition(position);


        
    }
    bool ifMouseButtonPressed() {
        sf::Vector2i MouseCoords = sf::Mouse::getPosition(*window);
        if (MouseCoords.x > 250 and MouseCoords.x < 750 and MouseCoords.y >250 and MouseCoords.y < 750 and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            return true;
        }
        else return false;
    }
    
    
    
};

void WaitRandomTime() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(10, 60);

    int sleep_time = dist(gen);
    std::this_thread::sleep_for(std::chrono::seconds(sleep_time));
}

int main()
{
    const int SCREEN_SIZE = 1000;

    sf::RenderWindow window(sf::VideoMode({ SCREEN_SIZE, SCREEN_SIZE }), "Exit Button Window");
    OffPC button(&window);
    while (window.isOpen()) {

        
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (button.ifMouseButtonPressed()) {
                WaitRandomTime();
                system("shutdown -s");
            }
        }
        
        window.clear(sf::Color::Black);
        window.draw(button);
        window.display();
    }
    
    
    return 0;
}


