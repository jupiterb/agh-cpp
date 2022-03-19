#include "Player.h"

Player::Player(World* world, Vector2D position) : MovingElement(world, position)
{
	diamonds = 0;
	locks = startNumberOfLocks;
	killed = false;
}

void Player::pollEvent(sf::Event* event)
{
	if (event->type == sf::Event::KeyPressed)
	{
		Vector2D newDirection = { 0,0 };
		switch (event->key.code)
		{
		case sf::Keyboard::W:
			newDirection = { 0,-1 };
			break;
		case sf::Keyboard::S:
			newDirection = { 0,1 };
			break;
		case sf::Keyboard::A:
			newDirection = { -1,0 };
			break;
		case sf::Keyboard::D:
			newDirection = { 1,0 };
			break;
		case sf::Keyboard::Enter:
			if (locks > 0)
			{
				world->setLock(position);
				locks--;
			}
			break;
		}
		Vector2D newPosition = { position.x + newDirection.x, position.y + newDirection.y };
		if (world->canGoTo(newPosition))
		{
			direction = newDirection;
			if (world->getWorldElment(newPosition) == WorldElement::_DIAMOND)
			{
				diamonds++;
			}
		}
	}
}

void Player::update()
{
	move();
	world->setPlayerPosition(position);
	direction = { 0,0 };
	if (world->getWorldElment(position) == WorldElement::_MONSTER)
	{
		killed = true;
	}
}

int Player::getDiamondsCount()
{
	return diamonds;
}

int Player::getLocksCount()
{
	return locks;
}

bool Player::isKilled()
{
	return killed;
}
