#ifndef HEX_H
#define HEX_H

#include "vector2.h"
#include <vector>

namespace Hex
{
	extern std::vector<Vector2> displacements;
	unsigned int Distance(const Vector2& first, const Vector2& second);
}

#endif //HEX_H