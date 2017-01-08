#include "hex.h"
#include <math.h>

std::vector<Vector2> Hex::displacements = { Vector2(1, 0), Vector2(-1, 0), Vector2(0, 1), Vector2(0, -1), Vector2(1, -1), Vector2(-1, 1) };

unsigned int Hex::Distance(const Vector2& first, const Vector2& second)
{
	return ( abs(first.x - second.x) + abs(first.x + first.y - second.x - second.y) + abs(first.y - second.y) ) / 2;
}