#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>

const int charcterSize = 30;
const sf::Vector2f buttonSize = { 300, 50 };

class Button
{
public:

	Button(sf::Vector2f position, sf::Vector2f size, const std::string name);

	void pollEvent(sf::Event* event);

	void update();

	void render(sf::RenderWindow* window);

	bool wasClicked();

private:

	sf::Vector2f position;
	sf::Vector2f size;

	sf::Font font;
	sf::Text text;

	sf::RectangleShape bg;

	bool cliecked;
};

#endif
