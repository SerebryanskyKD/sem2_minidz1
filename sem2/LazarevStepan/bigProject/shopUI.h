#pragma once

#include <fstream>
#include <iostream>
#include "game.h"
#include "player.h"
#include "button.hpp"
#include "shop.h"

class Button;
class Player;
class Shop;


class shopUI
{
private:
    std::vector<Button*> buttons;
    static inline sf::Font font{ "../fonts/KenneyBlocks.ttf" };
    sf::Text playerInfo{ font };
	Player* player;
    Shop* shop;
    bool isOpen;

public:
    shopUI(Player* player, Shop* shop, sf::VideoMode& mode);
    ~shopUI();

    void open();
    void close();
    bool isMenuOpen() const { return isOpen; }

    void render(sf::RenderWindow* window);
    void handleEvent(sf::Event& event, sf::RenderWindow* window);

    void updatePlayerInfo();
};

