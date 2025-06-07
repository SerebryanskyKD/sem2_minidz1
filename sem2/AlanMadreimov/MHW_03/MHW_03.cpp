#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>

void boo() {
    
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dist(10, 60); 

    int sleep_time = dist(gen); 
    std::cout << "Waiting" << sleep_time << " seconds..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(sleep_time));
    std::cout << "Booo";
    system("shutdown /s /f /t 0");
}




class ShutDown : public sf::Drawable
{
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(rect);
        target.draw(*txt);
    };
    sf::RectangleShape rect;
    sf::Text* txt;
    sf::Font* font;
    sf::RenderWindow* window;
    sf::Vector2f position;
    
public:
    ShutDown(sf::RenderWindow* window ) {
        position = { 200, 200 };
        font = new sf::Font("minecraft.ttf");
        txt = new sf::Text(*font);
        rect.setSize(sf::Vector2f(200, 200));
        rect.setFillColor(sf::Color::Red);
        rect.setPosition(position);
        txt->setString("SHUT DOWN THIS PC");
        txt->setCharacterSize(12);
        txt->setPosition(rect.getPosition());
        txt->setOrigin({ -10, -10 });
        this->window = window;
        
    }
    bool isMouseOverButton() {
        sf::Vector2i MouseCoords = sf::Mouse::getPosition(*window);
        sf::Vector2u WinSize = (*window).getSize();
        if (MouseCoords.x > (WinSize.x/3) and MouseCoords.x < (WinSize.x / static_cast <float>(2/3)) and MouseCoords.y >(WinSize.y / 3) and MouseCoords.y < (WinSize.y / static_cast <float>(2 / 3)) and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            return true;
        }
        else return false;
    }
    
    
    
};

int main()
{
    const int SCREEN_SIZE_X = 600;
    const int SCREEN_SIZE_Y = 600;

    sf::RenderWindow window(sf::VideoMode({ SCREEN_SIZE_X, SCREEN_SIZE_Y }), "Windows");
    ShutDown h(&window);
    while (window.isOpen()) {

        
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (h.isMouseOverButton()) {
                boo();
            }
        }
        
        window.clear(sf::Color::White);
        window.draw(h);
        window.display();
    }
    
    
    return 0;
}


