#include "museum.h"

using json = nlohmann::json;
	
Museum::Museum(sf::VideoMode& mode, sf::RenderWindow* window, Player* player)
{
	size_t layersAmount = loadMap("../textures/museum/museum.json");
	loadCollisionMap("../textures/museum/museum.json");

	layersVertices.resize(layersAmount);
	achievmentsList.resize(9);

	for (size_t i = 0; i < layersAmount; i++)
	{
		layersVertices[i] = sf::VertexArray(sf::PrimitiveType::Triangles, 16 * 22 * 6);
	}

	const int tileSize = 16;
	const int tilesPerRowShop = 60; // shop.tsj 
	const int tilesPerRowInterior = 32; // interior.tsj
	const int tilesPerRowMineria = 10; // Mineria.tsj

	for (size_t l = 0; l < layersAmount - 1; ++l) {
		const auto& layerData = layers[l];
		auto& vertices = layersVertices[l];

		for (int y = 0; y < 22; y++) {
			for (int x = 0; x < 16; x++) {
				int tileId = layerData[y * 16 + x];
				if (tileId == 0) continue;

				int index = (y * 16 + x) * 6;

				float px = x * tileSize;
				float py = y * tileSize;

				int adjustedTileId;
				int tilesPerRow;
				if (tileId >= 4625) { // Mineria.tsj (firstgid: 4625)
					adjustedTileId = tileId - 4625;
					tilesPerRow = tilesPerRowMineria;
				}
				else if (tileId >= 3601) { // interior.tsj (firstgid: 3601)
					adjustedTileId = tileId - 3601;
					tilesPerRow = tilesPerRowInterior;
				}
				else { // shop.tsj (firstgid: 1)
					adjustedTileId = tileId - 1;
					tilesPerRow = tilesPerRowShop;
				}

				int tileX = adjustedTileId % tilesPerRow;
				int tileY = adjustedTileId / tilesPerRow;

				float tx, ty;

				tx = tileX * tileSize;
				ty = tileY * tileSize;

				// Triangle 1: top-left, top-right, bottom-left
				vertices[index + 0].position = sf::Vector2f(px, py);
				vertices[index + 1].position = sf::Vector2f(px + tileSize, py);
				vertices[index + 2].position = sf::Vector2f(px, py + tileSize);
				vertices[index + 0].texCoords = sf::Vector2f(tx, ty);
				vertices[index + 1].texCoords = sf::Vector2f(tx + tileSize, ty);
				vertices[index + 2].texCoords = sf::Vector2f(tx, ty + tileSize);

				// Triangle 2: top-right, bottom-right, bottom-left
				vertices[index + 3].position = sf::Vector2f(px + tileSize, py);
				vertices[index + 4].position = sf::Vector2f(px + tileSize, py + tileSize);
				vertices[index + 5].position = sf::Vector2f(px, py + tileSize);
				vertices[index + 3].texCoords = sf::Vector2f(tx + tileSize, ty);
				vertices[index + 4].texCoords = sf::Vector2f(tx + tileSize, ty + tileSize);
				vertices[index + 5].texCoords = sf::Vector2f(tx, ty + tileSize);

			}
		}
	}
}

void Museum::checkPlayerAchievments()
{
	std::ifstream in("playerAchievments.txt");

	for (size_t i = 0; i < achievmentsList.size(); ++i)
	{
		str line;
		getline(in,line);

		if (line == "1")
		{
			achievmentsList[i] = true;
		}
		else if (line == "0")
		{
			achievmentsList[i] = false;
		}
	}

	in.close();
}

void Museum::render(sf::RenderWindow* window)
{
	checkPlayerAchievments();
	int i = 0;
	for (auto& layer : layersVertices)
	{
		if (i < 2)
			window->draw(layer, &tileset1);
		else if (i == 2)
			window->draw(layer, &tileset2);
		else if (i < 12)
		{
			if (achievmentsList[i - 3])
				window->draw(layer, &tileset3);
		}
		++i;
	}


}

size_t Museum::loadMap(const std::string& filename)
{
	std::ifstream file(filename);

	json data = json::parse(file);

	for (auto& layer : data["layers"])
	{
		std::vector<int> layerData = layer["data"].get<std::vector<int>>();
		layers.push_back(layerData);
	}

	file.close();

	return data["layers"].size();
}

void Museum::loadCollisionMap(const std::string& filename)
{
	std::ifstream file(filename);

	json data = json::parse(file);

	std::vector<int> collisionData = data["layers"][12]["data"].get<std::vector<int>>();
	collisionLayer.push_back(collisionData);

	file.close();
}