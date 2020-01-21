/**
  FILE: ArcLength.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Experimental implementation of a non-linear arc-length control method based on the Criesfield 
			   approach. We want to compare to our Newton Rapshon poorman's approach. The linear solver is 
			   defined as a Conjugate Gradient method. Add then the BiCGStab method.
			   
*/
#ifndef ARCLENGTH_H
#define ARCLENGTH_H

#include"descent/BiCGStab.h"
#include"../fem/ImplAssembly.h"
#include"LSolver.h"
#include"../plotter/gnuplot_i.hpp"
#include"../plotter/Plotter.h"

class ArcLength
{
	public: 
		ArcLength(ImplAssembly& assembly, double ds=0.0001, int maxSteps=1, 
				  double tol=10e-10, int maxIterations=10);
		
	public:

		void solve();
		void printArcLength();
		
	public:
		bool debug;
		bool verbose;
		
	protected:

		//MEMBER ATTRIBUTES PROPER TO A NONLINEAR INCREMENTAL APPROACH
		ImplAssembly& Assembly;
		//LSolver* lSolver;/**<Linear Solver that solves linearized problem for the displacement*/
		Matrix<double>& Kt;/**<Reference to the matrix stored in the Assembly*/
		Vector<double> u_total;/**<Accumulation of solution vectors per step*///also called u_current
		Vector<double> r;/**<Represents \f$f_{ext}-f_{int}\f$*/
		Vector<double> fext;/**<Normalized external load vector*/
		Vector<double> fint;/**<Internal force vector*/
		double tolerance;/**<Error reduction target*/
		int maxIterations;/**<control max amount of iterations*/
		double ds;/**<Arc length user-defined parameter*/
		double dLambda;
		double Lambda;
		
		Vector<double> uprev;
		double lambdaprev;
		
		
	private:
		/*!\brief Implements formula \f$ &Delta a_{j+1}=&Delta a_{j}+d&lambda_{j+1}da^{I}_{j+1}+da^{II}_{j+1}
		 */
		void updateValues();
		/*!\brief utility function to assign non-zero initial values and resize according to problem size
		 */
		void initializeSolver();
		/*!\brief Utility function to initialize to zero
		 */
		void initialValues();
		
	private:
		int lIts;/**<Counter for amount of iterations per step*/
		int steps;/**<Bookkeeping how many load steps so far*/
		int maxSteps;
		double normfext;/**<Store the norm of the external force*/
		double maxLambda;/**<Maximum value of lambda to be reached*/
		int dofs;/**<Bookkeeping size of problem*/
		Vector<double> daI;/**<Equivalent to \f$K^{-1}f_{ext}\f$*/
		Vector<double> daII;/**<Equivalent to \f$K^{-1}r\f$*/
		Vector<double> da;/**<Increment to nodal values*/
		
		
	
};
#endif