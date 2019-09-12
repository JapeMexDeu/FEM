/**
  FILE: Assembly.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Within this class the global stiffness matrix K and the global force vector f, for a FEM setting, will be generated. This is a 
			   NON-INSTANTIABLE CLASS, only provides interface functionality.
			   The class must have minimal access to classes DISCRETIZATION, since through it we can access the underlying MESH and element type of it.
			   In the implementation of this class is where we should be able to find the global stiffness matrix and global force vector as 
			   physical instances.
			   
			 		 
*/

#ifndef ASSEMBLY
#define ASSEMBLY

#include"Discretization.h"

class Assembly
{
	public:
		/*!\brief Method based on "Introduction to Finite Element", Lecture Notes, by G.P. Nikishkov.

		 */
		virtual void matrixAssemblyRoutine()=0;
		virtual void vectorAssemblyRoutine()=0;
		virtual void localSolutionVectorAssemblyRoutine(Vector<double>& globalSolution)=0;
	private:
		/*!\brief Receives element and an index {0,dofsPerNode} -which is element type dependent, and returns the global Node number.
		 *This function maps the received element el and an index i that goes from 0 to n-1 (number of dofs per element), to the dofNumber inside a 
		 *certain node, using the dofsPerNode quantity, which is found as follows:
		 *1.-check for the node: i/dofsPerNode-> yields a number between 0 and numberNodes*dofsPerNode
		 *2.-check which dof of the found node: i mod dofsPerNode-> yields a number between 0 and dofsPerNode-1 indicating the index in the dofNumbers 
		 *vector
		 */
		virtual int connectivityArray(Element* el, int i)=0;
	
};
#endif