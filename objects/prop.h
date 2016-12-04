#ifndef PROP_H
#define PROP_H

#include "object.h"
#include <string>
#include <SDL2/SDL.h>

class Prop : public Object
{
public:
	Prop(Vector2 initPosition, Vector2 initSize, std::string spritePath);
	Prop(std::string spritePath);
	
	virtual void Update() override;
	
	SDL_Texture* GetTexture();
private:
	void LoadTexture(std::string spritePath);
	
	SDL_Texture* texture;
	
};

#endif //PROP_H