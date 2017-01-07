#include "actor.h"
#include<iostream>
#include<math.h>
#include "../utilities/texture_flyweight.h"

Actor::Actor(Vector2 initPosition, Vector2 initSize, std::string spritePath)
	: Prop(initPosition, initSize)
{
    SetTexture(TextureFlyweight::Instance().GetTexture(spritePath));
}


void Actor::HandleEvents(SDL_Event event)
{
    int x,y;
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState(&x, &y);

        Vector2 clickPosition = Vector2((double)x,(double)y);
        Vector2 midPosition = Vector2(Prop::GetPosition().x+(Prop::GetSize().x/2),Prop::GetPosition().y+(Prop::GetSize().y/2));
        if(IsMouseInside(clickPosition, midPosition ,Prop::GetSize().x))
            std::cout << "JESTEM" << "\n";
        else
            std::cout << "NO NIE ZA BARDZO" << "\n";
    }
}

bool Actor::IsMouseInside(Vector2 clickPosition, Vector2 midPosition, double side)
{
    if( pow((clickPosition.x-midPosition.x),2) + pow((clickPosition.y - midPosition.y),2) < pow(side/2,2 ))
		return true;
    return false;
}
