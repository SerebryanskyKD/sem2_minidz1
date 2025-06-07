#include <SFML/Graphics.hpp>
#include "States.h"
#include "PlayerHUD.h";
#include "Player.h"
#include "Inventory.h"
#include "SaveManager.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1600, 900 }), "Practice");
	StateMachine game;
	Player player;
	SaveManager save;
	PlayerHUD hud(player);
	Inventory inventory;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			game.handleEvents(window, event, game, player, inventory, save);
		}

		window.clear();
		game.render(window, hud, inventory);
		window.display();
	}
};