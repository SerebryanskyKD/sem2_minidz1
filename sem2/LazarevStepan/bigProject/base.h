#pragma once
#include "player.h"
#include "game.h"
#include <limits>
#include "excavations.h"

class Excavation;

class Base {
private:
	Player* player;
public:
	Excavation* excavation;
	std::vector<Button*> buttons;
	static inline sf::Font font{ "../fonts/KenneyBlocks.ttf" };
	sf::Text playerInfo{ font };

	bool isClicked = false;

	Base(sf::VideoMode& mode, sf::RenderWindow* window,Player* player);

	void render(sf::RenderWindow* window);

	void handleEvent(sf::Event& event, sf::RenderWindow* window);
};