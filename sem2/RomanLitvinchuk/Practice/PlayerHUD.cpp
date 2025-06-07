#include "PlayerHUD.h"

PlayerHUD::PlayerHUD(Player& player)
	: player(player)
{
	font.loadFromFile("mine.ttf");

	energyText.setFont(font);
	energyText.setCharacterSize(24);
	energyText.setFillColor(sf::Color::Red);
	energyText.setPosition({ 100, 800 });

	moneyText.setFont(font);
	moneyText.setCharacterSize(24);
	moneyText.setFillColor(sf::Color::Red);
	moneyText.setPosition({ 100, 850 });
}

void PlayerHUD::draw(sf::RenderWindow& window)
{
	sf::RectangleShape bg({ 375,110 });
	bg.setFillColor(sf::Color(0, 0, 0, 200));
	bg.setOutlineThickness(2);
	bg.setPosition(75, 775);
	window.draw(bg);
	UpText(player);
	window.draw(energyText);
	window.draw(moneyText);
}

void PlayerHUD::UpText(Player& player) 
{
	energyText.setString("Energy: " + std::to_string(player.getEnergy()) + "/100");
	moneyText.setString("Money: " + std::to_string(player.getMoney()));
}