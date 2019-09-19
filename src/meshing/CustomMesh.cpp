#include"CustomMesh.h"

CustomMesh::CustomMesh(int n, int e)
{
	typeOfElement="4-NODE QUAD";
	numNodes=n;
	numElements=e;
	
	nodes.resize(numNodes);
	elements.resize(numElements);
	local_elements.resize(numElements);
	for(int i=0;i<elements.size();++i)
	{
		
		
		elements[i]=&(local_elements[i]);
		
		
	}
}

void CustomMesh::setNumElements(int n, int m)
{
	numElements=n;
}
void CustomMesh::setNumNodes(int n, int m)
{
	numElements=n;
}
void CustomMesh::setElementMaterial(Material* mat)
{
	for(int i=0;i<local_elements.size();++i)
	{
		local_elements[i].setMaterial(mat);
	}
}
void CustomMesh::print()
{
	Mesh::print();
	std::cout<<"   TYPE: "<<typeOfElement<<"\n";
	
	for(int i=0;i<nodes.size();++i)
	{
		std::cout<<"   "<<nodes[i];
	}
	for(int i=0;i<elements.size();++i)
	{
		std::cout<<"   "<<local_elements[i];
	}
	std::cout<<"END: PRINTING OF MESH******\n";
}
