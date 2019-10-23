#ifndef NODE_H
#define NODE_H

#include"../algebra/Vector.h"
#include"../physics/Force.h"
class Node
{
	public:
		Node(double x=0, double y=0, double z=0);
		Node(Vector<double> &coords);		
		//****SETTERS AND GETTERS******
		void setPosition(double x, double y, double z);
		void setPosition(Vector<double> &coords);
		void setX(double a);
		void setY(double a);
		void setZ(double a);
		void setPointForce(Force* f);
		Force* getPointForce();
		//*****VECTOR MEMBER ACCESS
		Vector<double> getPosition();
		Vector<int>& getDOFnumbers();
		Vector<double> getDOFs();
		//Vector<int> getDOFnumbersPtr();
		static int getNodesTotalNumber();
		void setDOF(int dof);/**<Should resize vectors dofs and dofNumbers to the size of dof*/
		int getDOF();
		int getNodeNumber();
		static void setNumDof(int);
		static int getNumDof();
		void print();
		//Operator Overload
		friend std::ostream& operator<<(std::ostream &out, Node& n);
	private:
		Force* pointForce;
		Vector<double> internalForce=Vector<double>(3);
		Vector<double> position=Vector<double>(3);/**<Stores xyz values*/
		Vector<double> dofs;/**<Values of DOFs of Node, in Mechanics its nodal displacements of size numDOF*/
		Vector<int> dofNumbers;/**<Global numbering of the DOFs, each entry will store a number or a -1 depending on the
							    constraints present*/
		
		int globalNum;/**<Node global number*/
		static int numDOF;/**<Degrees of freedom per node, provides size of numDOF*/
		static int totalNodes;/**<Total number of nodes*/
		
};
#endif
