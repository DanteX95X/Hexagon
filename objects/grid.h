#ifndef GRID_H
#define GRID_H
#include "field.h"
#include "window/window.h"

class Grid: public Object
{
public:
	Grid(Vector2 initPosition, double size)
	:Object(initPosition, Vector2(size*5, size*5)) 
	{
		position = initPosition;
		this->size = size;
	};
	
	void init();
	void render(Window& window);
	
	virtual void Update() override;
	
private:
	std::vector< Field > fields;
	Vector2 position;
	double size;
};

#endif