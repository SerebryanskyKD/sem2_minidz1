#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Inventory.h"
#include "States.h"

enum class TypeStone { Empty, Bone, Dug, BreakBone, TakeBone };

class CellStone
{
private:

	sf::RectangleShape shape;
	sf::Texture CellTexture;
	sf::Texture DugCellTexture;
	sf::Texture CellBoneTexture;
	sf::Texture TakeBoneTexture;
	sf::Texture BreakBoneTexture;
	TypeStone type = TypeStone::Empty;
	Bone currentBone;
public:

	CellStone();
	bool dig(Bone& outbone, Player& player);
	void setBone(Bone& bone);
	void setPosition(float x, float y);
	void draw(sf::RenderWindow& window);
	bool contains(sf::Vector2f point) const;
	bool hasBone() { return type == TypeStone::Bone; }
	bool isDug() { return type == TypeStone::Dug; }
};

class CaveState : public State
{
private:
	std::vector<std::vector<CellStone>> grid;
	std::vector<Bone> BoneTypes;
	Button HubButton;
	Button ShovelButton;
	Button BrushButton;
public:
	CaveState();
	void reset();
	void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) override;
	void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) override;
	void initializeGrid();
	void spawnBones();

};