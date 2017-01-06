#include <iostream>
#include "window/window.h"
#include "objects/prop.h"
#include "utilities/timer.h"
#include "min_max/vertex.h"
#include <queue>

int main(int argc, char** argv)
{
	bool isDone = false;
	
	SDL_Event event;
	Window window;
	
	Prop prop({0,0}, {240, 240}, "crate.png");
	
	int childQuantity, value;
	std::cin >> childQuantity >> value;
	Vertex* root = Vertex::BuildTree(childQuantity, value);
	
	std::cout << "\n";
	std::queue<Vertex*> queue;
	queue.push(root);
	while(queue.size() > 0)
	{
		std::cout << queue.front()->GetValue() << " " << queue.front()->GetChildren().size() << "\n";
		for(Vertex*& vertex : queue.front()->GetChildren())
			queue.push(vertex);
		
		queue.pop();
	}
	
	delete root;
	
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
