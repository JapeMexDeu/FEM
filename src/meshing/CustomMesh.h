#ifndef CUSTOM_MESH
#define CUSTOM_MESH
#include"Mesh.h"
#include"../elements/Quad2.h"
class CustomMesh:public Mesh
{
	public:
		CustomMesh(int nodes, int elements);
		virtual void print()override;
			
		//Setters and getters
		//virtual Vector<Element> getElements()override;
		virtual void setNumElements(int n, int m=0)override;
		virtual void setNumNodes(int n, int m=0)override;
		virtual void setElementMaterial(Material* mat)override;
		
	private:
		Vector<Quad2> local_elements;
};
#endif