#include <SFML/Graphics.hpp>
#include "States.h"
#include "Forest.h"
#include "Cave.h"
#include "PlayerHUD.h"
#include "Inventory.h"



void Button::draw(sf::RenderWindow& window) const
{
	if (isVisible)
	{
		window.draw(ShapeButton);
		window.draw(TextButton);
	}
}

bool Button::isClicked(sf::RenderWindow& window) const
{
	sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePosI.x), static_cast<float>(mousePosI.y));
	return isVisible and ShapeButton.getGlobalBounds().contains(mousePosF);
}


StartMenuState::StartMenuState() {

	BackgroundTexture.loadFromFile("Background.jpg");
	Background.setTexture(BackgroundTexture);
	font.loadFromFile("mine.ttf");
	NewGameButton.ShapeButton.setSize({ 200.f, 50.f });
	NewGameButton.ShapeButton.setPosition(700, 400);
	NewGameButton.TextureButton.loadFromFile("Button.png");
	NewGameButton.ShapeButton.setTexture(&NewGameButton.TextureButton);
	NewGameButton.TextButton.setFont(font);
	NewGameButton.TextButton.setString(L"Новая игра");
	NewGameButton.TextButton.setCharacterSize(18);
	NewGameButton.TextButton.setFillColor(sf::Color::Black);
	NewGameButton.TextButton.setPosition(715, 413);

	LoadButton.ShapeButton.setSize({ 200.f, 50.f });
	LoadButton.ShapeButton.setPosition(700, 460);
	LoadButton.TextureButton.loadFromFile("Button.png");
	LoadButton.ShapeButton.setTexture(&LoadButton.TextureButton);
	LoadButton.TextButton.setFont(font);
	LoadButton.TextButton.setString(L"Сохранение");
	LoadButton.TextButton.setCharacterSize(18);
	LoadButton.TextButton.setFillColor(sf::Color::Black);
	LoadButton.TextButton.setPosition(710, 473);
}
	
void StartMenuState::handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
	{
		if (NewGameButton.isClicked(window))
		{
			game.changeState(GameState::HubMenu);
		}
		if (LoadButton.isClicked(window)) 
		{
			save.loadGame(player, inventory);
			game.changeState(GameState::HubMenu);
		}
	}
}

void StartMenuState::render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) 
{
	window.draw(Background);
	NewGameButton.draw(window);
	LoadButton.draw(window);
}

HubMenuState::HubMenuState()
{
	font.loadFromFile("mine.ttf");
	BackgroundTexture.loadFromFile("Background.jpg");
	ButtonTexture.loadFromFile("Button.png");
	SaveTexture.loadFromFile("Save.png");
	Background.setTexture(BackgroundTexture);
	ShopButton.ShapeButton.setSize({ 200.f, 50.f });
	ShopButton.ShapeButton.setTexture(&ButtonTexture);
	ShopButton.ShapeButton.setPosition(300, 600);
	ShopButton.TextButton.setFont(font);
	ShopButton.TextButton.setCharacterSize(18);
	ShopButton.TextButton.setString(L"Магазин");
	ShopButton.TextButton.setPosition(335, 615);
	ShopButton.TextButton.setFillColor(sf::Color::Black);

	LocationsButton.ShapeButton.setSize({ 200.f, 50.f });
	LocationsButton.ShapeButton.setTexture(&ButtonTexture);
	LocationsButton.ShapeButton.setPosition(700, 600);
	LocationsButton.TextButton.setFont(font);
	LocationsButton.TextButton.setCharacterSize(18);
	LocationsButton.TextButton.setString(L"Экспедиция");
	LocationsButton.TextButton.setPosition(710, 615);
	LocationsButton.TextButton.setFillColor(sf::Color::Black);


	MuseumButton.ShapeButton.setSize({ 200.f, 50.f });
	MuseumButton.ShapeButton.setTexture(&ButtonTexture);
	MuseumButton.ShapeButton.setPosition(1100, 600);
	MuseumButton.TextButton.setFont(font);
	MuseumButton.TextButton.setCharacterSize(18);
	MuseumButton.TextButton.setString(L"Музей");
	MuseumButton.TextButton.setPosition(1150, 615);
	MuseumButton.TextButton.setFillColor(sf::Color::Black);

	InventoryButton.ShapeButton.setSize({ 200, 50 });
	InventoryButton.ShapeButton.setPosition(460, 800);
	InventoryButton.ShapeButton.setTexture(&ButtonTexture);
	InventoryButton.TextButton.setFont(font);
	InventoryButton.TextButton.setCharacterSize(18);
	InventoryButton.TextButton.setString(L"Инвентарь");
	InventoryButton.TextButton.setPosition(480, 815);
	InventoryButton.TextButton.setFillColor(sf::Color::Black);

	SaveButton.ShapeButton.setSize({ 100,100 });
	SaveButton.ShapeButton.setPosition(1500, 800);
	SaveButton.ShapeButton.setTexture(&SaveTexture);


}

