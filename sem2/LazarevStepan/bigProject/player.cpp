#include "player.h"


Player::Player(int sFood, int sMoney) :food(sFood), money(sMoney) {
	equipment.emplace("pick", 1);
	equipment.emplace("shovel", 1);
	equipment.emplace("brush", 1);

	position = sf::Vector2f{ 95, 260 };
	int x = position.x;
	int y = position.y;

	frames.reserve(12);

	for (int dir = 0; dir < 4; ++dir) { // 4 направления
		for (int frame = 0; frame < 3; ++frame) { // 3 кадра
			frames.push_back(sf::IntRect{ {dir * 16,frame * 17 }, {16,17} });
		}
	}

	body = new sf::RectangleShape;
	body->setSize({ 16.f,17.f });
	body->setPosition(position);
	body->setTexture(&texture);
	body->setTextureRect(frames[0]);
	//body->setScale({ 2.0f,2.0f });
}

Player::~Player()
{
	delete body;
	delete interactButton;
}

void Player::handleEvent(sf::Event& event, sf::RenderWindow* window, const std::vector<std::vector<int>>& collisionLayer, float deltaTime, Shop* shop)
{
	if (event.is<sf::Event::KeyPressed>() && event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::E) {
		if (isInteracting && shop && !shop->isMenuOpen()) {
			shop->openMenu();
			canMove = false;
		}
	}
}

void Player::update(float& deltaTime, City* city, Shop* shop, Museum* museum)
{

	isLocationChanged = false;
	sf::Vector2f movement(0.0f, 0.0f);

	if (canMove) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			movement.y -= speed * deltaTime;
			direction = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			movement.y += speed * deltaTime;
			direction = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			movement.x -= speed * deltaTime;
			direction = 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			movement.x += speed * deltaTime;
			direction = 1;
		}
	}

	switch (Gameplay::currentLocation)
	{
	case Gameplay::locations::city:
	{
		checkCollision(city->collisionLayer, movement, 30, 30, 16);
		break;
	}
	case Gameplay::locations::shop:
	{
		checkCollision(shop->collisionLayer, movement, 15, 15, 16);
		break;
	}
	case Gameplay::locations::museum:
	{
		checkCollision(museum->collisionLayer, movement, 16, 22, 16);
		break;
	}
	}

	if (abs(movement.x) == 0.0f && abs(movement.y) == 0.0f)
	{
		currentFrame = 0;
		body->setTextureRect(frames[direction * 3 + currentFrame]);
	}
	else if (!isLocationChanged)
	{
		animate(deltaTime);
		body->setPosition(position);
	}
}

void Player::animate(float& deltaTime)
{
	frameTimer += deltaTime;
	if (frameTimer >= frameTime) {
		frameTimer -= frameTime;

		currentFrame = (currentFrame + 1) % 3;
		body->setTextureRect(frames[direction * 3 + currentFrame]);
	}
}

void Player::render(sf::RenderWindow* window)
{
	window->draw(*body);
	if (isInteracting)
	{
		interactButton->render(window);
	}
}

void Player::interact(int itemID)
{
	switch (itemID)
	{
	case 117: // city -> shop
	{
		position = sf::Vector2f{ 45.0f, 130.0f };
		body->setPosition(position);
		isLocationChanged = true;
		Gameplay::currentLocation = Gameplay::locations::shop;
		break;
	}
	case 4675: // shop -> city
	{
		position = sf::Vector2f{ 95.0f, 280.0f };
		body->setPosition(position);
		isLocationChanged = true;
		Gameplay::currentLocation = Gameplay::locations::city;
		break;
	}
	case 4703: // museum -> city
	{
		position = sf::Vector2f{ 350.0f, 155.0f };
		body->setPosition(position);
		isLocationChanged = true;
		Gameplay::currentLocation = Gameplay::locations::city;
		break;
	}
	case 118: // city -> museum
		{
		position = sf::Vector2f{ 45.0f, 130.0f };
		body->setPosition(position);
		isLocationChanged = true;
		Gameplay::currentLocation = Gameplay::locations::museum;
		break;
		}
	case 129:
		{
		Gameplay::currentLocation = Gameplay::locations::base;
		isLocationChanged = true;
		}
	}
	if (itemID >= 4693 && itemID <= 4724 && Gameplay::currentLocation == Gameplay::locations::shop) //shop interaction
	{
		interactButton = new Button("E", [itemID, this]()
			{});
		interactButton->setPosition({ body->getGlobalBounds().getCenter() - sf::Vector2f{0.0f,body->getSize().y} });
		interactButton->setScale({ 0.5f,0.5f });
		isInteracting = true;
	}

}

