#include "gameplay.hpp"

Gameplay::locations Gameplay::currentLocation;

Gameplay::Gameplay(sf::VideoMode& mode, sf::RenderWindow* window)
{
	player = new Player(10, 50);
	this->currentLocation = locations::city;
	city = new City{ mode,window };
	shop = new Shop{ mode,window,player };
	museum = new Museum{ mode,window,player };
	base = new Base{ mode,window,player };
}

Gameplay::~Gameplay()
{
	Game::autoSave(player);

	delete city;
	delete shop;
	delete player;
	delete museum;
	delete base;
}

void Gameplay::render(sf::RenderWindow* window)
{
	if (Gameplay::currentLocation != locations::base)
	{
		sf::View view = window->getView();
		view.setSize({ 400.0f, 300.0f });

		sf::Vector2f playerCenter = player->body->getGlobalBounds().getCenter();

		float mapWidth;
		float mapHeight;

		switch (Gameplay::currentLocation)
		{
		case Gameplay::locations::city:
		{
			mapWidth = 30 * 16;
			mapHeight = 30 * 16;
			break;
		}
		case Gameplay::locations::shop:
		{
			mapWidth = 15 * 16;
			mapHeight = 15 * 16;
			break;
		}
		case Gameplay::locations::museum:
		{
			mapWidth = 16 * 16;
			mapHeight = 22 * 16;
			break;
		}
		}

		const float viewWidth = view.getSize().x;
		const float viewHeight = view.getSize().y;

		if (mapWidth <= viewWidth || mapHeight <= viewHeight) {
			view.setCenter({ mapWidth / 2.0f, mapHeight / 2.0f });
		}
		else {
			float minX = viewWidth / 2.0f;
			float maxX = mapWidth - viewWidth / 2.0f;
			float minY = viewHeight / 2.0f;
			float maxY = mapHeight - viewHeight / 2.0f;

			float clampedX = std::clamp(playerCenter.x, minX, maxX);
			float clampedY = std::clamp(playerCenter.y, minY, maxY);

			view.setCenter({ clampedX, clampedY });
		}
		window->setView(view);

		switch (currentLocation)
		{
		case locations::city:
		{
			city->render(window);
			break;
		}
		case locations::shop:
		{
			shop->render(window);
			break;
		}
		case locations::museum:
		{
			museum->render(window);
			break;
		}
		}
		player->render(window);
		window->setView(window->getDefaultView());
	}
	else
	{
		window->setView(window->getDefaultView());
		base->render(window);
	}
}

void Gameplay::handleEvent(sf::Event& event, sf::RenderWindow* window, float deltaTime)
{
	switch (currentLocation)
	{
	case locations::city:
	{
		city->handleEvent(event, window, deltaTime);
		break;
	}
	case locations::shop:
	{
		shop->handleEvent(event, window, deltaTime);
		break;
	}
	case locations::base:
		{
		base->handleEvent(event, window);
		}
	}
	if (Gameplay::currentLocation != locations::base)
		player->handleEvent(event, window, city->collisionLayer, deltaTime, shop);
}

void Gameplay::update(float& deltaTime, sf::VideoMode& mode, sf::RenderWindow* window)
{
	if (!player->getMoney())
		Game::gameOver(mode, window);
	else
	{
		if (Gameplay::currentLocation != locations::base)
			player->update(deltaTime, city, shop, museum);
	}
}