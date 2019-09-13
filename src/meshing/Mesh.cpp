#include"Mesh.h"

void Mesh::print()
{
	std::cout<<"BEGIN: PRINTING OF MESH******\n";
	std::cout<<"   NODES: "<<numNodes<<"\n";
	std::cout<<"   ELEMENTS: "<<numElements<<"\n";
	//std::cout<<"TYPE: "<<typeOfElement<<"\n";
/* 	for(int i=0;i<nodes.size();++i)
	{
		nodes[i].print();
	} */
}
Node* Mesh::getNode(int key)
{
	
	int i=0;
	while(i<nodes.size())
	{
		if(nodes[i].getNodeNumber()==key)
		{
			return &nodes[i];
		}
		++i;
	}
	return nullptr;
}
int Mesh::getNumElements()
{
	return numElements;
}
int Mesh::getNumNodes()
{
	return numNodes;
}
Vector<Node>& Mesh::getNodes()
{
	return nodes;
}
Vector<Element*>& Mesh::getElements()
{
	return elements;
}
