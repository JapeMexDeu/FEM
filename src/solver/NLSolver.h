/**
  FILE: NLSolver.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Implements a Non Linear 
			   
*/
#ifndef NLSOLVER
#define NLSOLVER

#include"../fem/ImplAssembly.h"
#include"LSolver.h"
#include"../plotter/gnuplot_i.hpp"
class NLSolver
{
	public: 
		NLSolver(ImplAssembly& assembly, double tol=10e-10, int maxIterations=100, int stps=20);
		
	public:
		Vector<Vector<double>> steps;/**<Stores the solution increment vector from every step*/
		void solve();
		void printNLSolver();
		Vector<double>& getAbscissae();
		Vector<double>& getOrdinates();
	protected:
		//For Plotting
		
		Vector<double> abscissae;
		Vector<double> ordinates;
		//MEMBER ATTRIBUTES PROPER TO A NONLINEAR INCREMENTAL APPROACH
		ImplAssembly& Assembly;
		int numSteps;/**<Total increments for the solution process*/
		LSolver* lSolver;/**<Linear Solver that solves linearized problem, must be implemented in derived classes*/
		Matrix<double>& Kt;/**<Reference to the matrix stored in the Assembly*/
		Vector<double> u_total;/**<Accumulation of solution vectors per step*///also called u_current
		Vector<double> r;/**<Represents \f$f_ext-f_int\f$*/
		double tolerance;/**<minimal value of norm searched for*/
		int maxIterations;/**<control max amount of iterations*/
	private:
		virtual void setLSolver()=0;
	public:
		
		
	
};
#endif