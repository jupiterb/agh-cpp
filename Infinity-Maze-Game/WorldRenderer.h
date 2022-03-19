#ifndef RENDERER
#define RENDERER

#include <SFML/Graphics.hpp>
#include "World.h"

const sf::Color corridorColor = sf::Color(200,200,200);
const sf::Color wallColor = sf::Color(50, 50, 50);
const sf::Color playerColor = sf::Color(200, 200, 0);
const sf::Color monsterColor = sf::Color(220, 0, 0);
const sf::Color diamondColor = sf::Color(50, 100, 250);
const sf::Color lockColor = sf::Color(0, 200, 0, 255);

const Vector2D windowSize = { 750, 850 };
const Vector2D boardSize = { 750, 750 };

class WorldRenderer
{
public:

	WorldRenderer(World* world);

	void render(sf::RenderWindow* window);

private:

	void drawRect(Vector2D position, sf::Color color, sf::RenderWindow* window);

	World * world;

	sf::Vector2f size;

};


#endif
