#pragma once
#include <vector>
#include "../sweatyArc/button.hpp"
#include "game.h"

class Button;

class Options {
private:
	int selectedButton = -1;
	int resolutionButtons = 0;
public:
	std::vector<Button*> buttons;
	bool deleteFlag = false;
	bool resolutionFlag = false;

	Options(sf::VideoMode& mode, sf::RenderWindow* window);

	~Options();

	void render(sf::RenderWindow* window);

	void handleEvent(sf::Event& event, sf::RenderWindow* window);
};