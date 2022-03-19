#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(World* world)
{
	this->world = world;
	this->size = {	((float)boardSize.x / world->getBoardSize().x),
					((float)boardSize.y / world->getBoardSize().y) };
}

void WorldRenderer::render(sf::RenderWindow* window)
{
	for (auto position : *world->getPositionsOnBorad())
	{
		Vector2D shiftedPosition = {	position.x - world->getUpperLeft().x,
										position.y - world->getUpperLeft().y };
		switch (world->getWorldElment(position))
		{
		case WorldElement::_CORRIDOR:
			drawRect(shiftedPosition, corridorColor, window);
			break;
		case WorldElement::_WALL:
			drawRect(shiftedPosition, wallColor, window);
			break;
		case WorldElement::_PLAYER:
			drawRect(shiftedPosition, playerColor, window);
			break;
		case WorldElement::_MONSTER:
			drawRect(shiftedPosition, monsterColor, window);
			break;
		case WorldElement::_DIAMOND:
			drawRect(shiftedPosition, diamondColor, window);
			break;
		case WorldElement::_LOCK:
			drawRect(shiftedPosition, lockColor, window);
			break;
		}
	}
}

void WorldRenderer::drawRect(Vector2D position, sf::Color color, sf::RenderWindow* window)
{
	sf::RectangleShape rect(size);
	rect.setFillColor(color);

	sf::Vector2f rectPosition = { position.x * size.x, position.y * size.y };
	rect.setPosition(rectPosition);

	window->draw(rect);
}
