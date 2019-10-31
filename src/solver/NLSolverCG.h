#ifndef NLSOLVERCG_H
#define NLSOLVERCG_H

#include"NLSolver.h"
#include"descent/ConjugateGradientDescent.h"

class NLSolverCG:public NLSolver
{
	public:
		NLSolverCG(ImplAssembly& assembly, double tol=10e-10, int maxIterations=100, int stps=20);
	protected:
		ConjugateGradientDescent cg=ConjugateGradientDescent(Kt,r);
		//ConjugateGradientDescent cg=ConjugateGradientDescent(Assembly.getGlobalMatrix(),r);
	private:
		virtual void setLSolver()override;
};
#endif