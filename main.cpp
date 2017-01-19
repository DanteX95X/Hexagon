#include <iostream>
#include "window/window.h"
#include "objects/prop.h"
#include "objects/field.h"
#include "utilities/timer.h"

#include "objects/hexagon_game.h"

#include "objects/actor.h"
#include "min_max/vertex.h"
#include <queue>
#include "min_max/ai.h"

int main(int argc, char** argv)
{
	bool isDone = false;

	SDL_Event event;
	Window window;

	HexagonGame game(Vector2 (300,200), {true, true});

	/*int childQuantity, value;
	std::cin >> childQuantity >> value;
	Vertex* root = Vertex::BuildTree(0, childQuantity, value);
	AI::AlphaBetaPruning(root, 100, INT_MIN, INT_MAX, true);

	std::cout << "\n";
	std::queue<Vertex*> queue;
	queue.push(root);
	while(queue.size() > 0)
	{
		std::cout <<queue.front()->GetDepth() << " " << queue.front()->GetValue() << " " << queue.front()->GetChildren().size() << "\n";
		for(Vertex*& vertex : queue.front()->GetChildren())
			queue.push(vertex);

		queue.pop();
	}

	delete root;*/

	
	while( !isDone)
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

		SDL_RenderPresent(window.GetRenderer());
	}


	return 0;
}
