#include "hex.h"
#include <math.h>


unsigned int Hex::Distance(const Vector2& first, const Vector2& second)
{
	return ( abs(first.x - second.x) + abs(first.x + first.y - second.x - second.y) + abs(first.y - second.y) ) / 2;
}