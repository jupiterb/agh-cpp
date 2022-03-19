#include "MovingElement.h"

MovingElement::MovingElement(World* world, Vector2D position)
{
	this->position = position;
	this->direction = { 0,0 };
	this->world = world;
}

void MovingElement::move()
{
	this->position.x += this->direction.x;
	this->position.y += this->direction.y;
}

Vector2D MovingElement::getPosition()
{
	return position;
}
