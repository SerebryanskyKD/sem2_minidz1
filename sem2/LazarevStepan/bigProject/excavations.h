#pragma once
#include <map>
#include <string>
#include <vector>
#include "player.h"
#include <random>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include "message.h"

using str = std::string;
class Message;

class Excavation {
private:
	std::map<str, int> Loot;
	str name;
public:
	Player* const player;
	std::vector<bool> achievemnts = { false,false,false };
	sf::Font font{ "../fonts/KenneyBlocks.ttf" };
	sf::VideoMode mode;

	Message* message;

	Excavation(Player* p, sf::VideoMode& mode, sf::RenderWindow* window);
	virtual ~Excavation();

	template<class T>
	static bool checkPlayer(Player* player);

	virtual void excavate(sf::RenderWindow* window) = 0;
	virtual void effect(sf::RenderWindow* window) = 0;
	virtual void printText(sf::RenderWindow* window) = 0;
	virtual void render(sf::RenderWindow* window) = 0;

	void setName(str name);

	void setLoot(std::map<str, int> loot);

	str getName() const;

	const std::map<str, int>& getLoot() const;

	const bool randomItem(sf::RenderWindow* window);

	void saveAchievments(int lineNumber, str&& toWrite);

};

class ExcavationUnderWater : public Excavation {
public:
	static const int cost = 10;
	static const int cost_food = 1;

	ExcavationUnderWater(Player* p, sf::VideoMode& mode, sf::RenderWindow* window);

	void excavate(sf::RenderWindow* window) override;

	void effect(sf::RenderWindow* window) override;

	void printText(sf::RenderWindow* window) override;

	void render(sf::RenderWindow* window) override;
};

class ExcavationVulkano : public Excavation {
public:
	static const int cost = 25;
	static const int cost_food = 2;

	ExcavationVulkano(Player* p, sf::VideoMode& mode, sf::RenderWindow* window);

	void excavate(sf::RenderWindow* window) override;

	void effect(sf::RenderWindow* window) override;

	void printText(sf::RenderWindow* window) override;

	void render(sf::RenderWindow* window)  override;
};

class ExcavationMoon : public Excavation {
public:
	const static int cost = 50;
	const static int cost_food = 3;

	ExcavationMoon(Player* p, sf::VideoMode& mode, sf::RenderWindow* window);

	void excavate(sf::RenderWindow* window) override;

	void effect(sf::RenderWindow* window) override;

	void printText(sf::RenderWindow* window) override;

	void render(sf::RenderWindow* window) override;
};