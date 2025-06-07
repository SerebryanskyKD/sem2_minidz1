#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <random>

#define CELLSIZE_M 10
#define CELLSIZE_N 10
#define CHANCE_FOOD 10
#define CHANCE_MONSTER 15

#define ENERGY_MAX 100
#define HP_MAX 10

#define CELLSIZE_SCREEN 100.f

enum CellType {
    Type_Grass,
    Type_Hill,
    Type_Forest,
    Type_Stone,
    Type_Sand,
    Type_Snow,
    Type_Water,
    Type_End
};
enum TextureType {
    Texture_Grass,
    Texture_Hill,
    Texture_Forest,
    Texture_Stone,
    Texture_Sand,
    Texture_Snow,
    Texture_Water,
    Texture_Hide,
    Texture_Soup,
    Texture_Monster,
    Texture_End
};

struct Cell {
    bool isHidden;
    bool isFood;
    bool isMonster;
    CellType cellType;
};

bool isWinOfGame(const Cell cells[CELLSIZE_M][CELLSIZE_N]) {
    for (int x = 0; x < CELLSIZE_M; x++) {
        for (int y = 0; y < CELLSIZE_N; y++) {
            if (cells[x][y].isHidden && !cells[x][y].isMonster) {
                return false;
            }
        }
    }
    return true;
}

bool isLoseOfGame(const int& energy, const int& hp) {
    return energy <= 0 || hp <= 0;
}

void clickTile(int& energy, int& hp,
    const sf::Vector2i& mouseCoord,
    Cell cells[CELLSIZE_M][CELLSIZE_N],
    sf::RectangleShape shapes[CELLSIZE_M][CELLSIZE_N],
    sf::Texture textures[TextureType::Texture_End]) {

    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<> dis(1, 3);

    const int x = mouseCoord.x < 0 ?
        0 :
        mouseCoord.x > CELLSIZE_SCREEN * CELLSIZE_M ?
        CELLSIZE_M - 1 :
        mouseCoord.x / CELLSIZE_SCREEN;

    const int y = mouseCoord.y < 0 ?
        0 :
        mouseCoord.y > CELLSIZE_SCREEN * CELLSIZE_N ?
        CELLSIZE_N - 1 :
        mouseCoord.y / CELLSIZE_SCREEN;

    if (!cells[x][y].isHidden) return; // Если тайл уже открыт, ничего не делаем

    cells[x][y].isHidden = false;

    if (cells[x][y].isMonster) {
        int damage = dis(gen);
        hp -= damage;
        shapes[x][y].setTexture(&textures[TextureType::Texture_Monster]);
    }
    else if (cells[x][y].isFood) {
        shapes[x][y].setTexture(&textures[TextureType::Texture_Soup]);
        energy = ENERGY_MAX;
    }
    else {
        shapes[x][y].setTexture(&textures[cells[x][y].cellType]);
    }

    // Уменьшаем энергию только если тайл был открыт впервые
    energy--;
}

