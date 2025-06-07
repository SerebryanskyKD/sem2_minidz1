#include "shopUI.h"

shopUI::shopUI(Player* player, Shop* shop, sf::VideoMode& mode) : player(player), shop(shop), isOpen(false) {
    buttons.resize(9);

    std::stringstream ss;
    ss << "Money: " << player->getMoney() << "\nFood: " << player->getFood();
    for (auto& item : shop->catalog)
    {
		ss << "\n" << item.first << ": " << std::get<0>(item.second) << "(Price) " << std::get<1>(item.second) << "(Amount) ";
    }

    playerInfo.setString(ss.str());
    playerInfo.setCharacterSize(20);
    playerInfo.setFillColor(sf::Color::White);
    playerInfo.setPosition({ mode.size.x / 2.0f - 100, mode.size.y / 4.0f - 80 });

    // Create buttons
    Button* buyPick = new Button("Buy Pick", [this]() {
        this->shop->buy("pick", 1);
        updatePlayerInfo();
        });
    Button* buyBrush = new Button("Buy Brush", [this]() {
        this->shop->buy("brush", 1);
        updatePlayerInfo();
        });
    Button* buyShovel = new Button("Buy Shovel", [this]() {
        this->shop->buy("shovel", 1);
        updatePlayerInfo();
        });
    Button* buyFood = new Button("Buy Food", [this]() {
        this->shop->buy("food", 1);
        updatePlayerInfo();
        });
    Button* sellPick = new Button("Sell Pick", [this]() {
        this->shop->sell("pick", 1);
        updatePlayerInfo();
        });
    Button* sellBrush = new Button("Sell Brush", [this]() {
        this->shop->sell("brush", 1);
        updatePlayerInfo();
        });
    Button* sellShovel = new Button("Sell Shovel", [this]() {
        this->shop->sell("shovel", 1);
        updatePlayerInfo();
        });
    Button* sellArtifacts = new Button("Sell Artifacts", [this]() {
        this->shop->sell("artifacts", 1);
        updatePlayerInfo();
        });
    Button* close = new Button("Close", [this]() {
        this->shop->closeMenu();
        });

    buyPick->setScale({ 0.5f,0.5f });
    buyBrush->setScale({ 0.5f,0.5f });
    buyShovel->setScale({ 0.5f,0.5f });
    buyFood->setScale({ 0.5f,0.5f });
    sellPick->setScale({ 0.5f,0.5f });
    sellBrush->setScale({ 0.5f,0.5f });
    sellShovel->setScale({ 0.5f,0.5f });
    sellArtifacts->setScale({ 0.5f,0.5f });
    close->setScale({ 0.5f,0.5f });

    buttons[0] = buyPick;
    buttons[1] = buyBrush;
    buttons[2] = buyShovel;
    buttons[3] = buyFood;
    buttons[4] = sellPick;
    buttons[5] = sellBrush;
    buttons[6] = sellShovel;
    buttons[7] = sellArtifacts;
    buttons[8] = close;

    for (auto& button : buttons) {
        button->placeCenter(mode);
    }

    for (auto& button : buttons) {
        button->setPosition(button->name.getGlobalBounds().getCenter() - sf::Vector2f{ 0.0f,100.0f });
    }
}

shopUI::~shopUI() {
    for (auto& button : buttons) {
        delete button;
    }
}

void shopUI::open() {
    isOpen = true;
    updatePlayerInfo();
}

void shopUI::close() {
    isOpen = false;
    player->canMove = true;
}

void shopUI::updatePlayerInfo() {
    std::stringstream ss;
    ss << "Money: " << player->getMoney() << "\nFood: " << player->getFood();
    for (auto& item : shop->catalog)
    {
        ss << "\n" << item.first << ": " << std::get<0>(item.second) << "(Price) " << std::get<1>(item.second) << "(Amount) ";
    }
    playerInfo.setString(ss.str());
}

void shopUI::render(sf::RenderWindow* window) {
    if (!isOpen) return;

    window->draw(playerInfo);
    for (auto& button : buttons) {
        button->render(window);
    }
}

void shopUI::handleEvent(sf::Event& event, sf::RenderWindow* window) {
    if (!isOpen) return;

    for (auto& button : buttons) {
        button->handleEvent(event, window);
    }
}