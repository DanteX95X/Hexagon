#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

class Vertex
{
public:
	Vertex(int initValue = 0);
	~Vertex();
	
	void AddChild(Vertex* child);
	
	static Vertex* BuildTree(int childQuantity, int value);
	
	int GetValue();
	std::vector<Vertex*>& GetChildren();
private:
	int value;
	std::vector<Vertex*> children;
};

#endif //VERTEX_H