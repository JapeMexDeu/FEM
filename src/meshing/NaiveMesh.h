#ifndef NAIVEMESH_H
#define NAIVEMESH_H
#include"Mesh.h"
#include"../elements/Quad2.h"
class NaiveMesh:public Mesh
{
	public:
		
		//*********GEOMETRY OF NAIVE MESH***********
		int a,b,c,d;
		
		NaiveMesh(int n=2, int m=2);
		
		virtual void print()override;
		
		//Setters and getters
		//virtual Vector<Element> getElements()override;
		virtual void setNumElements(int n, int m)override;
 		virtual void setNumNodes(int n, int m)override;
		virtual void setElementMaterial(ElasticMaterial* mat)override;
	//protected:
		
	private:
		Vector<Quad2> local_elements;
		void InitializeMesh();//Inside here we can define, without creating, an implicit geometry
		int n, m;
		
};
		
#endif