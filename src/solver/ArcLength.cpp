#include"ArcLength.h"

ArcLength::ArcLength(ImplAssembly& assembly, double ds, double tol/*=10e-10*/, int maxIterations/*=10*/)
					 :Assembly(assembly), Kt(Assembly.getGlobalMatrix()), lSolver(nullptr),
					 tolerance(tol), maxIterations(maxIterations), ds(ds), dofs(Assembly.getTotalDOF())
{
	setLSolver();
	zero();
}


void ArcLength::solve()
{
	
	//Begin of load step here
	Assembly.matrixAssemblyRoutine();
	Kt=Assembly.getGlobalMatrix();
}
void ArcLength::setLSolver()
{
	lSolver=&cg;
}
void ArcLength::printArcLength()
{
	std::cout<<"\nARC LENGTH METHOD WITH CRISFIELD APPROACH\n";
	std::cout<<"THE PARAMETERS ARE: \n";
	std::cout<<"PATH LENGTH INCREMENT IS: "<<sd<<"\n";
	std::cout<<"TOLERANCE IS: "<<tolerance<<"\n";
	std::cout<<"THE MAX. NUMBER OF ITERATIONS PER STEP IS: "<<maxIterations<<std::endl;
}
//PRIVATE METHODS THAT NEED NOT BE SEEN
void ArcLength::intializeSolver()
{
	//Resize all what needs resizing
	r.resize(dofs);
	u_total.resize(dofs);
	aI.resize(dofs);
	aII.resize(dofs);
}
void ArcLength::zero()
{
	
	r=0;
	u_total=0;
	aI=0;
	aII=0;
}