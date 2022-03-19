#include "Button.h"


Button::Button(sf::Vector2f position, sf::Vector2f size, const std::string name)
{
	this->position = position;
	this->size = size;
	this->cliecked = false;

	font.loadFromFile("Fonts/arial.ttf");
	text.setFont(font);
	text.setString(name);
	text.setFillColor(sf::Color::Magenta);
	text.setStyle(sf::Text::Bold);
	text.setPosition(this->position);
	text.setCharacterSize(charcterSize);

	bg = sf::RectangleShape(size);
	bg.setFillColor(sf::Color::Black);
	bg.setPosition(position);
}

void Button::pollEvent(sf::Event* event)
{
	if (event->type == sf::Event::MouseButtonPressed)
	{
		if (event->mouseButton.button == sf::Mouse::Left)
		{
			int x = event->mouseButton.x;
			int y = event->mouseButton.y;
			if (x >= position.x && x < position.x + size.x &&
				y >= position.y && y < position.y + size.y)
			{
				cliecked = true;
			}
		}
	}
}

void Button::update()
{
	cliecked = false;
}

void Button::render(sf::RenderWindow* window)
{
	window->draw(bg);
	window->draw(text);
}

bool Button::wasClicked()
{
	return cliecked;
}