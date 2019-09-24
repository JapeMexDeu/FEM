/**
  FILE: NLSolver.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Implements a Non Linear 
			   
*/
#ifndef NLSOLVER
#define NLSOLVER

#include"Solver.h"

class NLSolver
{
	public: 
		NLSolver();
		
	public:
		Vector<Vector<double>> steps;/**<Stores the solution increment vector from every step*/
		
	protected:
		int numSteps;/**<Total increments for the solution process*/
		Solver lSolver;/**<Linear Solver (based on linear iteration) that solves linearized problem*/
		Vector<double> u_total;/**<Accumulation of solution vectors per step*/
		Vector<double> r;/**<Represents \f$f_ext-f_int\f$*/
		
	private:
		void incrementLoad();
		void calculateR();
		
	public:
		
		struct Step
		{
			public:
				Vector<double> u_step;
				Vector<double> f;
				
		}
	
};
#endif