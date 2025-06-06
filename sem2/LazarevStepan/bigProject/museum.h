#pragma once
#include <string>
#include <random>
#include "player.h"
#include "game.h"
#include <vector>

using str = std::string;
class Player;

using str = std::string;

class Museum {
private:
	std::vector<str> foundLoot;
public:
	std::vector<sf::VertexArray> layersVertices;
	std::vector<std::vector<int>> layers;
	std::vector<std::vector<int>> collisionLayer;
	sf::Texture tileset1{ "../textures/interior/lotsOfSprites/hyptosis_tile-art-batch-1.png" };
	sf::Texture tileset2{ "../textures/interior/lps/interior.png" };
	sf::Texture tileset3{ "../textures/mining/Mineria.png" };

	std::vector<bool> achievmentsList;

	Museum(sf::VideoMode& mode, sf::RenderWindow* window, Player* player);

	void checkPlayerAchievments();

	void render(sf::RenderWindow* window);

	size_t loadMap(const std::string& filename);

	void loadCollisionMap(const std::string& filename);

};