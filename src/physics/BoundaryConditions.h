/**
  FILE: BoundaryConditions.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: A boundary condition, or constraint, can be fixed or have a value, but not both. Class provides both structures, but only one must
			   be used. All member parameters are initialized to empty zero-sized vectors or vectors. Recommended to initialize vectors individually.
			   Size of dof is let free, assuming user understands that it makes sense to assign as many DOFs as the discretization chosen. But this
			   could be easily set by the discretization (NOT IMPLEMENTED, YET).
			   The vector value_conditions will either store values or be set to zero. Zero can be a value as long as the dof is free.
			   The vector fixed_conditions will either have TRUE: fixed; or FALSE: free. In case it is fixed, the value in value_conditions is irrelevant.
			   The vector node_indices stores the set of node indices to which the boundary condition applies.
*/

#ifndef BOUNDARYCONDITIONS_H
#define BOUNDARYCONDITIONS_H
#include"../elements/Node.h"
class BoundaryConditions
{
	public:
		BoundaryConditions(int degOF=0, std::string name="", Vector<double> values=Vector<double>(0),
						   Vector<bool> fixed=Vector<bool>(0), Vector<int> indices=Vector<int>(0));
		//*****SETTERES AND GETTERS
		Vector<double>& getValues();
		Vector<bool>& getFixed();
		Vector<int>& getIndices();
		/*!\brief Add index to the index vector
		 */
		void addNode(int index);
		/*!\brief Add node index through the node, to the index vector
		 */
		void addNode(Node* node);
		/*!\brief Receive a set of indices to store into index set
		 */
		void setNodes(Vector<int> indices);
		int getDOF() const;
		/*!\brief Assign a value to a certain index in the values vector
		 *Vector of values could also be accessed by reference, yielding this function unusable.
		 */
		void setValue(double value, int i);
		std::string getType();
		/*!\brief Set the given index to fixed. 
		 *Where TRUE: fixed
		 *		FALSE: free
		 */
		void fixDOF(int i);	
		virtual void print();
	protected:
		Vector<double> value_conditions;/*<<Vector of given initial values, lower precedence than fixed_conditions*/
		Vector<bool> fixed_conditions;/*<<Set that indicates if any DOFs are fixed or free, this variable is implementation dependent*/
		Vector<int> node_indices;/*<<Set of node pointers where BC is being applied to*/
		int dof;/*<<Degrees of freedom for a type of BC, some of them will be constrained*/
		std::string type;
};
#endif