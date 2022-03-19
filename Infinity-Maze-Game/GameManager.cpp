#include "GameManager.h"

GameManager::GameManager()
{
	world = new World();
	renderer = new WorldRenderer(world);

	auto positions = world->getPositionsForSpawnPlayer();
	auto index = std::rand() % positions->size();
	auto playerPosition = positions->at(index);

	player = new Player(world, playerPosition);
	monsters = new std::list<Monster*>();
	monstersCount = 0;

	font.loadFromFile("Fonts/arial.ttf");
	text.setFont(font);
	text.setString(" ");
	text.setFillColor(sf::Color::Magenta);
	text.setStyle(sf::Text::Bold);
	text.setPosition({ 10, (float)boardSize.y + 10 });
	text.setCharacterSize(charcterSize/2);
	giveUp = new Button({ 10, (float)boardSize.y + 40 }, buttonSize, "give up");

	showingResult = showingResultTime;
}

void GameManager::pollEvent(sf::Event* event)
{
	if (!__isfinished())
	{
		player->pollEvent(event);
		giveUp->pollEvent(event);
	}
}

void GameManager::update()
{
	if (!__isfinished())
	{
		world->update();
		player->update();
		updateMonsters();
		updateText();
		giveUp->update();
	}
	else
	{
		result();
		showingResult--;
	}
}

void GameManager::render(sf::RenderWindow* window)
{
	if (!__isfinished())
	{
		renderer->render(window);
		giveUp->render(window);
	}
	window->draw(text);
}

bool GameManager::isfinished()
{
	return showingResult == 0;
}

GameManager::~GameManager()
{
	delete player;
	delete renderer;
	delete world;
	monsters->clear();
	delete monsters;
	delete giveUp;
}

bool GameManager::__isfinished()
{
	return player->getDiamondsCount() >= requiredDiamonds
		|| player->isKilled()
		|| giveUp->wasClicked();
}

void GameManager::updateText()
{
	std::string actualText = "Diamonds: " 
		+ std::to_string(player->getDiamondsCount()) 
		+ " / " 
		+ std::to_string(requiredDiamonds)
		+ "     Locks available: "
		+ std::to_string(player->getLocksCount())
		+ " / " 
		+ std::to_string(startNumberOfLocks)
		+ "     Direction to diamond: ";

	Vector2D direction = {	world->getDiamondPosition().x - player->getPosition().x,
							world->getDiamondPosition().y - player->getPosition().y };

	if (std::labs(direction.x) > std::labs(direction.y))
	{
		if (direction.x > 0)
		{
			actualText += "east";
		}
		else{
			actualText += "west";
		}
	}
	else
	{
		if (direction.y > 0)
		{
			actualText += "south";
		}
		else
		{
			actualText += "north";
		}
	}
	text.setString(actualText);
}

void GameManager::result()
{
	text.setPosition({ (float)boardSize.x / 2, (float)boardSize.y / 2 });
	if (player->getDiamondsCount() < requiredDiamonds)
	{
		text.setFillColor(sf::Color::Red);
		text.setString("You lose this game, try agin");
	}
	else
	{
		text.setFillColor(sf::Color::Green);
		text.setString("You won the game!");
	}
}

void GameManager::updateMonsters()
{
	for (int i = monstersCount; i < minMonstersNumber + monstersNumberBonus * player->getDiamondsCount(); i++)
	{
		auto positions = world->getPositionsForSpawnMonsters();
		auto position = positions->at(rand() % positions->size());
		Monster* monster = new Monster(world, position);
		world->addMonsterPosition(position);
		monsters->push_back(monster);
		monstersCount++;
	}
	for (auto monster : *monsters)
	{
		monster->update();
	}
}
