#include "grid.h"


void Grid::init()
{

	int left = 0;
	int right = 5;
	for(int i = -4; i < 5; ++i)
	{
		for(int j = left; j < right; ++j)
		{
			double proportion = 0.485;
			double x =  position.x + size*proportion * 1.5 * static_cast<double>(j);
			double y  =  position.y + 1.73*size*proportion*static_cast<double>(i) + 1.73*size*proportion*0.5*static_cast<double>(j);
			
			Field temporaryField({x,y},size, "crate.png");
			std::pair<int, int> abstractCoordinates(j, i);
			fieldsMap.insert(std::pair<std::pair<int, int>, Field>(abstractCoordinates, temporaryField));
		}
		
		if(i<0) --left;
		else --right;
		
	}

}


void Grid::render(Window& window)
{
	for(typename std::map<std::pair<int, int>, Field>::iterator i = fieldsMap.begin(); i != fieldsMap.end(); ++i)
	{
		window.RenderProp((*i).second);
	}
}

void Grid::Update()
{
}

Grid::Grid(Vector2 initPosition, double size)
:Object(initPosition, Vector2(size*5, size*5)) 
{
	position = initPosition;
	this->size = size;
};
