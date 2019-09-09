#ifndef DISCRETIZATION_H
#define DISCRETIZATION_H

#include"IDiscretization.h"

class Discretization:public IDiscretization
{
	public:
		/*!\brief Just in case
		 *Constructor, must receive a mesh and the amount of degrees of freedom per node for the discretized geometry
		 *
		 */
		Discretization(int dof, Mesh& mesh);
		virtual void DOFenum()override;
		virtual void addDOF()override;
		virtual Vector<BoundaryConditions>* modify_boundary_conditions()override;
		virtual void addBoundaryCondition(BoundaryConditions bc)override;
		virtual void print()override;
		//Setters and getters
		int getTotalDOF();
		int getDofPerNode();
		Mesh& getMesh();
		
	private:
		virtual void applyBoundaryConditions()override;
		virtual void applyBoundaryConditionsHelper(BoundaryConditions* bc, Node** node)override;
		virtual void resizeMeshDof()override;
		/*!\brief Used inside DOFenum, called recursively for every node of the Mesh to assign numbers and return last
		 *Function gets an integer, which is our starting point for numbering, and a pointer to a Node. We will modify the dofNumbers vector
		 *and return the last value for further computations.
		 */
		int DOFenumHelper(int index, Node* node);
	//protected:
		int totalDOF;/**<Total number of degrees of freedom in discretization*/
		Mesh& mesh;/**<MESH will be modified and nodes initialized their DOFs*/
		int dofPerNode;/**<Degrees of freedom per node*/
		Vector<BoundaryConditions> boundary_conditions;/**<Stores all BOUNDARYCONDITIONS elements belonging to discretized model*/ 
};
#endif