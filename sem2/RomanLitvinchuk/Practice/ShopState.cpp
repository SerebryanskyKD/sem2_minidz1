#include "States.h"
#include "Inventory.h"

ShopMenuState::ShopMenuState()
{
	BackgroundTexture.loadFromFile("Background.jpg");
	Background.setTexture(BackgroundTexture);

	font.loadFromFile("mine.ttf");

	ButtonTexture.loadFromFile("Button.png");
	shovelTexture.loadFromFile("shovel.png");
	BrushTexture.loadFromFile("brush.png");
	PickaxeTexture.loadFromFile("pickaxe.png");
	SmallFoodTexture.loadFromFile("SmallFood.png");
	CommonFoodTexture.loadFromFile("CommonFood.png");
	BigFoodTexture.loadFromFile("BigFood.png");

	HubButton.ShapeButton.setSize({ 200, 50 });
	HubButton.ShapeButton.setPosition({ 100, 100 });
	HubButton.ShapeButton.setTexture(&ButtonTexture);
	HubButton.TextButton.setFont(font);
	HubButton.TextButton.setCharacterSize(18);
	HubButton.TextButton.setString(L"В хаб");
	HubButton.TextButton.setPosition(160, 115);
	HubButton.TextButton.setFillColor(sf::Color::Black);

	ShovelButton.ShapeButton.setSize({ 100, 100 });
	ShovelButton.ShapeButton.setTexture(&shovelTexture);
	ShovelButton.ShapeButton.setPosition({ 300, 200 });
	ShovelButton.TextButton.setFont(font);
	ShovelButton.TextButton.setString(L"Лопата \nЦена: 20");
	ShovelButton.TextButton.setPosition({ 400, 200 });

	BrushButton.ShapeButton.setSize({ 100, 100 });
	BrushButton.ShapeButton.setTexture(&BrushTexture);
	BrushButton.ShapeButton.setPosition({ 300, 350 });
	BrushButton.TextButton.setFont(font);
	BrushButton.TextButton.setString(L"Кисточка \nЦена: 20");
	BrushButton.TextButton.setPosition({ 400, 350 });

	PickaxeButton.ShapeButton.setSize({ 100, 100 });
	PickaxeButton.ShapeButton.setTexture(&PickaxeTexture);
	PickaxeButton.ShapeButton.setPosition({ 300, 500 });
	PickaxeButton.TextButton.setFont(font);
	PickaxeButton.TextButton.setString(L"Кирка \nЦена: 50");
	PickaxeButton.TextButton.setPosition({ 400, 500 });

	SmallFoodButton.ShapeButton.setSize({ 100, 100 });
	SmallFoodButton.ShapeButton.setTexture(&SmallFoodTexture);
	SmallFoodButton.ShapeButton.setPosition({ 1000, 200 });
	SmallFoodButton.TextButton.setFont(font);
	SmallFoodButton.TextButton.setString(L"Перекус \nЦена: 10\n20 энергии");
	SmallFoodButton.TextButton.setPosition({ 1100, 200 });

	CommonFoodButton.ShapeButton.setSize({ 100, 100 });
	CommonFoodButton.ShapeButton.setTexture(&CommonFoodTexture);
	CommonFoodButton.ShapeButton.setPosition({ 1000, 350 });
	CommonFoodButton.TextButton.setFont(font);
	CommonFoodButton.TextButton.setString(L"Завтрак\nЦена: 25\n50 энергии");
	CommonFoodButton.TextButton.setPosition({ 1100, 350 });

	BigFoodButton.ShapeButton.setSize({ 100, 100 });
	BigFoodButton.ShapeButton.setTexture(&BigFoodTexture);
	BigFoodButton.ShapeButton.setPosition({ 1000, 500 });
	BigFoodButton.TextButton.setFont(font);
	BigFoodButton.TextButton.setString(L"Пицца\nЦена: 40\n80 энергии");
	BigFoodButton.TextButton.setPosition({ 1100,500 });

	SellButton.ShapeButton.setSize({ 200,50 });
	SellButton.ShapeButton.setPosition(700, 650);
	SellButton.ShapeButton.setTexture(&ButtonTexture);
	SellButton.TextButton.setFont(font);
	SellButton.TextButton.setCharacterSize(18);
	SellButton.TextButton.setString(L"Продать всё");
	SellButton.TextButton.setPosition(705, 665);
	SellButton.TextButton.setFillColor(sf::Color::Black);

	bg.setSize({1250, 450});
	bg.setFillColor(sf::Color(0, 0, 0, 200));
	bg.setPosition(250, 190);
	bg.setOutlineThickness(2);

}

void ShopMenuState::handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) 
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
	{
		if (ShovelButton.isClicked(window) and !player.getShovel() and player.getMoney()>=20)
		{
			player.setMoney(-20);
			player.setShovel();
		}
		if (BrushButton.isClicked(window) and !player.getBrush() and player.getMoney()>=20)
		{
			player.setMoney(-20);
			player.setBrush();
		}
		if (PickaxeButton.isClicked(window) and !player.getPickaxe() and player.getMoney()>=50)
		{
			player.setMoney(-50);
			player.setPickaxe();
		}
		if (SmallFoodButton.isClicked(window) and player.getMoney()>=10)
		{
			player.setMoney(-10);
			player.setEnergy(20);
		}
		if (CommonFoodButton.isClicked(window) and player.getMoney()>=25)
		{
			player.setMoney(-25);
			player.setEnergy(50);
		}
		if (BigFoodButton.isClicked(window) and player.getMoney()>=40)
		{
			player.setMoney(-40);
			player.setEnergy(80);
		}
		if (player.getMoney() == 0) 
		{
			game.changeState(GameState::GameOver);
		}
		if (HubButton.isClicked(window))
		{
			game.changeState(GameState::HubMenu);
		}
		if (SellButton.isClicked(window)) 
		{
			int count = inventory.getSize();
			int sum = 0;
			for (int i = 0; i != count; ++i) 
			{
				Bone currentBone = inventory.getBone();
				sum += currentBone.getCost();
			}
			player.setMoney(sum);
			inventory.reset();
		}
	}
}

void ShopMenuState::render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) 
{
	window.draw(Background);
	hud.draw(window);
	window.draw(bg);
	HubButton.draw(window);
	SellButton.draw(window);
	ShovelButton.draw(window);
	BrushButton.draw(window);
	PickaxeButton.draw(window);
	SmallFoodButton.draw(window);
	CommonFoodButton.draw(window);
	BigFoodButton.draw(window);
}