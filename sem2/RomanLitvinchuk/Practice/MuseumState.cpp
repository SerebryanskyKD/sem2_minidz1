#include "States.h"

MuseumState::MuseumState() 
{
	font.loadFromFile("mine.ttf");
	BackgroundTexture.loadFromFile("Background.jpg");
	Background.setTexture(BackgroundTexture);
	UnknownBone.loadFromFile("UnknownBone.png");

	SmallBone.ShapeButton.setSize({ 100,100 });
	SmallBone.ShapeButton.setPosition(200, 300);
	SmallBone.TextureButton.loadFromFile("SmallBone.png");

	CommonBone.ShapeButton.setSize({ 100,100 });
	CommonBone.ShapeButton.setPosition(500, 300);
	CommonBone.TextureButton.loadFromFile("CommonBone.png");

	BigBone.ShapeButton.setSize({ 100,100 });
	BigBone.ShapeButton.setPosition(800, 300);
	BigBone.TextureButton.loadFromFile("BigBone.png");

	RareBone.ShapeButton.setSize({ 100,100 });
	RareBone.ShapeButton.setPosition(200, 600);
	RareBone.TextureButton.loadFromFile("RareBone.png");

	EpicBone.ShapeButton.setSize({ 100,100 });
	EpicBone.ShapeButton.setPosition(500, 600);
	EpicBone.TextureButton.loadFromFile("EpicBone.png");

	LegendaryBone.ShapeButton.setSize({ 100,100 });
	LegendaryBone.ShapeButton.setPosition(800, 600);
	LegendaryBone.TextureButton.loadFromFile("LegendaryBone.png");


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

void MuseumState::handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) 
{
	if (player.getSB()) { SmallBone.ShapeButton.setTexture(&SmallBone.TextureButton); }
	else { SmallBone.ShapeButton.setTexture(&UnknownBone); }
	if (player.getCB()) { CommonBone.ShapeButton.setTexture(&CommonBone.TextureButton); }
	else { CommonBone.ShapeButton.setTexture(&UnknownBone); }
	if (player.getBB()) { BigBone.ShapeButton.setTexture(&BigBone.TextureButton); }
	else { BigBone.ShapeButton.setTexture(&UnknownBone); }
	if (player.getRB()) { RareBone.ShapeButton.setTexture(&RareBone.TextureButton); }
	else { RareBone.ShapeButton.setTexture(&UnknownBone); }
	if (player.getEB()) { EpicBone.ShapeButton.setTexture(&EpicBone.TextureButton); }
	else { EpicBone.ShapeButton.setTexture(&UnknownBone); }
	if (player.getLB()) { LegendaryBone.ShapeButton.setTexture(&LegendaryBone.TextureButton); }
	else { LegendaryBone.ShapeButton.setTexture(&UnknownBone); }

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
	{
		if (HubButton.isClicked(window))
		{
			game.changeState(GameState::HubMenu);
		}
	}
}

void MuseumState::render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) 
{
	window.draw(Background);
	HubButton.draw(window);
	SmallBone.draw(window);
	CommonBone.draw(window);
	BigBone.draw(window);
	RareBone.draw(window);
	EpicBone.draw(window);
	LegendaryBone.draw(window);
}

