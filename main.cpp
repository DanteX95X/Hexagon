#include <iostream>
#include "window/window.h"
#include "objects/prop.h"
#include "utilities/timer.h"

int main(int argc, char** argv)
{
	bool isDone = false;
	
	SDL_Event event;
	Window window;
	

	Prop prop({0,0}, {320,240}, "crate.png");
	
	while( !isDone)
	{
		
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				isDone = true;
			}

		}
		Timer::Instance().Update();
		
		SDL_RenderClear(window.GetRenderer());
		window.RenderProp(prop);
		SDL_RenderPresent(window.GetRenderer());
	}
	
	
	return 0;
}
