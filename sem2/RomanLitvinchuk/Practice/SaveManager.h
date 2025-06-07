#pragma once
#include "Player.h"
#include "Inventory.h"
#include <vector>
#include <string>

class SaveManager 
{
private:
	std::string SaveFile = "save.txt";
public:
	void saveGame(Player& player, Inventory& inventory);
	void loadGame(Player& player, Inventory& inventory);
};
