#include "field.h"
#include <iostream>

Field::Field(Vector2 initAxial, Vector2 position, float size, std::string texturePath)
	:Actor(Vector2 (position.x - size*0.5, position.y - size*0.5), Vector2 (size, size), texturePath), axial{initAxial}
{
}

void Field::HandleEvents(SDL_Event& event)
{
	    int x,y;
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        SDL_GetMouseState(&x, &y);

        Vector2 clickPosition = Vector2((double)x,(double)y);
        Vector2 midPosition = Vector2(Prop::GetPosition().x+(Prop::GetSize().x/2),Prop::GetPosition().y+(Prop::GetSize().y/2));
        if( IsMouseInside(clickPosition, midPosition ,Prop::GetSize().x) )
            std::cout << axial << "\n";
    }
}

void Field::Update()
{
}