#include <iostream>
#include "window/window.h"
#include "objects/prop.h"
#include "utilities/timer.h"
#include "objects/actor.h"
using namespace std;
int main(int argc, char** argv)
{
	bool isDone = false;

	SDL_Event event;
	Window window;
	Actor actor({0,0}, {400,400}, "crate.png");
	while( !isDone)
	{

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				isDone = true;
			}
			actor.handleEvents(event);
		}

		Timer::Instance().Update();

		SDL_RenderClear(window.GetRenderer());
		window.RenderProp(actor);
		SDL_RenderPresent(window.GetRenderer());
	}


	return 0;
}
