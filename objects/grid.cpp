#include "grid.h"


void Grid::init()
{

	int left = 0;
	int right = 5;
	for(int i = -4; i < 5; ++i)
	{
		for(int j = left; j < right; ++j)
		{
			
			double x =  position.x + 32*0.5 * 1.5 * static_cast<double>(j);
			double y  =  position.y + 1.73*32*0.5*static_cast<double>(i) + 1.73*32*0.5*0.5*static_cast<double>(j);
			
			Field* temporaryField = new Field({x,y},{static_cast<double>(j),static_cast<double>(i)},32, "crate.png");
			fields.push_back(temporaryField);
			
			//i is a second coordinate
		}
		
		if(i<0) --left;
		else --right;
		
	}

}


void Grid::render(Window& window)
{
	for(unsigned int i = 0; i < fields.size(); ++i)
	{
		window.RenderProp(*(fields[i]));
	}
}

void Grid::Update()
{
}