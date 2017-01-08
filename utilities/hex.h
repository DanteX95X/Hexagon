#ifndef HEX_H
#define HEX_H

#include "vector2.h"
#include <vector>

namespace Hex
{
	extern std::vector<Vector2> displacements;// = { Vector2(1, 0), Vector2(-1, 0), Vector2(0, 1), Vector2(0, -1), Vector2(1, -1), Vector2(-1, 1) };
	
	unsigned int Distance(const Vector2& first, const Vector2& second);
}

#endif //HEX_H