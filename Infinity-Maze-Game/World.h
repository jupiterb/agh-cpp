#ifndef WORLD
#define WORLD

#include "MazeGenerator.h"
#include <list>
#include <random>
#include <iostream>

static const Vector2D preferedBoardSize = { 50, 50 };

enum class WorldElement
{
	_CORRIDOR,
	_WALL, 
	_PLAYER,
	_MONSTER,
	_DIAMOND, 
	_LOCK
};


class World
{
public:

	World();

	~World();

	// API for GameManager

	void update();

	// API for MovingElements

	bool canGoTo(Vector2D position);

	// API for MovingElements and WorldRenderer

	WorldElement getWorldElment(Vector2D position);

	// API for Player

	void setPlayerPosition(Vector2D position);

	void setLock(Vector2D position);

	// API for Monsters

	void removeMonsterPosition(Vector2D position);

	void addMonsterPosition(Vector2D position);

	// API for WorldRenderer and position vectors getters

	std::vector<Vector2D> * getPositionsOnBorad();

	std::vector<Vector2D> * getPositionsForSpawnMonsters();

	std::vector<Vector2D> * getPositionsForSpawnPlayer();

	// other getters

	Vector2D getBoardSize();

	Vector2D getUpperLeft();

	Vector2D getDiamondPosition();

	Vector2D getPlayerPosition();

private:

	void exchangeDiamondPosition();

	MazeGenerator* generator;

	Vector2D upperLeft;

	Vector2D boardSize;

	Vector2D playerPosition;
	
	Vector2D diamondPosition;

	std::list<Vector2D> *monstersPositions;

	std::list<Vector2D>* locks;
};

#endif