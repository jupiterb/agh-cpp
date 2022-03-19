#ifndef MENU
#define MENU

#include <SFML/Graphics.hpp>
#include "HelpScreen.h"
#include "GameManager.h"

const sf::Vector2f positionPlayButton = { 10, 100 };
const sf::Vector2f positionHelpButton = { 10, 200 };

enum class Mode{_MENU, _HELP, _GAME};

class Menu
{
public:

	Menu();

	void pollEvent(sf::Event * event);

	void update();

	void render(sf::RenderWindow* window);

	~Menu();

private:

	sf::Window window;

	sf::Font font;
	sf::Text title;

	Button* playButton;
	Button* helpButton;

	Mode mode;

	HelpScreen* helper;

	GameManager* manager;
};

#endif