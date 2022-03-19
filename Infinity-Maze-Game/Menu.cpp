#include "Menu.h"

Menu::Menu()
{
	title.setString("Welcome to the Inifinty Maze game");
	title.setCharacterSize(charcterSize);
	title.setFillColor(sf::Color::Red);

	font.loadFromFile("Fonts/arial.ttf");

	title.setFont(font);
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);

	playButton = new Button(positionPlayButton, buttonSize, "Play Game");
	helpButton = new Button(positionHelpButton, buttonSize, "Help");

	mode = Mode::_MENU;
	helper = new HelpScreen();
}

void Menu::pollEvent(sf::Event* event)
{
	switch (mode)
	{
	case Mode::_MENU:
		playButton->pollEvent(event);
		helpButton->pollEvent(event);
		break;
	case Mode::_GAME:
		manager->pollEvent(event);
		break;
	case Mode::_HELP:
		helper->pollEvent(event);
		break;
	}
}

void Menu::update()
{
	switch (mode)
	{
	case Mode::_MENU:
		if (playButton->wasClicked())
		{
			manager = new GameManager();
			mode = Mode::_GAME;
		}
		else if (helpButton->wasClicked())
		{
			mode = Mode::_HELP;
		}
		playButton->update();
		helpButton->update();
		break;
	case Mode::_GAME:
		manager->update();
		if (manager->isfinished())
		{
			mode = Mode::_MENU;
			delete manager;
		}
		break;
	case Mode::_HELP:
		if (helper->isReleased())
		{
			mode = Mode::_MENU;
		}
		helper->update();
		break;
	}
}

void Menu::render(sf::RenderWindow* window)
{
	switch (mode)
	{
	case Mode::_MENU:
		window->draw(title);
		playButton->render(window);
		helpButton->render(window);
		break;
	case Mode::_GAME:
		manager->render(window);
		break;
	case Mode::_HELP:
		helper->render(window);
		break;
	}
}

Menu::~Menu()
{
	delete playButton;
	delete helpButton;
	delete helper;
}
