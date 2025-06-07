#include "button.hpp"


Button::Button(std::string str, std::function<void()> funcOnClick)
{
	this->name.setString(str);
	this->name.setFillColor(sf::Color::White);
	this->name.setOrigin(this->name.getGlobalBounds().getCenter());

	backgroundTexture = new sf::Texture("../UI/PNG/Default/Border/panel-border-028.png");
	backgroundTexture->setSmooth(true);

	background = new sf::Sprite(*backgroundTexture);
	background->setOrigin(background->getGlobalBounds().getCenter());
	background->setScale({ (name.getGlobalBounds().size.x + 20.f) / background->getGlobalBounds().size.x, (name.getGlobalBounds().size.y + 30.f) / background->getGlobalBounds().size.y });

	onClick = funcOnClick;
}

Button::~Button()
{
	delete backgroundTexture;
	delete background;
}

void Button::placeCenter(sf::VideoMode& mode) 
{
	sf::Vector2f middle({ mode.size.x / 2.f, mode.size.y / 4.f + offset });
	this->background->setPosition(middle);
	this->name.setPosition(middle);
	

	offset += this->name.getGlobalBounds().size.y + 20;
}

void  Button::placeHorizontal(sf::VideoMode& mode, std::vector<Button*>& buttons)
{
	float offset = mode.size.x / buttons.size() / 2.0f;
	float between = mode.size.x / buttons.size();

	for (auto& button:buttons)
	{
		sf::Vector2f middle({ offset, mode.size.y / 2.f });
		button->background->setPosition(middle);
		button->name.setPosition(middle);
		offset += between;
	}
}

void Button::setPosition(sf::Vector2f pos)
{
	this->background->setPosition(pos);
	this->name.setPosition(pos);
}

void Button::setScale(sf::Vector2f size)
{

	this->name.setScale(size);
	background->scale({ (name.getGlobalBounds().size.x + 20.f) / background->getGlobalBounds().size.x, (name.getGlobalBounds().size.y + 30.f) / background->getGlobalBounds().size.y });
}

void Button::render(sf::RenderWindow* window) const
{
	if (isSelected)
		window->draw(*background);
	window->draw(this->name);
}

void Button::handleEvent(sf::Event& event, sf::RenderWindow* window)
{
	if (event.is<sf::Event::MouseMoved>())
	{
		if (this->name.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))))
		{
			isSelected = true;
		}
		else
		{
			isSelected = false;
		}
	}
	if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (isSelected && onClick && mouseButtonPressed->button == sf::Mouse::Button::Left)
		{
			onClick();
		}
	}
	if (const auto* keyboardButtonPressed = event.getIf<sf::Event::KeyPressed>())
	{
		if (isSelected && onClick && keyboardButtonPressed->scancode == sf::Keyboard::Scancode::Enter)
		{
			onClick();
		}
	}
}
