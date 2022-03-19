#include "MazeGenerator.h"

int _abs(int number)
{
	if (number < 0) return (-1) * number;
	else return number;
}

MazeGenerator::MazeGenerator()
{
	shuffle(shifts);
	shuffle(moduls);
}

bool MazeGenerator::isCorridor(Vector2D position)
{
	return isCorridor(position, true);
}

bool MazeGenerator::isCorridor(Vector2D position, bool connectBlocks)
{
	Vector2D blockPosition = { position.x / blockSize, position.y / blockSize };
	if (blockPosition.x < 0) blockPosition.x--;
	if (blockPosition.y < 0) blockPosition.y--;

	int spiralCoord = _abs(blockPosition.x) >= _abs(blockPosition.y) ? blockPosition.x : blockPosition.y;
	int spiralTrans = (_abs(spiralCoord) * 2 - 1) * (_abs(spiralCoord) * 2 - 1);
	int blockIx = 0;

	if (blockPosition.x == spiralCoord && blockPosition.x > 0 && blockPosition.x > blockPosition.y)
	{
		blockIx = spiralTrans - blockPosition.y + _abs(spiralCoord) - 1;
	}
	else if (blockPosition.y == spiralCoord && blockPosition.y < 0 && abs(blockPosition.y) > blockPosition.x)
	{
		blockIx = spiralTrans + _abs(spiralCoord) * 3 - blockPosition.x  - 1;
	}
	else if (blockPosition.x == spiralCoord && blockPosition.x < 0 && blockPosition.x < blockPosition.y)
	{
		blockIx = spiralTrans + _abs(spiralCoord) * 5 + blockPosition.y - 1;
	}
	else if (blockPosition.y == spiralCoord && blockPosition.y > 0 && blockPosition.x > _abs(blockPosition.y))
	{
		blockIx = spiralTrans + _abs(spiralCoord) * 7 + blockPosition.x - 1;
	}
	blockIx = blockIx % blockVariants;

	if ((position.x - this->shifts[blockIx].x) % this->moduls[blockIx].x == 0)
	{
		return true;
	}
	if ((position.y - this->shifts[blockIx].y) % this->moduls[blockIx].y == 0)
	{
		return true;
	}
	if (connectBlocks)
	{
		short count = 0;
		for (int i = 0; i < 9 ; i++)
		{
			int x = i % 3 - 1;
			int y = i / 3 - 1;
			if (isCorridor({ position.x + x, position.y + y }, false))
			{
				if (_abs(x) + _abs(y) == 1)
				{
					count++;
				}
				else if (_abs(x) + _abs(y) == 2)
				{
					count--;
				}
			}
		}
		return count > 0;
	}
	return false;
}

void MazeGenerator::shuffle(Vector2D array[])
{
	int weights[blockVariants] = {}, max;
	for (int i = 0; i < blockVariants; i++)
	{
		weights[i] = rand() % 100;
	}
	for (int i = 0; i < blockVariants; i++) 
	{
		max = i;
		for (int j = i + 1; j < blockVariants; j++)
		{
			if (weights[max] < weights[max]) max = j;
		}
		weights[max] = weights[i];
		auto temp = array[i];
		array[i] = array[max];
		array[max] = temp;
	}
}
