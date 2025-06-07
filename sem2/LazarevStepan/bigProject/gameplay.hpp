#pragma once
#include <vector>
#include "button.hpp"
#include "game.h"
#include "city.hpp"
#include "player.h"
#include "shop.h"
#include "museum.h"
#include "base.h"

class Button;
class City;
class Player;
class Shop;
class Museum;
class Base;

class Gameplay {
private:
	std::vector<Button*> buttons;
	int selectedButton = -1;
public:
	bool deleteFlag = false;

	static enum class locations {shop, base, city,museum};
	static locations currentLocation;

	Player* player;

	City* city;
	Shop* shop;
	Museum* museum;
	Base* base;


	Gameplay(sf::VideoMode& mode, sf::RenderWindow* window);

	~Gameplay();

	void render(sf::RenderWindow* window);

	void handleEvent(sf::Event& event, sf::RenderWindow* window, float deltaTime);

	void update(float& deltaTime,sf::VideoMode& mode, sf::RenderWindow* window);

	Player* getPlayer() const { return player; }
};