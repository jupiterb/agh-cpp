#include <SFML/Graphics.hpp>
#include "Menu.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main()
{
	srand((unsigned)time(NULL));

	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Infinity Maze Game");

	sf::Event event;
	
	Menu* menu = new Menu();

	sf::Time delay = sf::milliseconds(10);

	while (window.isOpen()) 
	{

		sf::sleep(delay);
		while (window.pollEvent(event)) 
		{
			
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}
			else
			{
				menu->pollEvent(&event);
			}
		}
		window.clear(sf::Color::White);
		menu->update();
		menu->render(&window);
		window.display();
	}
	delete menu;

	return 0;
}