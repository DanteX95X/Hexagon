#include <iostream>
#include "window/window.h"
#include "utilities/texture_flyweight.h"

int main(int argc, char** argv)
{
	bool isDone = false;
	
	SDL_Event event;
	Window window;
	
	SDL_Texture* t = TextureFlyweight::Instance().GetTexture("crate.png");
	if(t == nullptr)
		std::cout << "Dupa\n";
	
	
	while( !isDone)
	{
		
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				isDone = true;
			}

		}
		
		SDL_RenderClear(window.GetRenderer());
		SDL_RenderCopy(window.GetRenderer(), t, NULL, NULL);
		SDL_RenderPresent(window.GetRenderer());
	}
	
	
	return 0;
}
