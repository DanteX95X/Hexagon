#include "prop.h"
#include "../utilities/texture_flyweight.h"

Prop::Prop(Vector2 initPosition, Vector2 initSize, std::string spritePath)
	: Object(initPosition, initSize), texture{TextureFlyweight::Instance().GetTexture(spritePath)}
{
}

Prop::Prop(std::string spritePath)
	: Object({0,0}, {0,0}), texture{TextureFlyweight::Instance().GetTexture(spritePath)}
{
}

void Prop::Update()
{
}

SDL_Texture* Prop::GetTexture() { return texture; }