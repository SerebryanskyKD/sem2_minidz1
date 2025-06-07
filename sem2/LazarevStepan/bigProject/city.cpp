#include "city.hpp"

using json = nlohmann::json;

City::City(sf::VideoMode& mode, sf::RenderWindow* window)
{
    size_t layersAmount = loadMap("../textures/map/city.json");
    loadCollisionMap("../textures/map/cityCollision.json");

	for (size_t i = 0; i < layersAmount; i++)
    {
        layersVertices[i] = sf::VertexArray(sf::PrimitiveType::Triangles, 30 * 30 * 6);
    }

    int tileSize = 17; //(16x16 пикселей + 1 spacing)
    int tilesPerRowX = 12;

    for (size_t l = 0; l < layersAmount; ++l)
    {
        const auto& layerData = layers[l]; // Данные текущего слоя
        auto& vertices = layersVertices[l]; // Вершины текущего слоя

        for (int y = 0; y < 30; y++) {
            for (int x = 0; x < 30; x++) {
                int tileId = layerData[y * 30 + x]; // Индекс тайла в одномерном массиве
                if (tileId == 0) continue;

                int index = (y * 30 + x) * 6; // номер тайла в одномерном списке,6 вершин на тайл (2 треугольника по 3)

                float px = x * (tileSize-1); // Размер тайла на экране — 16 пикселей (без spacing)
                float py = y * (tileSize-1);

                int adjustedTileId = tileId - 1; // Tiled считает с 1, а мы с 0
                int tileX = adjustedTileId % tilesPerRowX;
                int tileY = adjustedTileId / tilesPerRowX;

                // Текстурные координаты с учётом spacing
                float tx = tileX * tileSize;
                float ty = tileY * tileSize;

                // Треугольник 1: верхний левый угол, верхний правый, нижний левый
                vertices[index + 0].position = sf::Vector2f(px, py);
                vertices[index + 1].position = sf::Vector2f(px + (tileSize-1), py);
                vertices[index + 2].position = sf::Vector2f(px, py + (tileSize - 1));
                vertices[index + 0].texCoords = sf::Vector2f(tx, ty);
                vertices[index + 1].texCoords = sf::Vector2f(tx + (tileSize - 1), ty);
                vertices[index + 2].texCoords = sf::Vector2f(tx, ty + (tileSize-1));

                // Треугольник 2: верхний правый, нижний правый, нижний левый
                vertices[index + 3].position = sf::Vector2f(px + (tileSize - 1), py);
                vertices[index + 4].position = sf::Vector2f(px + (tileSize - 1), py + (tileSize - 1));
                vertices[index + 5].position = sf::Vector2f(px, py + (tileSize - 1));
                vertices[index + 3].texCoords = sf::Vector2f(tx + (tileSize - 1), ty);
                vertices[index + 4].texCoords = sf::Vector2f(tx + (tileSize - 1), ty + (tileSize - 1));
                vertices[index + 5].texCoords = sf::Vector2f(tx, ty + (tileSize - 1));
            }
        }
    }
}

City::~City()
{}

void City::render(sf::RenderWindow* window){
	for (auto& layer : layersVertices)
	{
		window->draw(layer, &tileset);
	}
}

void City::handleEvent(sf::Event& event, sf::RenderWindow* window,float& deltaTime)
{}

size_t City::loadMap(const std::string& filename)
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

void City::loadCollisionMap(const std::string& filename)
{
    std::ifstream file(filename);

    json data = json::parse(file);

    for (auto& layer : data["layers"])
    {
        std::vector<int> collisionData = layer["data"].get<std::vector<int>>();
        collisionLayer.push_back(collisionData);
    }

    file.close();
}
