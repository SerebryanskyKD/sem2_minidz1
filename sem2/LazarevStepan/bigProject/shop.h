#pragma once
#include <map>
#include <string>
#include <random>
#include "player.h"
#include <tuple>
#include "game.h"
#include <vector>
#include "game.h"
#include "player.h"
#include "shopUI.h"


class Button;
class Player;
class shopUI;

using str = std::string;

class Shop {
public:
	Shop(sf::VideoMode& mode, sf::RenderWindow* window, Player* player);
	~Shop();

	std::map<std::string, std::tuple<int, int>> catalog;
	const int foodPrice = 5;

	shopUI* menu;
	Player* player;

	std::vector<sf::VertexArray> layersVertices;
	std::vector<std::vector<int>> layers;
	std::vector<std::vector<int>> collisionLayer;

	bool deleteFlag = false;

	sf::Texture tileset1{ "../textures/interior/lotsOfSprites/hyptosis_tile-art-batch-1.png" };
	sf::Texture tileset2{ "../textures/interior/lps/interior.png" };
	sf::Texture tileset3{ "../textures/mining/Mineria.png" };

	void render(sf::RenderWindow* window);

	void handleEvent(sf::Event& event, sf::RenderWindow* window, float& deltaTime);


	size_t loadMap(const std::string& filename);

	void loadCollisionMap(const std::string& filename);

	void openMenu();

	void closeMenu();

	bool isMenuOpen() const;

	bool checkBuyer(const str& item, int amount);

	void buy(const str& item, int amount);

	void sell(const str& item, int amount);
};