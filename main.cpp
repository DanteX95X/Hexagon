#include <iostream>
#include "window/window.h"
#include "objects/prop.h"
#include "objects/field.h"
#include "utilities/timer.h"
#include "objects/hexagon_game.h"
#include "objects/actor.h"
#include <queue>
#include "min_max/ai.h"
#include "objects/text_field.h"

int main(int argc, char** argv)
{
	bool isDone = false;

	SDL_Event event;
	Window window;

	TextField textfield({0,0}, {100,50});
	textfield.LoadFont();
	textfield.LoadFromRenderedText(window.GetRenderer());
	
	
	while( !isDone && textfield.IsSet())
	{

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				isDone = true;
			}
			textfield.HandleEvents(event);
		}

		SDL_RenderClear(window.GetRenderer());

		textfield.Render(window.GetRenderer());

		SDL_RenderPresent(window.GetRenderer());
	}
	

	HexagonGame game(Vector2 (320,240), 50, textfield.GetStringAsInt(), {false, true});
	while( !isDone && game.GameOver() == Owner::NONE)
	{

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				isDone = true;
			}
			game.HandleEvents(event);
		}

		Timer::Instance().Update();
		game.Update();

		SDL_RenderClear(window.GetRenderer());
		
		game.Render(window.GetRenderer());
		textfield.Render(window.GetRenderer());

		SDL_RenderPresent(window.GetRenderer());
	}
	
	std::cout << "Winner: " << static_cast<int>(game.GameOver()) << "\n";
	
	if(game.GameOver() == Owner::PLAYER)
		textfield.SetText("Winner: Blue");
	else
		textfield.SetText("Winner: Red");
		
	while(!isDone)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				isDone = true;
			}
		}
		
		SDL_RenderClear(window.GetRenderer());
		textfield.Render(window.GetRenderer());
		SDL_RenderPresent(window.GetRenderer());
	}

	return 0;
}
