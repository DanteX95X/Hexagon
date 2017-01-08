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
Prop::Prop(Vector2 initPosition, Vector2 initSize)
    : Object(initPosition, initSize)
{
}


Vector2 Prop::GetPosition() { return Object::GetPosition(); }
Vector2 Prop::GetSize() { return Object::GetSize(); }


void Prop::SetTexture(SDL_Texture* texture)
{ this->texture = texture; }

SDL_Texture* Prop::GetTexture() { return texture; }
