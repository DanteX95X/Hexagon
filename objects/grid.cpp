#include "grid.h"


void Grid::init()
{

	int left = 0;
	int right = 5;
	for(int i = -4; i < 5; ++i)
	{
		for(int j = left; j < right; ++j)
		{
			if( ( i==-1 && j == 0 ) || ( i == 0 && j == 1 ) || ( i == 1 && j == -1 ) )
				continue;
			
			const double proportion = 0.485;
			double x =  position.x + size*proportion * 1.5 * static_cast<double>(j);
			double y  =  position.y + 1.73*size*proportion*static_cast<double>(i) + 1.73*size*proportion*0.5*static_cast<double>(j);
			
			Vector2 axial(static_cast<double>(j), static_cast<double>(i));
			Field temporaryField(axial, {x,y},size, "crate.png", Owner::PLAYER);
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
		i->second.Render(window.GetRenderer());
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


std::map<std::pair<int, int>, Field>& Grid::GetFields() { return fieldsMap; }