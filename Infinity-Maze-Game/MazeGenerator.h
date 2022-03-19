#ifndef MAZE
#define MAZE

#include <vector>
#include <stdlib.h> 

struct Vector2D
{
	int x;
	int y;
};

inline int vector2DHash(const Vector2D& vec)
{
	return vec.x * 5 - vec.y * 17;
}

inline bool operator<(const Vector2D& lhs, const Vector2D& rhs)
{
	return vector2DHash(lhs) < vector2DHash(rhs);
}

inline bool operator==(const Vector2D& lhs, const Vector2D& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

const int blockSize = 5;

const int blockVariants = 6;

class MazeGenerator
{
public:

	MazeGenerator();

	bool isCorridor(Vector2D position);

private:

	bool isCorridor(Vector2D position, bool connectBlocks);

	Vector2D moduls[6] = { {6,6}, {4,6}, {4,4}, {6,4}, {3,4}, {3,5} };
	Vector2D shifts[6] = { {1,2}, {3,2}, {3,2}, {1,2}, {1,3}, {2,3} };

	void shuffle(Vector2D array[]);
};

#endif