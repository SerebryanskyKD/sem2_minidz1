#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>

class PlayerHUD 
{
private:
	Player& player;
	sf::Font font;
	sf::Text energyText;
	sf::Text moneyText;

public:
	PlayerHUD(Player& player);
	void draw(sf::RenderWindow& window);
	void UpText(Player& player);
};