#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Inventory.h"
#include "States.h"

enum class Type { Empty, Bone, Dug };

class Cell 
{
private:

	sf::RectangleShape shape;
	sf::Texture CellTexture;
	sf::Texture DugCellTexture;
	Type type = Type::Empty;
	Bone currentBone;

public:

	Cell();
	bool dig(Bone& outbone);
	void setBone(Bone& bone);
	void setPosition(float x, float y);
	void draw(sf::RenderWindow& window);
	bool contains(sf::Vector2f point) const;
	bool hasBone() { return type == Type::Bone; }
	bool isDug() { return type == Type::Dug; }
};

class GameplayState : public State
{
private:
	std::vector<std::vector<Cell>> grid;
	std::vector<Bone> BoneTypes;
public:
	GameplayState();
	void handleEvents(sf::RenderWindow& window, sf::Event& event, StateMachine& game, Player& player, Inventory& inventory, SaveManager& save) override;
	void render(sf::RenderWindow& window, PlayerHUD& hud, Inventory& inventory) override;
	void initializeGrid();
	void spawnBones();

};