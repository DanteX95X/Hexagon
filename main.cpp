#include <iostream>
#include "window/window.h"
#include "objects/prop.h"
#include "objects/field.h"
#include "utilities/timer.h"
#include "objects/grid.h"

int main(int argc, char** argv)
{
	bool isDone = false;
	
	SDL_Event event;
	Window window;
	

	//Field field({0,0}, 40, "crate.png");
	//Field field2({497*40*0.002,0}, 40, "crate.png");
	Grid grid(Vector2 (300,200), 50);
	grid.init();
	
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
		grid.render(window);

		SDL_RenderPresent(window.GetRenderer());
	}
	
	
	return 0;
}
