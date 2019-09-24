/**
  FILE: NLSolver.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Implements a Non Linear 
			   
*/
#ifndef NLSOLVER
#define NLSOLVER

#include"../fem/ImplAssembly.h"
#include"LSolver.h"

class NLSolver
{
	public: 
		NLSolver(ImplAssembly& assembly, double tol=10e-10, int maxIterations=100, int stps=20);
		
	public:
		Vector<Vector<double>> steps;/**<Stores the solution increment vector from every step*/
		void solve();
	protected:
		//MEMBER ATTRIBUTES PROPER TO A NONLINEAR INCREMENTAL APPROACH
		ImplAssembly& Assembly;
		int numSteps;/**<Total increments for the solution process*/
		LSolver* lSolver;/**<Linear Solver that solves linearized problem, must be implemented in derived classes*/
		Vector<double> u_total;/**<Accumulation of solution vectors per step*///also called u_current
		Vector<double> r;/**<Represents \f$f_ext-f_int\f$*/
		double tolerance;/**<minimal value of norm searched for*/
		int maxIterations;/**<control max amount of iterations*/
	
		
	public:
		
		/* struct Step
		{
			public:
				Vector<double> u_step;
				Vector<double> f;
				
		} */
	
};
#endif