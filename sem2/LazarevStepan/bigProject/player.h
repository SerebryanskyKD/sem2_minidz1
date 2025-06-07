#pragma once
#include <map>
#include <string>
#include "game.h"
#include "city.hpp"
#include "shop.h"
#include "button.hpp"
#include "museum.h"

using str = std::string;

class City;
class Shop;
class Museum;
class Button;

class Player {
private:
	int food;
	std::map<str, int> equipment;
	int money;
	int artifactsOnSell = 0;
public:
	sf::Texture texture{ "../textures/character/M_07.png" };
	sf::Vector2f position;
	float speed = 100.0f; //pixels in sec

	sf::RectangleShape* body;

	std::vector<sf::IntRect> frames; 
	int currentFrame = 0;
	float frameTime = 0.3f;
	float frameTimer = 0.0f;
	int direction = 0;

	bool isLocationChanged = false;
	bool isInteracting = false;
	bool canMove = true;

	Button* interactButton;

	Player(int sFood, int sMoney);
	~Player();


	void render(sf::RenderWindow* window);

	void handleEvent(sf::Event& event, sf::RenderWindow* window, const std::vector<std::vector<int>>& collisionLayer, float deltaTime, Shop* shop);

	void animate(float& deltaTime);

	void update(float& deltaTime, City* city, Shop* shop, Museum* museum);

	void interact(int itemID);


	void checkCollision(std::vector<std::vector<int>>& collisionLayer, sf::Vector2f& movement,
		const float& mapWidthTiles, const float& mapHeightTiles, const int& tileSize);


	void setMoney(int money);

	void setFood(int food);

	void setEquipment(const str& name, int amount);

	void setArtifacts(int toAdd);

	int getMoney() const;

	int getFood() const;

	std::map<str, int>& getEquipment();

	int getArtifacts() const;
};