#include <cmake-build-debug/_deps/sfml-src/include/SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <utility>

class ColorUtils {
public:
	static sf::Color getColorFromHex(const std::string& hex) {
		if (hex.size() != 7 || hex[0] != '#') {
			throw std::invalid_argument("Invalid hex color format");
		}

		int r = std::stoi(hex.substr(1, 2), nullptr, 16);
		int g = std::stoi(hex.substr(3, 2), nullptr, 16);
		int b = std::stoi(hex.substr(5, 2), nullptr, 16);

		return sf::Color(r, g, b);
	}

	static sf::Color lerp(const sf::Color& a, const sf::Color& b, const float time) {
		return {
			static_cast<std::uint8_t>(a.r + time * (b.r - a.r)),
				static_cast<std::uint8_t>(a.g + time * (b.g - a.g)),
				static_cast<std::uint8_t>(a.b + time * (b.b - a.b)),
				static_cast<std::uint8_t>(a.a + time * (b.a - a.a))
		};
	}

	static sf::Color clerp(const sf::Color& a, const sf::Color& b, const float time) {
        return lerp(a, b, std::clamp(time, 0.0f, 1.0f));
    }

	static sf::Color inverse(const sf::Color& color) {
        return { static_cast<std::uint8_t>(255 - color.r), static_cast<std::uint8_t>(255 - color.g), static_cast<std::uint8_t>(255 - color.b), color.a};
    }
};

class ITickable {
public:
    virtual void tick(float delta_time) = 0;
};

class Global {
    static sf::RenderWindow* window;

public:
	static void setWindow(sf::RenderWindow* win) {
        window = win;
    }
    static sf::RenderWindow* getWindow() {
        return window;
    }

	static sf::Vector2f getMousePosition() {
        return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
    }
};
sf::RenderWindow* Global::window = nullptr;

struct ButtonColors {
	sf::Color background_color = ColorUtils::getColorFromHex("#FF0000");
	sf::Color text_color = ColorUtils::getColorFromHex("#FFFFFF");

	ButtonColors() = default;
	ButtonColors(const sf::Color& bg_color, const sf::Color& txt_color) : background_color(bg_color), text_color(txt_color) {}
	ButtonColors(const std::string& bg_hex, const std::string& txt_hex) : background_color(ColorUtils::getColorFromHex(bg_hex)), text_color(ColorUtils::getColorFromHex(txt_hex)) {}
};

struct ButtonScheme {
	ButtonColors normal {
        ColorUtils::getColorFromHex("#3498DB"),
        ColorUtils::getColorFromHex("#FFFFFF")
    };
	ButtonColors hover {
        ColorUtils::getColorFromHex("#2980B9"),
        ColorUtils::getColorFromHex("#FFFFFF")
    };
	ButtonColors pressed {
        ColorUtils::getColorFromHex("#1ABC9C"),
        ColorUtils::getColorFromHex("#FFFFFF")
    };
};

class Button final : public sf::Drawable, public sf::Transformable, public ITickable {
	sf::RectangleShape shape;
	sf::Text text;
	ButtonScheme scheme;
	std::function<void()> on_click_callback;

public:
	Button(const sf::Vector2f& size, const std::string& text_str = "Button", const sf::Font& font = sf::Font(), const unsigned int text_size = 30, std::function<void()> on_click = nullptr) : text(font), on_click_callback(std::move(on_click)) {
		shape = sf::RectangleShape(size);

		text.setString(text_str);
		text.setCharacterSize(text_size);
		text.setFillColor(sf::Color::Black);

		const auto bounds = text.getGlobalBounds().size;
		text.setOrigin({ bounds.x / 2.0f, bounds.y / 1.25f });
		text.setPosition(size / 2.0f);
    }

	void setScheme(const ButtonScheme& new_scheme) {
        scheme = new_scheme;
    }

	bool isHovered() const {
		const auto mouse_pos = Global::getMousePosition();
		const auto shape_bounds = shape.getGlobalBounds();

		return shape_bounds.contains(mouse_pos);
	}

	void onClick() {
		if (!isHovered())
			return;

		if (on_click_callback) {
			on_click_callback();
		}
    }

	void tick(const float delta_time) override {
		const bool is_hovered = isHovered();
		const bool is_pressed = isButtonPressed(sf::Mouse::Button::Left) && is_hovered;

		const ButtonColors new_colors = is_pressed ? scheme.pressed : (is_hovered ? scheme.hover : scheme.normal);
		const float transition_time = is_pressed ? 2.0f : 1.0f;

		shape.setFillColor(ColorUtils::lerp(shape.getFillColor(), new_colors.background_color, delta_time * transition_time * 10.0f));
		text.setFillColor(ColorUtils::lerp(text.getFillColor(), new_colors.text_color, delta_time * transition_time * 10.0f));
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();
        target.draw(shape, states);
        target.draw(text, states);
	}
};

void system_shutdown() {
	#if defined(_WIN32) || defined(_WIN64)
        system("shutdown /s /t 0");
    #elif defined(__linux__)
        system("shutdown now");
    #elif defined(__APPLE__) || defined(__MACH__)
        system("osascript -e 'tell app \"System Events\" to shut down'");
    #else
        std::cerr << "Unsupported OS" << std::endl;
    #endif
}

int main() {
	const auto window = new sf::RenderWindow(sf::VideoMode({200u, 50u}), "Shutdown: Button", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(144);
	Global::setWindow(window);

	sf::Font font;
	if (!font.openFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

	Button button({200.f, 50.f}, "SHUTDOWN", font, 30, []() {
		system_shutdown();
    });
	button.setScheme(
		{
			{
				ColorUtils::getColorFromHex("#E74C3C"),
                ColorUtils::getColorFromHex("#FFFFFF")
            },
            {
                ColorUtils::getColorFromHex("#C0392B"),
                ColorUtils::getColorFromHex("#FFFFFF")
            },
            {
                ColorUtils::getColorFromHex("#ECF0F1"),
                ColorUtils::getColorFromHex("#000000")
			}
		});

	sf::Clock clock;
	while (window->isOpen())
	{
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window->close();

			if (auto mouse_event = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse_event->button == sf::Mouse::Button::Left)
                {
                	button.onClick();
                }
            }
		}

		sf::Time delta_time = clock.restart();

		window->clear();

		button.tick(delta_time.asSeconds());
		window->draw(button);

		window->display();
	}
}