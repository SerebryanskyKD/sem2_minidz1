#pragma once
#include "Player.h"
#include "PlayerHUD.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Inventory.h"
#include "SaveManager.h"
class StateMachine;

enum class GameState
{
	StartMenu,
	HubMenu,
	ShopMenu,
	MuseumMenu,
	Locations,
	Forest,
	Cave,
	GameOver
};

struct Button
{
	sf::Texture TextureButton;
	sf::RectangleShape ShapeButton;
	sf::Text TextButton;
	bool isVisible;
	void draw(sf::RenderWindow& window) const;
	bool isClicked(sf::RenderWindow& window) const;
};


class State 
{

public:
	sf::Font font;
	sf::Sprite Background;
	sf::Texture BackgroundTexture;
	sf::Texture ButtonTexture;
	virtual void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) = 0;
	virtual void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) = 0;
};

class StartMenuState : public State 
{
	Button NewGameButton;
	Button LoadButton;
public:
	StartMenuState();
	void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) override;
	void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) override;
};

class HubMenuState : public State 
{
	Button ShopButton;
	Button LocationsButton;
	Button MuseumButton;
	Button InventoryButton;
	Button SaveButton;
	sf::Text PlayerStat;
	sf::Texture SaveTexture;
public:
	HubMenuState();
	void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) override;
	void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) override;

};


class StateMachine
{
	std::unordered_map<GameState, std::unique_ptr<State>> states;
	GameState CurrentState;
public:
	StateMachine();
	void changeState(GameState NewState);
	void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save);
	void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory);
};

class ShopMenuState : public State
{
	Button ShovelButton;
	Button BrushButton;
	Button PickaxeButton;
	Button SmallFoodButton;
	Button CommonFoodButton;
	Button BigFoodButton;
	Button HubButton;
	Button SellButton;
	sf::RectangleShape bg;
	sf::Texture shovelTexture;
	sf::Texture BrushTexture;
	sf::Texture PickaxeTexture;
	sf::Texture SmallFoodTexture;
	sf::Texture CommonFoodTexture;
	sf::Texture BigFoodTexture;
public:
	ShopMenuState();
	void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) override;
	void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) override;
};

class MuseumState : public State 
{
	Button SmallBone;
	Button CommonBone;
	Button BigBone;
	Button RareBone;
	Button EpicBone;
	Button LegendaryBone;
	sf::Texture UnknownBone;
	Button HubButton;
public:
	MuseumState();
	void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) override;
	void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) override;
};

class LocationsState : public State
{
	Button ForestButton;
	Button CaveButton;
	Button HubButton;

public:
	LocationsState();
	void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) override;
	void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) override;
};

class GameOverState : public State 
{
	Button StartButton;
	sf::Text text;
public:
	GameOverState();
	void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) override;
	void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) override;
};
