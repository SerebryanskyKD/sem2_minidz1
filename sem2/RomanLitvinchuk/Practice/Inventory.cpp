#include "Inventory.h"
#include <SFML/Graphics.hpp>
#include <sstream>

Bone::Bone(const std::string& name, int id, int cost)
	: name(name), id(id), cost(cost) {};

Inventory::Inventory() 
{
	font.loadFromFile("mine.ttf");
	inventoryText.setFont(font);
	inventoryText.setCharacterSize(18);
}

void Inventory::addBoneSave(int id, std::string& name, int cost) 
{
	bones.emplace_back(name, id, cost);
}

void Inventory::addBone(Bone& bone) 
{
	bones.push_back(bone);
}
void Inventory::draw(sf::RenderWindow& window) 
{
	if (!isVisible) return;

	sf::RectangleShape bg({ 300, 400 });
	bg.setFillColor(sf::Color(0, 0, 0, 200));
	bg.setOutlineThickness(2);
	bg.setPosition(20, 20);
	window.draw(bg);
	sf::Text title("Inventory", font, 24);
	title.setPosition(30, 30);
	window.draw(title);

	int y = 70;
	int count = 0;
	for (auto& bone : bones) 
	{
		count++;
		if (count > 8) 
		{
			sf::Text enough("...", font, 18);
			window.draw(enough);
			break;
		}
		sf::Text itemText(bone.getName() + "($" + std::to_string(bone.getCost()) + ")", font, 18);
		itemText.setPosition(40, y);
		window.draw(itemText);
		y += 40;
	}
}

Bone Inventory::getBone() 
{
	if (getSize() != 0) 
	{
		return bones[0];
	}
}
void Inventory::reset() 
{
	bones.clear();
}