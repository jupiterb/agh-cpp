#ifndef MONSTER
#define MONSTER

#include <SFML/Graphics.hpp>
#include "MovingElement.h"
#include <set>
#include <stdlib.h> 

const int view_range = 40;
const Vector2D availableDirections[] = { {0,-1}, {0,1}, {-1,0}, {1,0} };

class Monster : public MovingElement
{
public:

	static const int tempo = 5;

	Monster(World* world, Vector2D position);

	void update();
};

#endif

