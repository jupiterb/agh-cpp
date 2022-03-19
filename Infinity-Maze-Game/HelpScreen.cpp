#include "HelpScreen.h"

HelpScreen::HelpScreen()
{
	font.loadFromFile("Fonts/arial.ttf");
	text.setFont(font);

	std::string manual =	"Controlling: WASD\n"
							"Leave block: Enter\n"
							"Aim: collect ";
	manual					+= std::to_string(requiredDiamonds);
	manual					+= " diamonds\n"
							"Attention: Monsters can kill player";

	text.setString(manual);
	text.setCharacterSize(charcterSize);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Underlined);
	text.setPosition({ 50,50 });

	closeButton = new Button({ 50, 500 }, buttonSize, "Clsoe Helper");
	released = true;
}

void HelpScreen::pollEvent(sf::Event* event)
{
	closeButton->pollEvent(event);
	if (closeButton->wasClicked())
	{
		released = true;
	}
}

void HelpScreen::update()
{
	released = false;
	closeButton->update();
}

void HelpScreen::render(sf::RenderWindow* window)
{
	window->draw(text);
	closeButton->render(window);
}

bool HelpScreen::isReleased()
{
	return released;
}

HelpScreen::~HelpScreen()
{
	delete closeButton;
}
