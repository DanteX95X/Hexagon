#ifndef PROP_H
#define PROP_H

#include "object.h"
#include <string>

class Prop : public Object
{
public:
	Prop(Vector2 initPosition, Vector2 initSize, std::string spritePath);
	Prop(std::string spritePath);
	
	virtual void Update() override;
	void Render();
	
private:
	void LoadTexture(std::string spritePath);
	
	SDL_Texture* texture;
	
}

#endif //PROP_H