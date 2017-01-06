#include "actor.h"
#include<iostream>
#include<math.h>
#include "../utilities/texture_flyweight.h"

using namespace std;

Actor::Actor(Vector2 initPosition, Vector2 initSize, std::string spritePath)
	: Prop(initPosition, initSize)
{
    SetTexture(TextureFlyweight::Instance().GetTexture(spritePath));
}


void Actor::handleEvents(SDL_Event event)
{
    int x,y;
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState(&x, &y);
        cout<<"x: "<<x<<" y: " <<y<< endl;
        Vector2 clickPosition = Vector2((double)x,(double)y);
        Vector2 midPosition = Vector2(Prop::GetPosition().x+(Prop::GetSize().x/2),Prop::GetPosition().y+(Prop::GetSize().y/2));
        if(am_i_in(clickPosition, midPosition ,Prop::GetSize().x))
            cout<<"JESTEM"<<endl;
        else
            cout<<"NO NIE ZA BARDZO"<<endl;
    }
}

bool Actor::am_i_in(Vector2 clickPosition, Vector2 midPosition, double side)
{
    if(sqrt(pow((clickPosition.x-midPosition.x),2)+pow((clickPosition.y - midPosition.y),2))<side/2)
    return true;
    return false;
}