void Player::checkCollision(std::vector<std::vector<int>>& collisionLayer, sf::Vector2f& movement,
	const float& mapWidthTiles, const float& mapHeightTiles, const int& tileSize)
{

	const float mapWidth = mapWidthTiles * tileSize;
	const float mapHeight = mapHeightTiles * tileSize;
	const float playerWidth = 16 * body->getScale().x;
	const float playerHeight = 17 * body->getScale().y;

	// Проверка движения по X

	if (movement.x != 0) {
		sf::Vector2f newPositionX = position;
		newPositionX.x += movement.x;

		if (newPositionX.x < 0) {
			newPositionX.x = 0;
		}
		else if (newPositionX.x + playerWidth > mapWidth) {
			newPositionX.x = mapWidth - playerWidth;
		}

		bool canMoveX = true;
		int minTileY = static_cast<int>(newPositionX.y / tileSize);
		int maxTileY = static_cast<int>((newPositionX.y + playerHeight - 1) / tileSize);

		int checkTileX;
		if (movement.x > 0) { // Движение вправо
			checkTileX = static_cast<int>((newPositionX.x + playerWidth - 1) / tileSize); // Правый край
		}
		else { // Движение влево
			checkTileX = static_cast<int>(newPositionX.x / tileSize); // Левый край
		}

		if (checkTileX >= 0 && checkTileX < mapWidthTiles && minTileY >= 0 && maxTileY < mapHeightTiles) {
			for (int y = minTileY; y <= maxTileY && canMoveX; ++y) {
				int idx = y * mapWidthTiles + checkTileX;
				if (collisionLayer[0][idx] != 0) {
					canMoveX = false;
				}
				else
				{
					isInteracting = false;
					delete interactButton;
					interactButton = nullptr;
				}
			}
		}
		else {
			canMoveX = false;
		}

		if (canMoveX) {
			position.x = newPositionX.x;
		}
	}

	// Проверка движения по Y
	if (movement.y != 0) {
		sf::Vector2f newPositionY = position;
		newPositionY.y += movement.y;

		if (newPositionY.y < 0) {
			newPositionY.y = 0;
		}
		else if (newPositionY.y + playerHeight > mapHeight) {
			newPositionY.y = mapHeight - playerHeight;
		}

		bool canMoveY = true;
		int minTileX = static_cast<int>(newPositionY.x / tileSize);
		int maxTileX = static_cast<int>((newPositionY.x + playerWidth - 1) / tileSize);

		int checkTileY;
		if (movement.y > 0) { // Движение вниз
			checkTileY = static_cast<int>((newPositionY.y + playerHeight - 1) / tileSize); // Нижний край
		}
		else { // Движение вверх
			checkTileY = static_cast<int>(newPositionY.y / tileSize); // Верхний край
		}

		if (minTileX >= 0 && maxTileX < mapWidthTiles && checkTileY >= 0 && checkTileY < mapHeightTiles) {
			for (int x = minTileX; x <= maxTileX && canMoveY; ++x) {
				int idx = checkTileY * mapWidthTiles + x;
				if (collisionLayer[0][idx] != 0) {
					canMoveY = false;
					interact(collisionLayer[0][idx]);
				}
				else
				{
					isInteracting = false;
					delete interactButton;
					interactButton = nullptr;
				}
			}
		}
		else {
			canMoveY = false;
		}

		if (canMoveY) {
			position.y = newPositionY.y;
		}
	}
}

void Player::setMoney(int money) {
	this->money = (money < 0) ? 0 : money;
}

void Player::setFood(int food) {
	this->food = (food < 0) ? 0 : food;
}

void Player::setEquipment(const str& name, int amount) {
	equipment[name] = (amount < 0) ? 0 : amount;
}

void Player::setArtifacts(int newVal) {
	artifactsOnSell = newVal;
}

int Player::getMoney() const {
	return this->money;
}

int Player::getFood() const {
	return this->food;
}

std::map<str, int>& Player::getEquipment() {
	return this->equipment;
}

int Player::getArtifacts() const {
	return artifactsOnSell;
}