#include "options.hpp"

Options::Options(sf::VideoMode& mode, sf::RenderWindow* window)
{
	Button::offset = 0;

	Button* back = new Button("Return", [this, window,&mode]()
		{
			window->clear();
			Button::offset = 0;
			Game::currentState = Game::state::main_menu;
			Game::menu = new mainMenu(mode, window);
			this->deleteFlag = true;
		});
	Button* resolution = new Button("Resolution", [&mode,window,back,this]()
		{
			if (!resolutionFlag)
			{
				buttons.resize(6);
				Button::offset = 0;
				resolutionFlag = true;
				window->clear();

				Button* opt1 = new Button("800x600", [window,this,&mode]()
					{
						Button::offset = 0;
						window->setSize(sf::Vector2u(800, 600));
						mode = sf::VideoMode({ 800, 600 });
						window->setView(sf::View(sf::FloatRect({ 0, 0 }, { static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y) })));
						for (auto& button : buttons)
						{
							button->placeCenter(mode);
						}
					});
				Button* opt2 = new Button("1152x872", [window, this, &mode]()
					{
						Button::offset = 0;
						window->setSize(sf::Vector2u(1152, 872));
						mode = sf::VideoMode({ 1152, 872 });
						window->setView(sf::View(sf::FloatRect({ 0, 0 }, { static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y) })));

						for (auto& button : buttons)
						{
							button->placeCenter(mode);
						}
					});
				Button* opt3 = new Button("1600x1200", [window, this, &mode]()
					{
						Button::offset = 0;
						window->setSize(sf::Vector2u(1600, 1200));
						mode = sf::VideoMode({ 1600, 1200 });
						window->setView(sf::View(sf::FloatRect({ 0, 0 }, { static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y) })));

						for (auto& button : buttons)
						{
							button->placeCenter(mode);
						}
					});
				Button* opt4 = new Button("1920x1080", [window, this, &mode]()
					{
						Button::offset = 0;
						window->setSize(sf::Vector2u(1920, 1080));
						mode = sf::VideoMode({ 1920, 1080 });
						window->setView(sf::View(sf::FloatRect({ 0, 0 }, { static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y) })));

						for (auto& button : buttons)
						{
							button->placeCenter(mode);
						}
					});
				resolutionButtons = 4;

				buttons[1] = opt1;
				buttons[2] = opt2;
				buttons[3] = opt3;
				buttons[4] = opt4;
				buttons[5] = back;

				for (auto& button : buttons)
				{
					button->placeCenter(mode);
				}
			}
			else
			{
				Button::offset = 0;
				resolutionFlag = false;
				window->clear();

				buttons.resize(1);
				resolutionButtons = 0;

				buttons.push_back(back);

				for (auto& button : buttons)
				{
					button->placeCenter(mode);
				}

			}
			
		});

	resolution->placeCenter(mode);
	back->placeCenter(mode);

	buttons.push_back(resolution);
	buttons.push_back(back);
}


Options::~Options()
{
	for (auto& button : buttons)
	{
		delete button;
	}
}

void Options::render(sf::RenderWindow* window)
{
	for (auto& button : buttons)
	{
		button->render(window);
	}
}

void Options::handleEvent(sf::Event& event, sf::RenderWindow* window)
{
	if (const auto* keyboardButtonPressed = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyboardButtonPressed->scancode == sf::Keyboard::Scancode::Down)
		{
			selectedButton = (selectedButton + 1) % buttons.size();
			buttons[selectedButton]->isSelected = true;
			if (selectedButton == 0)
			{
				buttons[buttons.size()-1]->isSelected = false;
			}
			else
			{
				buttons[selectedButton - 1]->isSelected = false;
			}
		}
		if (keyboardButtonPressed->scancode == sf::Keyboard::Scancode::Up)
		{
			selectedButton -= 1;

			if (selectedButton < 0)
			{
				selectedButton = buttons.size()-1;
			}

			buttons[selectedButton]->isSelected = true;

			if (selectedButton == buttons.size()-1)
			{
				buttons[0]->isSelected = false;
			}
			else
			{
				buttons[selectedButton + 1]->isSelected = false;
			}
		}
	}
	for (auto& button : buttons)
	{
		if (button)
			button->handleEvent(event, window);
	}
}