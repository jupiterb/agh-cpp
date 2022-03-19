#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include "MovingElement.h"


const int startNumberOfLocks = 10;


class Player : public MovingElement
{
public:

	static const int tempo = 4;

	Player(World* world, Vector2D position);

	void pollEvent(sf::Event* event);

	void update();

	int getDiamondsCount();

	int getLocksCount();

	bool isKilled();

private:

	int diamonds;

	int locks;

	bool killed;
};

#endif

