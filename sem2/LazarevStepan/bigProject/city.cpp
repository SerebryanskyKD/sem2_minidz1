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

    int tileSize = 17; //(16x16 �������� + 1 spacing)
    int tilesPerRowX = 12;

    for (size_t l = 0; l < layersAmount; ++l)
    {
        const auto& layerData = layers[l]; // ������ �������� ����
        auto& vertices = layersVertices[l]; // ������� �������� ����

        for (int y = 0; y < 30; y++) {
            for (int x = 0; x < 30; x++) {
                int tileId = layerData[y * 30 + x]; // ������ ����� � ���������� �������
                if (tileId == 0) continue;

                int index = (y * 30 + x) * 6; // ����� ����� � ���������� ������,6 ������ �� ���� (2 ������������ �� 3)

                float px = x * (tileSize-1); // ������ ����� �� ������ � 16 �������� (��� spacing)
                float py = y * (tileSize-1);

                int adjustedTileId = tileId - 1; // Tiled ������� � 1, � �� � 0
                int tileX = adjustedTileId % tilesPerRowX;
                int tileY = adjustedTileId / tilesPerRowX;

                // ���������� ���������� � ������ spacing
                float tx = tileX * tileSize;
                float ty = tileY * tileSize;

                // ����������� 1: ������� ����� ����, ������� ������, ������ �����
                vertices[index + 0].position = sf::Vector2f(px, py);
                vertices[index + 1].position = sf::Vector2f(px + (tileSize-1), py);
                vertices[index + 2].position = sf::Vector2f(px, py + (tileSize - 1));
                vertices[index + 0].texCoords = sf::Vector2f(tx, ty);
                vertices[index + 1].texCoords = sf::Vector2f(tx + (tileSize - 1), ty);
                vertices[index + 2].texCoords = sf::Vector2f(tx, ty + (tileSize-1));

                // ����������� 2: ������� ������, ������ ������, ������ �����
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
