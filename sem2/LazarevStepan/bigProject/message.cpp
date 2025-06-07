#include "message.h"

Message::Message(std::string&& str,sf::VideoMode& mode_) : mode(mode_)
{
	this->name.setString(str);
	this->name.setCharacterSize(20);
	this->name.setFillColor(sf::Color::White);
	this->name.setOrigin(this->name.getLocalBounds().getCenter());

	backgroundTexture = new sf::Texture("../UI/PNG/Default/Border/panel-border-028.png");
	backgroundTexture->setSmooth(true);

	background = new sf::Sprite(*backgroundTexture);
	background->setOrigin(background->getLocalBounds().getCenter());

	background->setPosition({ mode.size.x / 2.f,mode.size.y / 2.f });
	name.setPosition({ mode.size.x / 2.f,mode.size.y / 2.f });

	background->scale({ (name.getLocalBounds().size.x + 50.f) / background->getLocalBounds().size.x, (name.getLocalBounds().size.y + 70.f) / background->getLocalBounds().size.y });
}

void Message::render(sf::RenderWindow* window)
{
	window->draw(*background);
	window->draw(name);
}

Message& Message::operator=(str&& string)
{
	if (this->name.getString() != string)
		this->name.setString(string);

	this->name.setOrigin(this->name.getLocalBounds().getCenter());
	this->name.setPosition({ mode.size.x / 2.f,mode.size.y / 2.f });
	this->background->setScale({ (name.getLocalBounds().size.x + 50.f) / background->getLocalBounds().size.x, (name.getLocalBounds().size.y + 70.f) / background->getLocalBounds().size.y });

	return *this;
}