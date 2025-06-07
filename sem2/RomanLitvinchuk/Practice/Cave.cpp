#include "Cave.h"
#include <random>
#include "Inventory.h"


CellStone::CellStone()
	: currentBone("", 0, 0)
{
	shape.setSize({ 50, 50 });
	CellTexture.loadFromFile("Stone.jpg");
	DugCellTexture.loadFromFile("DugStone.png");
	TakeBoneTexture.loadFromFile("TakeBoneStone.png");
	BreakBoneTexture.loadFromFile("BreakBoneStone.png");
}

bool CellStone::dig(Bone& outbone, Player& player)
{
	if (player.getPickaxe())
	{
		if (type == TypeStone::Bone)
		{
			player.setEnergy(-5);
			if (player.getBrush())
			{
				type = TypeStone::TakeBone;
				outbone = currentBone;
				return true;
			}
			else
			{
				type = TypeStone::BreakBone;
			}
		}
		else if (type == TypeStone::Empty)
		{
			type = TypeStone::Dug;
			player.setEnergy(-5);
		}

	}
	return false;
}


void CellStone::setBone(Bone& bone)
{
	currentBone = bone;
	type = TypeStone::Bone;
}


void CellStone::draw(sf::RenderWindow& window)
{
	if (type == TypeStone::Empty or type == TypeStone::Bone)
	{
		shape.setTexture(&CellTexture);

	}
	else if (type == TypeStone::Dug) { shape.setTexture(&DugCellTexture); }
	else if (type == TypeStone::TakeBone) { shape.setTexture(&TakeBoneTexture); }
	else if (type == TypeStone::BreakBone) { shape.setTexture(&BreakBoneTexture); }
	window.draw(shape);
}

bool CellStone::contains(sf::Vector2f point) const
{
	return shape.getGlobalBounds().contains(point);
}

void CellStone::setPosition(float x, float y)
{
	shape.setPosition(x, y);
}


CaveState::CaveState()
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

void CaveState::initializeGrid()
{
	grid.clear();
	grid.resize(5, std::vector<CellStone>(5));

	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			grid[y][x].setPosition(x * 50.f + 650, y * 50.f + 300);
		}
	}
}

void CaveState::spawnBones()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 4); //20%

	Bone rareBone("Rare_Bone", 4, 10);
	Bone epicBone("Epic_Bone", 5, 175);
	Bone LegendaryBone("Legendary_Bone", 6, 200);

	for (auto& row : grid)
	{
		for (auto& cell : row)
		{
			if (dist(gen) == 0)
			{
				if (dist(gen) % 2 == 0) {
					cell.setBone(rareBone);
				}
				else {
					if (dist(gen) % 3 == 0)
					{
						cell.setBone(epicBone);
					}
					else { cell.setBone(LegendaryBone); }
				}
			}
		}
	}
}


void CaveState::handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save)
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

void CaveState::render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory)
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

void CaveState::reset()
{
	grid.clear();
	initializeGrid();
	spawnBones();
}