void HubMenuState::handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
	{
		if (ShopButton.isClicked(window))
		{
			game.changeState(GameState::ShopMenu);
		}
		if (LocationsButton.isClicked(window)) 
		{
			game.changeState(GameState::Locations);
		}
		if (MuseumButton.isClicked(window)) 
		{
			game.changeState(GameState::MuseumMenu);
		}
		if (InventoryButton.isClicked(window)) 
		{
			inventory.toggleVisibility();
		}
		if (SaveButton.isClicked(window)) 
		{
			save.saveGame(player, inventory);
		}
	}
}

void HubMenuState::render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory)
{
	window.draw(Background);
	hud.draw(window);
	ShopButton.draw(window);
	LocationsButton.draw(window);
	MuseumButton.draw(window);
	InventoryButton.draw(window);
	SaveButton.draw(window);
	if (inventory.getVisibility()) 
	{
		inventory.draw(window);
	}
}

LocationsState::LocationsState() 
{
	font.loadFromFile("mine.ttf");
	BackgroundTexture.loadFromFile("Background.jpg");
	Background.setTexture(BackgroundTexture);

	ForestButton.ShapeButton.setSize({200,50});
	ForestButton.ShapeButton.setPosition(300, 400);
	ForestButton.TextureButton.loadFromFile("Button.png");
	ForestButton.ShapeButton.setTexture(&ForestButton.TextureButton);
	ForestButton.TextButton.setFont(font);
	ForestButton.TextButton.setCharacterSize(18);
	ForestButton.TextButton.setString(L"Лес");
	ForestButton.TextButton.setFillColor(sf::Color::Black);
	ForestButton.TextButton.setPosition(365, 415);

	CaveButton.ShapeButton.setSize({ 200,50 });
	CaveButton.ShapeButton.setPosition(800, 400);
	CaveButton.TextureButton.loadFromFile("Button.png");
	CaveButton.ShapeButton.setTexture(&CaveButton.TextureButton);
	CaveButton.TextButton.setFont(font);
	CaveButton.TextButton.setCharacterSize(18);
	CaveButton.TextButton.setFillColor(sf::Color::Black);
	CaveButton.TextButton.setString(L"Пещера");
	CaveButton.TextButton.setPosition(837, 415);

	HubButton.ShapeButton.setSize({ 200,50 });
	HubButton.TextureButton.loadFromFile("Button.png");
	HubButton.ShapeButton.setTexture(&HubButton.TextureButton);
	HubButton.ShapeButton.setPosition(100, 100);
	HubButton.TextButton.setFont(font);
	HubButton.TextButton.setCharacterSize(18);
	HubButton.TextButton.setString(L"В хаб");
	HubButton.TextButton.setFillColor(sf::Color::Black);
	HubButton.TextButton.setPosition(130, 110);
}

void LocationsState::handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) 
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
	{
		if (ForestButton.isClicked(window)) 
		{
			game.changeState(GameState::Forest);
		}
		if (CaveButton.isClicked(window)) 
		{
			game.changeState(GameState::Cave);
		}
		if (HubButton.isClicked(window)) 
		{
			game.changeState(GameState::HubMenu);
		}
	}
}

void LocationsState::render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) 
{
	window.draw(Background);
	ForestButton.draw(window);
	CaveButton.draw(window);
	HubButton.draw(window);
}

GameOverState::GameOverState() 
{
	font.loadFromFile("mine.ttf");

	text.setFont(font);
	text.setCharacterSize(24);
	text.setString("GAME OVER");
	text.setFillColor(sf::Color::White);
	text.setPosition(700, 300);
}

void GameOverState::handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) {};

void GameOverState::render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) 
{
	window.draw(text);
}



StateMachine::StateMachine() {
	states[GameState::StartMenu] = std::make_unique<StartMenuState>();
	states[GameState::HubMenu] = std::make_unique<HubMenuState>();
	states[GameState::ShopMenu] = std::make_unique<ShopMenuState>();
	states[GameState::Forest] = std::make_unique<ForestState>();
	states[GameState::MuseumMenu] = std::make_unique<MuseumState>();
	states[GameState::Locations] = std::make_unique<LocationsState>();
	states[GameState::Cave] = std::make_unique<CaveState>();
	states[GameState::GameOver] = std::make_unique<GameOverState>();
	CurrentState = GameState::StartMenu;
}

void StateMachine::changeState(GameState NewState)
{
	CurrentState = NewState;
}

void StateMachine::handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save)
{
	states[CurrentState]->handleEvents(window, event, game, player, inventory, save);
}
void StateMachine::render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory)
{
	states[CurrentState]->render(window, hud, inventory);
}
