#include "excavations.h"

extern std::mt19937 gen;
extern std::uniform_int_distribution<> distribLoot;
extern std::uniform_int_distribution<> distribEffect;
extern std::uniform_int_distribution<> distirEquip;

//BASE CLASS.............................................................................................................................

Excavation::Excavation(Player* p, sf::VideoMode& m, sf::RenderWindow* window) : player(p), mode(m)
{
	message = new Message{ "",mode };
}

Excavation::~Excavation()
{
	delete message;
}

const bool Excavation::randomItem(sf::RenderWindow* window) {
	int rand = distirEquip(gen);
	std::stringstream ss;
	ss << "What equipment will you use?";
	window->clear();
	*message = ss.str();
	message->render(window);
	window->display();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	window->clear();

	int input;
	bool isClicked = false;

	Button* Pickaxe = new Button("Pickaxe", [&input, &isClicked,window]()
		{
			input = 1;
			isClicked = true;
		});
	Button* Brush = new Button("Brush", [&input, &isClicked, window]()
		{
			input = 2;
			isClicked = true;
		});
	Button* Shovel = new Button("Shovel", [&input, &isClicked, window]()
		{
			input = 3;
			isClicked = true;
		});

	Button::offset = 0;
	Pickaxe->placeCenter(mode);
	Brush->placeCenter(mode);
	Shovel->placeCenter(mode);

	Pickaxe->render(window);
	Brush->render(window);
	Shovel->render(window);

	window->display();

	while (!isClicked) {
		while (auto event = window->pollEvent()) {
			if (event.has_value())
			{
				Pickaxe->handleEvent(event.value(), window);
				Brush->handleEvent(event.value(), window);
				Shovel->handleEvent(event.value(), window);
			}
		}

		window->clear();
		Pickaxe->render(window);
		Brush->render(window);
		Shovel->render(window);
		window->display();
	}

	delete Pickaxe;
	delete Brush;
	delete Shovel;

	return (input != rand);
}

void Excavation::saveAchievments(int lineNumber, str&& toWrite)
{
	str filePath = "playerAchievments.txt";
	std::vector<std::string> lines;
	str line;

	std::ifstream inputFile(filePath);
	if (inputFile.is_open()) {
		while (std::getline(inputFile, line)) {
			lines.push_back(line);
		}
		inputFile.close();
	}

	lines[lineNumber - 1] = toWrite;

	std::ofstream outputFile(filePath);
	if (outputFile.is_open()) {
		for (const auto& l : lines) {
			outputFile << l << std::endl;
		}
		outputFile.close();
	}
}

template<class T>
bool Excavation::checkPlayer(Player* player) {
		if (player->getMoney() >= T::cost && player->getFood() >= T::cost_food) {
			return true;
		}
		return false;
	}

template bool Excavation::checkPlayer<ExcavationUnderWater>(Player* player);
template bool Excavation::checkPlayer<ExcavationVulkano>(Player* player);
template bool Excavation::checkPlayer<ExcavationMoon>(Player* player);

void Excavation::setName(str name) {
		this->name = name;
}

void Excavation::setLoot(std::map<str, int> loot) {
		this->Loot = loot;
}

str Excavation::getName() const {
		return this->name;
}

const std::map<str, int>& Excavation::getLoot() const {
		return this->Loot;
}

//UNDER WATER................................................................................................................................

ExcavationUnderWater::ExcavationUnderWater(Player* p, sf::VideoMode& mode, sf::RenderWindow* window) :Excavation(p,mode,window) {
		setLoot(std::map<std::string, int>{{"Deepwater Totem", 10}, { "Coral Crown", 25 }, { "Pearl of the Depths", 50 }});
		setName("Expedition to the kingdom of Poseidon.");
}

