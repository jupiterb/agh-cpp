#ifndef MELEMENT
#define MELEMENT


#include "World.h"

class MovingElement{
public:

	MovingElement(World* world, Vector2D position);

	void move();

	Vector2D getPosition();

protected:

	Vector2D position;

	Vector2D direction;

	World* world;

};

#endif
