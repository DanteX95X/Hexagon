#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "actor.h"

class Field : public Actor
{
public:
	Field(Vector2 initAxial, Vector2 position, float size, std::string texturePath);
	
	void HandleEvents(SDL_Event& event) override;
	void Update() override;
	
private:
	Vector2 axial;
};


#endif