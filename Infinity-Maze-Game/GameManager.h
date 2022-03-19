#ifndef MANAGER
#define MANAGER

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Monster.h"
#include "WorldRenderer.h"
#include "Button.h"
#include <string> 



const int requiredDiamonds = 2;
const int minMonstersNumber = 30;
const int monstersNumberBonus = 10;

const int showingResultTime = 500;

class GameManager
{
public:

	GameManager();

	void pollEvent(sf::Event* event);

	void update();

	void render(sf::RenderWindow* window);

	bool isfinished();

	~GameManager();

private:

	Player* player;
	World* world;
	WorldRenderer* renderer;
	std::list<Monster*> * monsters;
	int monstersCount;

	sf::Font font;
	sf::Text text;

	bool __isfinished();

	void updateText();

	void result();

	void updateMonsters();

	int showingResult;

	Button* giveUp;
};

#endif

