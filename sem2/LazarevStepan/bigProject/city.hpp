#pragma once
#include <vector>
#include "game.h"
#include "player.h"

class Button;
class Player;

class City {
public:
	bool deleteFlag = false;

	std::vector<sf::VertexArray> layersVertices{ 2 };
	std::vector<std::vector<int>> layers;
	std::vector<std::vector<int>> collisionLayer;

	sf::Texture tileset{ "../textures/kenney_tiny-town/Tilemap/tilemap.png" };

	City(sf::VideoMode& mode, sf::RenderWindow* window);

	~City();

	void render(sf::RenderWindow* window);

	void handleEvent(sf::Event& event, sf::RenderWindow* window,float& deltaTime);

	size_t loadMap(const std::string& filename);

	void loadCollisionMap(const std::string& filename);
};