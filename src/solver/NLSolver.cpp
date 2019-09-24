#include"NLSolver.h"

NLSolver::NLSolver(ImplAssembly& assembly,double tol/*=10e-10*/,int iterations/*=100*/, int stps/*=20*/)
				   :Assembly(assembly),numSteps(stps),tolerance(tol),lSolver=nullptr
{
	steps.resize(numSteps);
	//WE ALSO KNOW NOW THE SIZE OF THE PROBLEM...right??
	//RESIZE u_total and r, THEIR VALUE IS ZERO, WHICH IS OK
	r.resize(Assembly.getTotalDOF());
	u_total.resize(Assembly.getTotalDOF());
}

void NLSolver::solve()
{
	//NEED A LOCAL VARIABLE FOR THE CURRENT FORCE INCREMENT
	Vector<double> current_Force (Assembly.getTotalDOF());
	Vector<double> current_iForce(Assembly.getTotalDOF());
	double step_ratio;//for reducing the force
	//HAVE TO DO FOR AS MANY INCREMENTS
	for(int step=1;step<=numSteps;++step)
	{
		step_ratio=(double)step/(double)numSteps;//make sure it is a double
		current_Force=Assembly.getGlobalVector();
		current_Force*=step_ratio;
		r=current_Force-current_iForce;
		//AT SOME POINT WE BEGIN TO ITERATE THE NON LINEAR PROBLEM
		int nlIterations=0;
		while(nlIterations<maxIterations && r.norm()>tolerance)
		{
			//pass matrix and current residuum
			//linear solver goes here
			steps[step-1]+=lSolver.getU();//Implements update
			nlIterations++;
			current_iForce;//Must be Kglobal*steps[step-1];
			r=current_Force-current_iForce;//update of residuum within same load step
		}
		
	
	}
}