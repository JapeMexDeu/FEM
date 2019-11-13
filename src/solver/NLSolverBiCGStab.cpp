#include"NLSolverBiCGStab.h"

NLSolverBiCGStab::NLSolverBiCGStab(ImplAssembly& assembly, double tol/*=10e-10*/, 
					   int maxIterations/*=100*/, int stps/*=20*/):NLSolver(assembly, tol, maxIterations,stps)
{
	setLSolver();
}
void NLSolverBiCGStab::setLSolver()
{
	lSolver=&cg;
}