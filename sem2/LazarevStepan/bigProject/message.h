#pragma once
#include "game.h"

class Message
{
public:
	Message(std::string&& str,sf::VideoMode& mode_);

	static inline sf::Font font{ "../fonts/KenneyBlocks.ttf" };
	sf::Text name{ font };
	sf::Texture* backgroundTexture;
	sf::Sprite* background;

	sf::VideoMode mode;

	void render(sf::RenderWindow* window);

	Message& operator=(str&& string);
};