void ExcavationUnderWater::excavate(sf::RenderWindow* window) {
		player->setMoney(player->getMoney() - cost);
		player->setFood(player->getFood() - cost_food);

		int loot_chance = distribLoot(gen);
		std::map<str, int> Loot = getLoot();
		auto it = Loot.begin();

		*message = getName();
		window->clear();
		message->render(window);
		window->display();


		std::this_thread::sleep_for(std::chrono::seconds(3));

		printText(window);

		if (loot_chance < 40) {
			*message = "You found nothing!";
			window->clear();
			message->render(window);
			window->display();

			std::this_thread::sleep_for(std::chrono::seconds(3));

		}
		else if (loot_chance < 70 && loot_chance >= 40) {
			if (randomItem(window)) 
			{
				std::stringstream ss;
				ss << "Found common loot: " << (*it).first << "\nIt costs: " << (*it).second;
				*message = ss.str();
				window->clear();
				message->render(window);
				window->display();

				std::this_thread::sleep_for(std::chrono::seconds(3));

				player->setArtifacts(10);

				if (!achievemnts[0]) {
					saveAchievments(1, "1");
					achievemnts[0] = true;
				}
			}
			else 
			{
				std::stringstream ss;
				ss << "Used instrument is useless!";
				*message = ss.str();
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
		else if (loot_chance < 90 && loot_chance >= 70) {
			if (randomItem(window))
			{
				++it;
				std::stringstream ss;
				ss << "You've found rare loot: " << (*it).first << "\nIt costs: " << (*it).second;
				*message = ss.str();
				window->clear();
				message->render(window);
				window->display();

				std::this_thread::sleep_for(std::chrono::seconds(3));

				player->setArtifacts(25);

				if (!achievemnts[1]) {
					saveAchievments(2, "1");
					achievemnts[1] = true;
				}
			}
			else
			{
				std::stringstream ss;
				ss << "Used instrument is useless!\n";
				*message = ss.str();
				window->clear();
				message->render(window);
				window->display();

				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
		else 
		{
			if (randomItem(window)) 
			{
				std::advance(it, 2);
				std::stringstream ss;
				ss << "You've found epic loot: " << (*it).first << "\nIt costs: " << (*it).second;

				*message = ss.str();
				window->clear();
				message->render(window);
				window->display();

				std::this_thread::sleep_for(std::chrono::seconds(3));

				player->setArtifacts(50);

				if (!achievemnts[2]) {
					saveAchievments(3, "1");
					achievemnts[2] = true;
				}
			}
			else 
			{
				std::stringstream ss;
				ss << "Used instrument is useless!";
				*message = ss.str();
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}

}

void ExcavationUnderWater::effect(sf::RenderWindow* window){
		int event = distribEffect(gen);
		if (event) {
			*message = "Oh no! THE WATER TOOK YOUR CHICKEN AWAY!\n\n FOOD DECREASED BY ONE.";
			message->render(window);
			window->display();
			std::this_thread::sleep_for(std::chrono::seconds(3));
			player->setFood(player->getFood() - 1);
		}
}

void ExcavationUnderWater::printText(sf::RenderWindow* window){
	*message = "Gurgle gurgle crucian carp... \nwater drip-drip... looks like it's starting to rain... \n(getting loot)";
	window->clear();
	message->render(window);
	window->display();
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

void ExcavationUnderWater::render(sf::RenderWindow* window) 
{
	effect(window);
	excavate(window);
}

//VULKAN..................................................................................................................

ExcavationVulkano::ExcavationVulkano(Player* p, sf::VideoMode& mode, sf::RenderWindow* window)
		: Excavation(p, mode, window)
{
		setLoot(std::map<std::string, int>{{"Lava Heart Stone", 20}, { "Flame Gloves", 35 }, { "Lava Sword", 50 }});
		setName("Underworld.");
}

void ExcavationVulkano::excavate(sf::RenderWindow* window) {
		player->setMoney(player->getMoney() - cost);
		player->setFood(player->getFood() - cost_food);

		int loot_chance = distribLoot(gen);
		std::map<std::string, int> Loot = getLoot();
		auto it = Loot.begin();

		printText(window);

		if (loot_chance < 40) {
			*message = "You've found nothing!";
			window->clear();
			message->render(window);
			window->display();
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
		else if (loot_chance < 70 && loot_chance >= 40) {
			if (randomItem(window)) {
				*message = "Found common loot: " + (*it).first + "\nIt costs: " + std::to_string((*it).second);
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));

				player->setArtifacts(20);
				if (!achievemnts[0]) {
					saveAchievments(4, "1");
					achievemnts[0] = true;
				}
			}
			else {
				*message = "Used instrument is useless!";
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
		else if (loot_chance < 90 && loot_chance >= 70) {
			if (randomItem(window)) {
				++it;
				*message = "You've found rare loot: " + (*it).first + "\nIt costs: " + std::to_string((*it).second);
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));

				player->setArtifacts(35);
				if (!achievemnts[1]) {
					saveAchievments(5, "1");
					achievemnts[1] = true;
				}
			}
			else {
				*message = "Used instrument is useless!";
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
		else {
			if (randomItem(window)) {
				std::advance(it, 2);
				*message = "You've found epic loot: " + (*it).first + "\nIt costs: " + std::to_string((*it).second);
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));

				player->setArtifacts(50);
				if (!achievemnts[3]) {
					saveAchievments(6, "1");
					achievemnts[3] = true;
				}
			}
			else {
				*message = "Used instrument is useless!";
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
	}

	void ExcavationVulkano::effect(sf::RenderWindow* window) {
		int event = distribEffect(gen);
		if (event) {
			*message = "Oh no! THE FIRE HAS BURNED YOUR GEAR!";
			window->clear();
			message->render(window);
			window->display();
			std::this_thread::sleep_for(std::chrono::seconds(3));

			std::uniform_int_distribution<> distribEquipment(0, player->getEquipment().size() - 1);
			int distrib = distribEquipment(gen);
			auto it = (player->getEquipment()).begin();
			std::advance(it, distrib);
			(*it).second = (*it).second - 1;
		}
	}

	void ExcavationVulkano::printText(sf::RenderWindow* window) {
		*message = "Heat, heat-ah.\nThe roasting sun of big cities!...(getting loot)";
		window->clear();
		message->render(window);
		window->display();
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}

	void ExcavationVulkano::render(sf::RenderWindow* window) 
	{
		effect(window);
		excavate(window);
	}
//MOON...........................................................................................................................................................

	ExcavationMoon::ExcavationMoon(Player* p, sf::VideoMode& mode, sf::RenderWindow* window)
		: Excavation(p, mode, window) {
		setLoot(std::map<std::string, int>{{"Moon Crystal Essence", 40}, { "Lunar Power Shard", 70 }, { "Stardust Elixir", 100 }});
		setName("Crater on the moon.");
	}

	void ExcavationMoon::excavate(sf::RenderWindow* window) {
		player->setMoney(player->getMoney() - cost);
		player->setFood(player->getFood() - cost_food);

		int loot_chance = distribLoot(gen);
		std::map<std::string, int> Loot = getLoot();
		auto it = Loot.begin();

		printText(window);

		if (loot_chance < 40) {
			*message = "You've found nothing!";
			window->clear();
			message->render(window);
			window->display();
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
		else if (loot_chance < 70 && loot_chance >= 40) {
			if (randomItem(window)) {
				*message = "Found common loot: " + (*it).first + "\nIt costs: " + std::to_string((*it).second);
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));

				player->setArtifacts(40);
				if (!achievemnts[0]) {
					saveAchievments(7, "1");
					achievemnts[0] = true;
				}
			}
			else {
				*message = "Used instrument is useless!";
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
		else if (loot_chance < 90 && loot_chance >= 70) {
			if (randomItem(window)) {
				++it;
				*message = "You've found rare loot: " + (*it).first + "\nIt costs: " + std::to_string((*it).second);
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));

				player->setArtifacts(70);
				if (!achievemnts[1]) {
					saveAchievments(8, "1");
					achievemnts[1] = true;
				}
			}
			else {
				*message = "Used instrument is useless!";
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
		else {
			if (randomItem(window)) {
				std::advance(it, 2);
				*message = "You've found epic loot: " + (*it).first + "\nIt costs: " + std::to_string((*it).second);
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));

				player->setArtifacts(100);
				if (!achievemnts[2]) {
					saveAchievments(9, "1");
					achievemnts[2] = true;
				}
			}
			else {
				*message = "Used instrument is useless!";
				window->clear();
				message->render(window);
				window->display();
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
	}

	void ExcavationMoon::effect(sf::RenderWindow* window) {
		int event = distribEffect(gen);
		if (event) {
			*message = "I FORGOT TO CLOSE MY BACKPAAAAACK!";
			window->clear();
			message->render(window);
			window->display();
			std::this_thread::sleep_for(std::chrono::seconds(3));
			*message = "15 shekels left your wallet... (your inner side-swept personality is raging).";
			window->clear();
			message->render(window);
			window->display();
			std::this_thread::sleep_for(std::chrono::seconds(3));

			player->setMoney(player->getMoney() - 15);
		}
	}

	void ExcavationMoon::printText(sf::RenderWindow* window) {
		*message = "The Earth is in the porthole, The Earth is in the porthole, The Earth is visible in the porthole...";
		window->clear();
		message->render(window);
		window->display();
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}

	void ExcavationMoon::render(sf::RenderWindow* window) 
	{
		effect(window);
		excavate(window);
	}