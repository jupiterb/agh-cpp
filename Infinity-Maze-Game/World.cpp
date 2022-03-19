#include "World.h"

World::World()
{
	generator =			new MazeGenerator();
	monstersPositions =	new std::list<Vector2D>();
	locks =				new std::list<Vector2D>();
	upperLeft = { -preferedBoardSize.x/2, -preferedBoardSize.y / 2 };
	boardSize = preferedBoardSize;
	playerPosition = { 0,0 };
	exchangeDiamondPosition();
}

World::~World()
{
	delete generator;
	delete monstersPositions;
	delete locks;
}

void World::update()
{
	// update upper left position;
	double playerOnBoradX = ((double)playerPosition.x - upperLeft.x) / boardSize.x;
	double playerOnBoradY = ((double)playerPosition.y - upperLeft.y) / boardSize.y;
	if (playerOnBoradX < 0.25)
	{
		upperLeft.x--;
	}
	else if (playerOnBoradX > 0.75)
	{
		upperLeft.x++;
	}
	if (playerOnBoradY < 0.25)
	{
		upperLeft.y--;
	}
	else if (playerOnBoradY > 0.75)
	{
		upperLeft.y++;
	}
	// exchange diamond position if necessary
	if (playerPosition == diamondPosition)
	{
		exchangeDiamondPosition();
	}
}

bool World::canGoTo(Vector2D position)
{
	return getWorldElment(position) != WorldElement::_WALL
		&& getWorldElment(position) != WorldElement::_MONSTER
		&& getWorldElment(position) != WorldElement::_LOCK;
}

WorldElement World::getWorldElment(Vector2D position)
{
	if (diamondPosition == position)
	{
		return WorldElement::_DIAMOND;
	}
	if (std::find(locks->begin(), locks->end(), position) != locks->end())
	{
		return WorldElement::_LOCK;
	}
	if (std::find(monstersPositions->begin(), monstersPositions->end(), position) != monstersPositions->end())
	{
		return WorldElement::_MONSTER;
	}
	if (playerPosition == position)
	{
		return WorldElement::_PLAYER;
	}
	if (generator->isCorridor(position))
	{
		return WorldElement::_CORRIDOR;
	}
	else 
	{
		return WorldElement::_WALL;
	}
}

void World::setPlayerPosition(Vector2D position)
{
	playerPosition = position;
}

void World::setLock(Vector2D position)
{
	locks->push_back(position);
}

void World::removeMonsterPosition(Vector2D position)
{
	monstersPositions->remove(position);
}

void World::addMonsterPosition(Vector2D position)
{
	monstersPositions->push_back(position);
}

std::vector<Vector2D>* World::getPositionsOnBorad()
{
	auto positions = new std::vector<Vector2D>();
	for (int x = upperLeft.x; x < upperLeft.x + boardSize.x; x++)
	{
		for (int y = upperLeft.y; y < upperLeft.y + boardSize.y; y++)
		{
			positions->push_back({ x, y });
		}
	}
	return positions;
}

std::vector<Vector2D>* World::getPositionsForSpawnMonsters()
{
	auto positions = new std::vector<Vector2D>();
	for (int x = upperLeft.x-boardSize.x; x < upperLeft.x + 2*boardSize.x; x++)
	{
		for (int y = upperLeft.y - boardSize.y; y < upperLeft.y + 2*boardSize.y; y++)
		{
			if (x < upperLeft.x || x >= upperLeft.x + boardSize.x)
			{
				if (y < upperLeft.y || y >= upperLeft.y + boardSize.y)
				{
					Vector2D position = { x, y };
					if (canGoTo(position))
					{
						positions->push_back(position);
					}
				}
			}
		}
	}
	return positions;
}

std::vector<Vector2D>* World::getPositionsForSpawnPlayer()
{
	auto positions = new std::vector<Vector2D>();
	for (auto position : *getPositionsOnBorad())
	{
		if (canGoTo(position))
		{
			positions->push_back(position);
		}
	}
	return positions;
}

Vector2D World::getBoardSize()
{
	return boardSize;
}

Vector2D World::getUpperLeft()
{
	return upperLeft;
}

Vector2D World::getDiamondPosition()
{
	return diamondPosition;
}

Vector2D World::getPlayerPosition()
{
	return playerPosition;
}

void World::exchangeDiamondPosition()
{
	auto positions = getPositionsForSpawnMonsters();
	auto index = std::rand() % positions->size();
	diamondPosition = positions->at(index);
}
