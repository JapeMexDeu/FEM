#ifndef IDISCRETIZATION_H
#define IDISCRETIZATION_H

#include"../meshing/Mesh.h"
#include"../physics/BoundaryConditions.h"

class IDiscretization
{
	public:
		
		~IDiscretization()
		{};
		//Discretization(int dof);
		virtual void DOFenum()=0;
		/*!\brief Just in case
		 */
		virtual void addDOF()=0;
		virtual void print()=0;
		//****SETTERS AND GETTERS*****
		/*!\brief Reference-by-pointer
		 */
		virtual Vector<BoundaryConditions>* modify_boundary_conditions()=0;
		virtual void addBoundaryCondition(BoundaryConditions bc)=0;
		
		
		
	private:
		/*!\brief Used within DOFenum to constrain the indicated nodes
		 */
		virtual void applyBoundaryConditions()=0;
		virtual void applyBoundaryConditionsHelper(BoundaryConditions* bc, Node** node)=0;
		/*!\brief Manipulates MESH nodes vector to resize the dofs and dofnumbers, and set the static member numDOF
		 */
		virtual void resizeMeshDof()=0;
		
		
	protected:
//		Mesh& mesh;/**<MESH will be modified and nodes initialized their DOFs*/
	//	int dofPerNode;/**<Degrees of freedom per node*/
		//Vector<BoundaryConditions> boundary_conditions;/**<Stores all BOUNDARYCONDITIONS elements belonging to discretized model*/
		
};
#endif