int main() {
    int energy = ENERGY_MAX;
    int hp = HP_MAX;

    srand(time(0));

    Cell cells[CELLSIZE_M][CELLSIZE_N];
    for (int x = 0; x < CELLSIZE_M; x++) {
        for (int y = 0; y < CELLSIZE_N; y++) {
            cells[x][y].isHidden = true;
            cells[x][y].isFood = rand() % 100 < CHANCE_FOOD;
            cells[x][y].isMonster = rand() % 100 < CHANCE_MONSTER;
            cells[x][y].cellType = static_cast<CellType>(rand() % (CellType::Type_End - 1));
        }
    }

    sf::RenderWindow window(
        sf::VideoMode({ static_cast<unsigned int>(CELLSIZE_SCREEN * CELLSIZE_M),
            static_cast<unsigned int>(CELLSIZE_SCREEN * CELLSIZE_N) }),
        "NOT MINESWEEPER GAME", sf::Style::Default);
    sf::Vector2i mouseCoord;

    sf::Font font{ "Kenney Future.ttf" };

    sf::Text textEnergy(font);
    sf::Text textHP(font);
    sf::Text textCondition(font);
    textEnergy.setCharacterSize(CELLSIZE_SCREEN / 2);
    textEnergy.setFillColor(sf::Color::Red);
    textEnergy.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textHP.setCharacterSize(CELLSIZE_SCREEN / 2);
    textHP.setFillColor(sf::Color::Red);
    textHP.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textHP.setPosition({ 0, CELLSIZE_SCREEN / 2 });
    textCondition.setCharacterSize(CELLSIZE_SCREEN);
    textCondition.setFillColor(sf::Color::Red);
    textCondition.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::RectangleShape shapes[CELLSIZE_M][CELLSIZE_N];
    sf::Texture textures[TextureType::Texture_End];
    if (!textures[TextureType::Texture_Grass].loadFromFile("grass.png")) return -1;
    if (!textures[TextureType::Texture_Hill].loadFromFile("hill.png")) return -1;
    if (!textures[TextureType::Texture_Forest].loadFromFile("forest.png")) return -1;
    if (!textures[TextureType::Texture_Stone].loadFromFile("stone.png")) return -1;
    if (!textures[TextureType::Texture_Sand].loadFromFile("sand.png")) return -1;
    if (!textures[TextureType::Texture_Snow].loadFromFile("snow.png")) return -1;
    if (!textures[TextureType::Texture_Water].loadFromFile("water.png")) return -1;
    if (!textures[TextureType::Texture_Hide].loadFromFile("hide.png")) return -1;
    if (!textures[TextureType::Texture_Soup].loadFromFile("soup.png")) return -1;
    if (!textures[TextureType::Texture_Monster].loadFromFile("monster.png")) return -1;

    for (int x = 0; x < CELLSIZE_M; x++) {
        for (int y = 0; y < CELLSIZE_N; y++) {
            if (cells[x][y].isHidden)
                shapes[x][y].setTexture(&textures[TextureType::Texture_Hide]);
            else
                shapes[x][y].setTexture(&textures[cells[x][y].cellType]);

            shapes[x][y].setPosition(
                sf::Vector2f(x * CELLSIZE_SCREEN, y * CELLSIZE_SCREEN));
            shapes[x][y].setSize({ CELLSIZE_SCREEN, CELLSIZE_SCREEN });
        }
    }

    bool mousepressed = false;
    bool gameOver = false;
    sf::Clock gameOverClock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }

            if (!gameOver) {
                if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    mousepressed = false;
                }

                if (!mousepressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    mousepressed = true;
                    mouseCoord = sf::Mouse::getPosition(window);

                    clickTile(energy, hp, mouseCoord, cells, shapes, textures);

                    textEnergy.setString(L"Energy: " + std::to_wstring(energy));
                    textHP.setString(L"HP: " + std::to_wstring(hp));

                    if (isWinOfGame(cells)) {
                        textCondition.setString("WINNER!!!");
                        textCondition.setOrigin(textCondition.getGlobalBounds().getCenter());
                        textCondition.setPosition({ window.getSize().x / 2.f , window.getSize().y / 2.f });
                        gameOver = true;
                        gameOverClock.restart();
                    }
                    if (isLoseOfGame(energy, hp)) {
                        textCondition.setString("LOSER!!!");
                        textCondition.setOrigin(textCondition.getGlobalBounds().getCenter());
                        textCondition.setPosition({ window.getSize().x / 2.f , window.getSize().y / 2.f });
                        gameOver = true;
                        gameOverClock.restart();
                    }
                }
            }
        }

        if (gameOver && gameOverClock.getElapsedTime().asSeconds() >= 3.0f) {
            window.close();
        }

        window.clear();
        for (int x = 0; x < CELLSIZE_M; x++) {
            for (int y = 0; y < CELLSIZE_N; y++) {
                window.draw(shapes[x][y]);
            }
        }
        window.draw(textEnergy);
        window.draw(textHP);
        window.draw(textCondition);
        window.display();
    }

    return 0;
}