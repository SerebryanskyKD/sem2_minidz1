#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "../states/mainMenu.hpp"
#include "options.hpp"
#include "gameplay.hpp"
#include "json.hpp"
#include "player.h"
#include "base.h"   
#include <sstream>
#include <memory>
#include <string>
#include <fstream>
#include "message.h"

class mainMenu;
class Options;
class Gameplay;
class Message;

class Game {
private:
	sf::RenderWindow* window;
	std::optional<sf::Event> ev;

	void  initializeVariables();
	void  initWindow();
public:
	sf::VideoMode videoMode;

	enum class state { main_menu, game_play, options};
	static state currentState;

	static Options* options;
	static mainMenu* menu;
	static Gameplay* gameplay;

	static void loadSave(Player* player);
	static void autoSave(Player* player);
	static void gameOver(sf::VideoMode videoMode, sf::RenderWindow* window);
	static void clearAchievments();

	Game();
	~Game();

	const bool getWindowIsOpen() const;

	void handleEvent(float& deltaTime);
	void render();
	void update(float& deltaTime);
};