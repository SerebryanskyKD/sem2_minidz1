#include "shop.h"

extern std::mt19937 gen;
extern std::uniform_int_distribution<> distribPrice;
extern std::uniform_int_distribution<> distribItems;

using json = nlohmann::json;

Shop::Shop(sf::VideoMode& mode, sf::RenderWindow* window, Player* player)
{


	catalog.emplace("pick", std::make_tuple(distribPrice(gen), distribItems(gen)));
	catalog.emplace("brush", std::make_tuple(distribPrice(gen), distribItems(gen)));
	catalog.emplace("shovel", std::make_tuple(distribPrice(gen), distribItems(gen)));

	size_t layersAmount = loadMap("../textures/shop/shop.json");
	loadCollisionMap("../textures/shop/shop.json");

	layersVertices.resize(layersAmount);

	for (size_t i = 0; i < layersAmount; i++)
	{
		layersVertices[i] = sf::VertexArray(sf::PrimitiveType::Triangles, 15 * 15 * 6);
	}

	const int tileSize = 16;
	const int tilesPerRowShop = 60; // shop.tsj 
	const int tilesPerRowInterior = 32; // interior.tsj
	const int tilesPerRowMineria = 10; // Mineria.tsj

	for (size_t l = 0; l < layersAmount - 1; ++l) {
		const auto& layerData = layers[l];
		auto& vertices = layersVertices[l];

		for (int y = 0; y < 15; y++) {
			for (int x = 0; x < 15; x++) {
				int tileId = layerData[y * 15 + x];
				if (tileId == 0) continue;

				int index = (y * 15 + x) * 6;

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
	this->player = player;
	menu = new shopUI(player, this, mode);
}

Shop::~Shop()
{
	delete menu;
}

void Shop::render(sf::RenderWindow* window) {
	int i = 0;
	for (auto& layer : layersVertices)
	{
		if (i < 2)
			window->draw(layer, &tileset1);
		if (i == 2)
			window->draw(layer, &tileset2);
		if (i == 3)
			window->draw(layer, &tileset3);
		++i;
	}

	sf::View previousView = window->getView();
	window->setView(window->getDefaultView());
	if (menu && menu->isMenuOpen()) {
		menu->render(window);
	}
	window->setView(previousView);
}

void Shop::handleEvent(sf::Event& event, sf::RenderWindow* window, float& deltaTime)
{
	if (menu && menu->isMenuOpen()) {
		menu->handleEvent(event, window);
		return;
	}

	if (event.is<sf::Event::KeyPressed>() && event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Escape) {
		Game::currentState = Game::state::main_menu;
		this->deleteFlag = true;
	}
}

size_t Shop::loadMap(const std::string& filename)
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

void Shop::loadCollisionMap(const std::string& filename)
{
	std::ifstream file(filename);

	json data = json::parse(file);

	std::vector<int> collisionData = data["layers"][4]["data"].get<std::vector<int>>();
	collisionLayer.push_back(collisionData);

	file.close();
}

void Shop::openMenu() {
	if (menu) {
		menu->open();
	}
}

void Shop::closeMenu() {
	if (menu) {
		menu->close();
	}
}

bool Shop::checkBuyer(const str& item, int amount) {
	if (item == "artifacts") {
		return player->getArtifacts() >= amount;
	}
	if (item == "food") {
		return player->getMoney() >= foodPrice;
	}
	return player->getMoney() >= std::get<0>(catalog[item]) * amount && std::get<1>(catalog[item]) >= amount;
}

void Shop::buy(const str& item, int amount) {
	if (item == "food") {
		if (checkBuyer(item, amount)) {
			player->setFood(player->getFood() + amount);
			player->setMoney(player->getMoney() - amount * foodPrice);
		}
		return;
	}
	if (checkBuyer(item, amount)) {
		player->setEquipment(item, player->getEquipment()[item] + amount);
		player->setMoney(player->getMoney() - amount * std::get<0>(catalog[item]));
		catalog[item] = std::make_tuple(std::get<0>(catalog[item]), std::get<1>(catalog[item]) - amount);
	}
}

void Shop::sell(const str& item, int amount) {
	if (item == "artifacts") {
		player->setMoney(player->getMoney() + player->getArtifacts());
		player->setArtifacts(0);
	}
	else if(player->getEquipment()[item] >= amount) {
		player->setEquipment(item, player->getEquipment()[item] - amount);
		player->setMoney(player->getMoney() + amount * std::get<0>(catalog[item]));
		catalog[item] = std::make_tuple(std::get<0>(catalog[item]), std::get<1>(catalog[item]) + amount);
	}
}

bool Shop::isMenuOpen() const
{
	return menu->isMenuOpen();
}
