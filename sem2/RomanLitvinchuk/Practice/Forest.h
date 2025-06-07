#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Inventory.h"
#include "States.h"

enum class Type { Empty, Bone, Dug, BreakBone, TakeBone };

class Cell 
{
private:

	sf::RectangleShape shape;
	sf::Texture CellTexture;
	sf::Texture DugCellTexture;
	sf::Texture CellBoneTexture;
	sf::Texture TakeBoneTexture;
	sf::Texture BreakBoneTexture;
	Type type = Type::Empty;
	Bone currentBone;
public:

	Cell();
	bool dig(Bone& outbone, Player& player);
	void setBone(Bone& bone);
	void setPosition(float x, float y);
	void draw(sf::RenderWindow& window);
	bool contains(sf::Vector2f point) const;
	bool hasBone() { return type == Type::Bone; }
	bool isDug() { return type == Type::Dug; }
};

class ForestState : public State
{
private:
	std::vector<std::vector<Cell>> grid;
	std::vector<Bone> BoneTypes;
	Button HubButton;
	Button ShovelButton;
	Button BrushButton;
public:
	ForestState();
	void reset();
	void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) override;
	void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) override;
	void initializeGrid();
	void spawnBones();

};