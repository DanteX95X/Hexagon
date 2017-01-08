#include "field.h"
#include <iostream>
#include "../utilities/texture_flyweight.h"

Field::Field(Vector2 initAxial, Vector2 position, float size, std::string texturePath, Owner initOwner)
	:Actor(Vector2 (position.x - size*0.5, position.y - size*0.5), 
	Vector2 (size, size), texturePath), 
	axial{initAxial}, 
	owner{initOwner} 
{
	playerPawn = TextureFlyweight::Instance().GetTexture("pawn_blue.png");
	opponentPawn = TextureFlyweight::Instance().GetTexture("pawn_red.png");
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
		{
            std::cout << axial;
			std::cout <<  " ";
			std::cout  << static_cast<int> (owner) << "\n";
		}
    }
}

void Field::Update()
{
}

void Field::Render(SDL_Renderer* renderer)
{
	Actor::Render(renderer);
	
	SDL_Rect destination = { static_cast<int>(position.x + size.x/4), static_cast<int>(position.y + size.y/4), static_cast<int>(size.x/2), static_cast<int>(size.y/2) };
	if( owner == Owner::PLAYER )
		SDL_RenderCopy(renderer, playerPawn, nullptr, &destination);
	else if( owner == Owner::OPPONENT )
		SDL_RenderCopy(renderer, opponentPawn, nullptr, &destination);
}