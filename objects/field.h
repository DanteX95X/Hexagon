#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "prop.h"

class Field : public Prop
{
public:
	Field(Vector2 position, Vector2 abstractPosition, float size, std::string texturePath)
	:Prop(Vector2 (position.x - size*0.5, position.y - size*0.5), Vector2 (size, size), texturePath)
	{
	}
	

private:
	std::vector<Field*> neighbours;
};


#endif