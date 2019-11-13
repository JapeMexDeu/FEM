#ifndef NLBICGSTAB_H
#define NLBICGSTAB_H

#include"NLSolver.h"
#include"descent/BiCGStab.h"

class NLSolverBiCGStab:public NLSolver
{
	public:
		NLSolverBiCGStab(ImplAssembly& assembly, double tol=10e-12, int maxIterations=100, int stps=20);
	protected:
		BiCGStab cg=BiCGStab(Kt,r);
		//ConjugateGradientDescent cg=ConjugateGradientDescent(Assembly.getGlobalMatrix(),r);
	private:
		virtual void setLSolver()override;
};
#endif