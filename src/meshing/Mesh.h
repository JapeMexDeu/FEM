/**
  FILE: Mesh.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: ABSTRACT NON-INTANTIABLE CLASS. Pure abstract class, provides base functionalities for mesh classes.
			   Most importantly provides the NODES and ELEMENTS stored in respective VECTORs. It should be passed as reference or
			   pointer to other classes, for it function as an "instantiable" object
  
			   
*/


#ifndef MESH_H
#define MESH_H

#include"../elements/Element.h"
#include"../elements/Node.h"
#include"../algebra/Vector.h"

class Mesh
{
	public:
		/*!\brief Print MESH information
		 */
		virtual void print();
		//*****SETTERS AND GETTERS
		/*!\brief Pointer to a node depending on the node local number starts at 0
		 */
		Node* getNode(int key);
		virtual void setNumElements(int n, int m)=0;
		int getNumElements();
		virtual void setNumNodes(int n, int m)=0;
		int getNumNodes();
		Vector<Node>& getNodes();
		Vector<Element*>& getElements();
		virtual void setElementMaterial(ElasticMaterial* mat)=0;
	protected:
		//Structures to store our data
		Vector<Node> nodes;/**<Stores nodes in MESH*/
		Vector<Element*> elements;/**<Stores elements in MESH*/
		int numNodes;
		int numElements;
		std::string typeOfElement;
	
};
#endif 