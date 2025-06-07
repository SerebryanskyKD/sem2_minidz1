#include "base.h"

Base::Base(sf::VideoMode& mode, sf::RenderWindow* window, Player* player) :player(player)
{
	excavation = nullptr;

	std::stringstream ss1;
	ss1 << "Excavation underwater\n" << "Price: " << ExcavationUnderWater::cost << "\n" << "Food cost: " << ExcavationUnderWater::cost_food;
	std::stringstream ss2;
	ss2 << "Excavation in Vulkano\n" << "Price: " << ExcavationVulkano::cost << "\n" << "Food cost: " << ExcavationVulkano::cost_food;
	std::stringstream ss3;
	ss3 << "Excavation on Moon\n" << "Price: " << ExcavationMoon::cost << "\n" << "Food cost: " << ExcavationMoon::cost_food;

	Button* water = new Button(ss1.str(), [this, window, &mode]()
		{
			if (Excavation::checkPlayer<ExcavationUnderWater>(this->player))
			{
				this->excavation = new ExcavationUnderWater(this->player, mode, window);
				isClicked = true;
			}
		});
	Button* vulkan = new Button(ss2.str(), [this, window, &mode]()
		{
			if (Excavation::checkPlayer<ExcavationVulkano>(this->player))
			{
				this->excavation = new ExcavationVulkano(this->player, mode, window);
				isClicked = true;
			}
		});
	Button* moon = new Button(ss3.str(), [this, window, &mode]()
		{
			if (Excavation::checkPlayer<ExcavationMoon>(this->player))
			{
				this->excavation = new ExcavationMoon(this->player, mode, window);
				isClicked = true;
			}
		});
	Button* exit = new Button("Exit", [this, window, &mode]()
		{
			Gameplay::currentLocation = Gameplay::locations::city;
		});

	buttons.push_back(water);
	buttons.push_back(vulkan);
	buttons.push_back(moon);
	buttons.push_back(exit);

	for (auto& button : buttons)
	{
		button->setScale({ 0.4f,0.4f });
	}

	Button::placeHorizontal(mode,buttons);

	std::stringstream ss;
	ss << "Money: " << player->getMoney() << "\nFood: " << player->getFood();

	playerInfo.setString(ss.str());
	playerInfo.setCharacterSize(20);
	playerInfo.setFillColor(sf::Color::White);
	playerInfo.setPosition({ mode.size.x / 2.0f - 100, mode.size.y / 4.0f - 80 });

}

void Base::render(sf::RenderWindow* window)
{
	if (!isClicked)
	{
		window->draw(playerInfo);
		for (auto& button : buttons)
			button->render(window);
	}
	else
	{
		excavation->render(window);
		std::stringstream ss;
		ss << "Money: " << player->getMoney() << "\nFood: " << player->getFood();
		playerInfo.setString(ss.str());
		isClicked = false;
	}
}

void Base::handleEvent(sf::Event& event, sf::RenderWindow* window)
{
	std::stringstream ss;
	ss << "Money: " << player->getMoney() << "\nFood: " << player->getFood();
	playerInfo.setString(ss.str());

	for (auto& button:buttons)
	{
		button->handleEvent(event, window);
	}
}