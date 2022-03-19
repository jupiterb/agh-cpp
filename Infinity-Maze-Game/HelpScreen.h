#ifndef HELP
#define HELP

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameManager.h"
#include <string>

class HelpScreen
{
public:

	HelpScreen();

	void pollEvent(sf::Event* event);

	void update();

	void render(sf::RenderWindow* window);

	bool isReleased();

	~HelpScreen();

private:

	Button * closeButton;
	sf::Text text;
	sf::Font font;

	bool released;
};

#endif