#include "game.h"

Game::state Game::currentState;
Options* Game::options;
mainMenu* Game::menu;
Gameplay* Game::gameplay;

void Game::initializeVariables()
{
	this->window = nullptr;
	this->options = nullptr;
	this->menu = nullptr;
	this->gameplay = nullptr;
	this->ev = std::nullopt;
	currentState = state::main_menu;
}


void Game::initWindow()
{
	this->videoMode.size = sf::Vector2u(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Sweaty Archaeologists 2");
	this->window->setFramerateLimit(60);

}

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	menu = new mainMenu(this->videoMode, this->window);
}

Game::~Game()
{
	delete options;
	delete menu;
	delete gameplay;
	delete window;

	options = nullptr;
	menu = nullptr;
	gameplay = nullptr;
	window = nullptr;
}

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::handleEvent(float& deltaTime)
{
	
	while (this->ev = this->window->pollEvent())
	{
		if (ev->is<sf::Event::Closed>())
			window->close();

		if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>())
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				window->close();

		if (options && options->deleteFlag)
		{
			delete options;
			options = nullptr;
		}

		if (menu && menu->deleteFlag)
		{
			delete menu;
			menu = nullptr;
		}

		if (gameplay && gameplay->deleteFlag)
		{
			delete gameplay;
			gameplay = nullptr;
		}

		switch (currentState)
		{
		case state::main_menu:
		{
			menu->handleEvent(ev.value(), window);
			break;
		}
		case state::options:
		{
			options->handleEvent(ev.value(), window);
			break;
		}
		case state::game_play:
		{
			gameplay->handleEvent(ev.value(), window, deltaTime);
			break;
		}
		}
	}
}


void Game::update(float& deltaTime)
{
	switch (currentState)
	{
	case state::game_play:
	{
		gameplay->update(deltaTime,videoMode,window);
		break;
	}
	}
}


void Game::render()
{
	if (window)
	{
		this->window->clear();

		switch (currentState)
		{
		case state::main_menu:
		{
			menu->render(window);
			break;
		}
		case state::options:
		{
			options->render(window);
			break;
		}
		case state::game_play:
		{
			gameplay->render(window);
			break;
		}
		}

		this->window->display();
	}
}

void Game::loadSave(Player* player) {
		std::ifstream in("playerSettings.txt");

		str line;

		std::getline(in, line);

		std::stringstream ss(line);
		int money, food;

		ss >> money >> food;

		player->setMoney(money);
		player->setFood(food);

		while (std::getline(in, line)) {
			std::stringstream ss(line);
			str item;
			int amount;

			ss >> item >> amount;
			player->getEquipment()[item] = amount;
		}

		in.close();
}

void Game::autoSave(Player* player) {
		std::ofstream out("playerSettings.txt", std::ios::trunc);

		out << player->getMoney() << " " << player->getFood() << "\n";

		for (const auto& item : player->getEquipment())
		{
			out << item.first << " " << item.second << "\n";
		}

		out.close();

}

void Game::gameOver(sf::VideoMode videoMode, sf::RenderWindow* window) {

	Message fail("FINANCING IS CUT - GAME OVER!", videoMode);

	window->clear();
	fail.render(window);
	window->display();
	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::ofstream out1("playerSettings.txt", std::ios::trunc);
	std::ofstream out2("playerAchievments.txt", std::ios::trunc);

	out1.close();
	out2.close();

	clearAchievments();

	window->clear();
	window->close();
}

void Game::clearAchievments()
{
	std::ofstream outputFile("playerAchievments.txt",std::ofstream::trunc);
	if (outputFile.is_open()) {
		for (size_t i = 0; i < 9; ++i) {
			if (i != 8)
				outputFile << "0" << "\n";
			else
				outputFile << "0";
		}
		outputFile.close();
	}
}