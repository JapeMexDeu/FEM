/**
  FILE: ArcLength.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Experimental implementation of a non-linear arc-length control method based on the Criesfield 
			   approach. We want to compare to our Newton Rapshon poorman's approach. The linear solver is 
			   defined as a Conjugate Gradient method. Add then the BiCGStab method.
			   
*/
#ifndef ARCLENGTH_H
#define ARCLENGTH_H

#include"../fem/ImplAssembly.h"
#include"LSolver.h"
#include"../plotter/gnuplot_i.hpp"
#include"../plotter/Plotter.h"

class ArcLength
{
	public: 
		ArcLength(ImplAssembly& assembly, double ds=0.0001, double tol=10e-10, int maxIterations=10);
		
	public:
		Vector<Vector<double>> steps;/**<Stores the solution increment vector from every step*/
		void solve();
		void printArcLength();
		
	protected:
		ConjugateGradientDescent cg=ConjugateGradientDescent(Kt,r);
		//MEMBER ATTRIBUTES PROPER TO A NONLINEAR INCREMENTAL APPROACH
		ImplAssembly& Assembly;
		LSolver* lSolver;/**<Linear Solver that solves linearized problem for the displacement*/
		Matrix<double>& Kt;/**<Reference to the matrix stored in the Assembly*/
		Vector<double> u_total;/**<Accumulation of solution vectors per step*///also called u_current
		Vector<double> r;/**<Represents \f$f_ext-f_int\f$*/
		double tolerance;/**<minimal value of norm searched for*/
		int maxIterations;/**<control max amount of iterations*/
		double ds;/**<Arc length user-defined parameter*/
	private:
		void setLSolver();
		void initializeSolver();
		void zero();
	private:
		int dofs;
		Vector<double> aI;
		Vector<double> aII;
		
	
};
#endif