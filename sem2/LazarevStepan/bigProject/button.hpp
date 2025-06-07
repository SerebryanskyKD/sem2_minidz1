#pragma once
#include "game.h"

class Button {
public:
	Button(std::string str, std::function<void()> funcOnClick);
	~Button();

	static inline int offset = 0;
	static inline sf::Font font{ "../fonts/KenneyBlocks.ttf" };
	sf::Text name{font};
	sf::Texture* backgroundTexture;
	sf::Sprite* background;
	bool isSelected = false;
	std::function<void()> onClick;

	void placeCenter(sf::VideoMode& mode);

	static void placeHorizontal(sf::VideoMode& mode, std::vector<Button*>& buttons);

	void setPosition(sf::Vector2f pos);

	void setScale(sf::Vector2f size);

	void render(sf::RenderWindow* window) const;

	void handleEvent(sf::Event& event, sf::RenderWindow* window);

};