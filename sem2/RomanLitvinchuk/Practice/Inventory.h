#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Bone 
{
private:
	std::string name;
	int id;
	int cost;
	//sf::Texture textureBone;
	//sf::Sprite spriteBone;
public:
	Bone(const std::string& name, int id, int cost);
	const std::string& getName() const { return name; }
	int getID() const { return id; }
	int getCost() const { return cost; }
	void setName(std::string& newName) { name = newName; }
	void setID(int newID) { id = newID; }
	void setCost(int newCost) { cost = newCost; }
	//void setPosition(float x, float y) { spriteBone.setPosition(x, y); }
};

class Inventory 
{
private:
	std::vector<Bone> bones;
	sf::Font font;
	sf::Text inventoryText;
	bool isVisible = false;

public:
	Inventory();
	void addBoneSave(int id, std::string& name, int cost);
	void addBone(Bone& bone);
	void toggleVisibility() { isVisible = !isVisible; }
	bool getVisibility() { return isVisible; }
	int getSize() { return bones.size(); }
	void draw(sf::RenderWindow& window);
	Bone getBone();
	void reset();
	std::vector<Bone>& getBones() { return bones; }
};