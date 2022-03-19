#include "Monster.h"

Monster::Monster(World* world, Vector2D position) : MovingElement(world, position)
{
	direction = availableDirections[rand() % 4];
}

void Monster::update()
{
	world->removeMonsterPosition(position);


	// update direction
	// 1. If monster can go to the plyer
	Vector2D oldDirection = direction;
	if (world->getPlayerPosition().x == position.x)
	{
		if (world->getPlayerPosition().y < position.y)
		{
			direction = { 0, -1 };
		}
		else
		{
			direction = { 0, 1 };
		}
	}
	else if (world->getPlayerPosition().y == position.y)
	{
		if (world->getPlayerPosition().x < position.x)
		{
			direction = { -1, 0 };
		}
		else
		{
			direction = { 1, 0 };
		}
	}
	for (int i = 1; i < view_range; i++)
	{
		Vector2D scannedPosition = { position.x + i * direction.x, position.y + i * direction.y};
		if (!world->canGoTo(scannedPosition))
		{
			direction = oldDirection;
			break;
		}
		else if (scannedPosition == world->getPlayerPosition())
		{
			break;
		}
	}
	// 2. can he go straight ahead?
	Vector2D newPosition = { position.x + direction.x, position.y + direction.y };
	if (!world->canGoTo(newPosition))
	{
		std::vector<Vector2D> possibleDirections;
		for (auto dir : availableDirections)
		{
			if (world->canGoTo({ position.x + dir.x, position.y + dir.y }))
			{
				possibleDirections.push_back(dir);
			}
		}
		if (possibleDirections.size() > 0)
		{
			direction = possibleDirections.at(rand() % possibleDirections.size());
		}
		else
		{
			direction = { direction.x * (-1), direction.y * (-1) };
		}
	}
	move();
	world->addMonsterPosition(position);
}
