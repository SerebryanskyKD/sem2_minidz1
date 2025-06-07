#include "Forest.h"
#include <random>
#include "Inventory.h"


Cell::Cell()
	: currentBone("", 0, 0)
{
	shape.setSize({ 50, 50 });
	//shape.setFillColor(sf::Color::Red);
	CellTexture.loadFromFile("cell.png");
	DugCellTexture.loadFromFile("DugCell.png");
	CellBoneTexture.loadFromFile("CellBone.jpg");
	TakeBoneTexture.loadFromFile("TakeBone.png");
	BreakBoneTexture.loadFromFile("BreakBone.png");
}

bool Cell::dig(Bone& outbone, Player& player)
{
	if (player.getShovel())
	{
		if (type == Type::Bone)
		{
			player.setEnergy(-5);
			if (player.getBrush())
			{
				type = Type::TakeBone;
				outbone = currentBone;
				return true;
			}
			else 
			{
				type = Type::BreakBone;
			}
		}
		else if (type == Type::Empty)
		{
			type = Type::Dug;
			player.setEnergy(-5);
		}

	}
	return false;
}
	

void Cell::setBone(Bone& bone) 
{
	currentBone = bone;
	type = Type::Bone;
}


void Cell::draw(sf::RenderWindow& window)
{
	if (type == Type::Empty or type==Type::Bone)
	{
		shape.setTexture(&CellTexture);

	}
	else if (type == Type::Dug) { shape.setTexture(&DugCellTexture); }
	else if (type == Type::TakeBone) { shape.setTexture(&TakeBoneTexture); }
	else if (type == Type::BreakBone) { shape.setTexture(&BreakBoneTexture); }
	window.draw(shape);
}

bool Cell::contains(sf::Vector2f point) const 
{
	return shape.getGlobalBounds().contains(point);
}

void Cell::setPosition(float x, float y) 
{
	shape.setPosition(x, y);
}


ForestState::ForestState()
{
	HubButton.ShapeButton.setSize({ 100 , 100 });
	HubButton.ShapeButton.setPosition(1400, 500);
	HubButton.ShapeButton.setFillColor(sf::Color::Red);

	ShovelButton.ShapeButton.setSize({ 200, 50 });
	ShovelButton.ShapeButton.setPosition(1400, 650);
	ShovelButton.ShapeButton.setFillColor(sf::Color::Red);
	initializeGrid();
	spawnBones();
}

void ForestState::initializeGrid()
{
	grid.clear();
	grid.resize(5, std::vector<Cell>(5));

	//Размещаем кости случайным образом

	for (int y = 0; y < 5; ++y) 
	{
		for (int x = 0; x < 5; ++x) 
		{
			grid[y][x].setPosition(x * 50.f+650, y * 50.f+300);
		}
	}
}

void ForestState::spawnBones() 
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 4); //20%

	Bone smallBone("Small_Bone", 1, 50);
	Bone commonBone("Common_Bone", 2, 75);
	Bone bigBone("Big_Bone", 3, 100);

	for (auto& row : grid)
	{
		for (auto& cell : row) 
		{
			if (dist(gen) == 0)
			{
				if (dist(gen) % 2 == 0) {
					cell.setBone(smallBone);
				}
				else {
					if (dist(gen) % 3 == 0)
					{
						cell.setBone(commonBone);
					}
					else { cell.setBone(bigBone); }
				}
			}
		}
	}
}


void ForestState::handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) 
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosF(static_cast<float>(mousePosI.x), static_cast<float>(mousePosI.y));

		for (auto& row : grid)
		{
			for (auto& cell : row)
			{
				if (cell.contains(mousePosF))
				{
					Bone dugBone("", 0, 0);
					cell.dig(dugBone, player);
					if (player.getEnergy() == 0)
					{
						game.changeState(GameState::HubMenu);
						reset();
					}
					if (dugBone.getID() != 0) {
						inventory.addBone(dugBone);
						if (dugBone.getID() == 1) { player.setSB(); }
						else if (dugBone.getID() == 2) { player.setCB(); }
						else if (dugBone.getID() == 3) { player.setBB(); }
					}
				}
			}
		}
			if (HubButton.isClicked(window))
			{
				game.changeState(GameState::HubMenu);
				reset();
			}
	}

}


void ForestState::render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory)
{
	hud.draw(window);
	for (auto& row : grid)
	{
		for (auto& cell : row)
		{
			cell.draw(window);
		}
	}
}

void ForestState::reset() 
{
	grid.clear();
	initializeGrid();
	spawnBones();
}