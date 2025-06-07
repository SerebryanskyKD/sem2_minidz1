#include "SaveManager.h"
#include <fstream>
#include <sstream>

void SaveManager::saveGame(Player& player, Inventory& inventory)
{
	std::ofstream file(SaveFile);
	if (file.is_open())
	{
		file << player.getEnergy() << "\n";
		file << player.getMoney() << "\n";
		file << player.getShovel() << "\n";
		file << player.getBrush() << "\n";
		file << player.getPickaxe() << "\n";
		file << player.getSB() << "\n";
		file << player.getCB() << "\n";
		file << player.getBB() << "\n";
		file << player.getRB() << "\n";
		file << player.getEB() << "\n";
		file << player.getLB() << "\n";
		file << inventory.getSize() << "\n";
		auto& bones = inventory.getBones();
		for (auto& bone : bones) 
		{
			file << bone.getName() << " " << bone.getID() << " " << bone.getCost() << "\n";
		}
	}
	file.close();
}

void SaveManager::loadGame(Player& player, Inventory& inventory) 
{
	std::ifstream file(SaveFile);
	std::string line;
	int value;
	int count;
	int id, cost;
	bool bvalue;
	std::string name;
	file >> value;
	player.setEnergy(-100 + value);
	file >> value;
	player.setMoney(-100 + value);
	file >> bvalue;
	player.setShovel();
	file >> bvalue;
	player.setBrush();
	file >> bvalue;
	player.setPickaxe();
	file >> bvalue;
	player.setSB();
	file >> bvalue;
	player.setCB();
	file >> bvalue;
	player.setBB();
	file >> bvalue;
	player.setRB();
	file >> bvalue;
	player.setEB();
	file >> bvalue;
	player.setLB();
	file >> count;
	for (int i = 0; i != count+1; ++i) 
	{
		std::getline(file, line);
		std::istringstream iss(line);
		Bone addingBone("", 0, 0);
		if (iss >> name >> id >> cost) 
		{
			addingBone.setName(name);
			addingBone.setID(id);
			addingBone.setCost(cost);
			inventory.addBone(addingBone);
		}
		
	}
	file.close();
}