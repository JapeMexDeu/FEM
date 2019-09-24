/**
  FILE: ImplAssembly.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Provides an INSTANTIABLE CLASS for the class ASSEMBLY. Implements functions and provides data members.
			 		 
*/

#ifndef IMPLASSEMBLY_H
#define IMPLASSEMBLY_H
#include"Assembly.h"

class ImplAssembly:public Assembly
{
	public:
		ImplAssembly(Discretization* disc);
		virtual void matrixAssemblyRoutine()override;
		virtual void vectorAssemblyRoutine()override;
		virtual void localSolutionVectorAssemblyRoutine(Vector<double>& globalSolution) override;
		void printImplAssembly();
		//Setters and getters
		Matrix<double>& getGlobalMatrix();
		Vector<double>& getGlobalVector();
		int getTotalDOF();
	private:
		/*!\brief Receives element and an index {0,dofsPerNode} -which is element type dependent, and returns the global Node number
		 */
		virtual int connectivityArray(Element* el, int i)override;
		void setN();
	protected:
		//int dofsPerNode;/**<Number of degrees of freedom per Node, comes from Discretization or from size of nodes vector in element*/
		int n;/**<number of degrees of freedom per element, depends on element type and dofsPerNode*/
		int E;/**<total number of elements, can be taken directly from Element as a static function*/
		Discretization* disc;/**<Number of degrees of freedom per Node, comes from Discretization or from size of nodes vector in element*/
		Matrix<double> globalK;/**<Global stiffness matrix of the given discretized model*/
		Vector<double> globalF;/**<Global force vector of the given discretized model*/
		
};
#endif
