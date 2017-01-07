#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <climits>

class Vertex
{
public:
	Vertex(int initDepth, int initValue = INT_MIN);
	~Vertex();
	
	void AddChild(Vertex* child);
	
	static Vertex* BuildTree(int depth, int childQuantity, int value);
	
	int GetValue();
	void SetValue(int value);
	std::vector<Vertex*>& GetChildren();
	int GetDepth();
	
private:
	int value;
	int depth;
	std::vector<Vertex*> children;
};

#endif //VERTEX_H