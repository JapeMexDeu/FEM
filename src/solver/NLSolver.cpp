#include"NLSolver.h"

NLSolver::NLSolver(ImplAssembly& assembly,double tol/*=10e-10*/,int iterations/*=100*/, int stps/*=20*/)
				   :Assembly(assembly),numSteps(stps),tolerance(tol), maxIterations(iterations),
				    Kt(Assembly.getGlobalMatrix()), lSolver(nullptr)
{
	steps.resize(numSteps);
	//WE ALSO KNOW NOW THE SIZE OF THE PROBLEM...right??
	//RESIZE u_total and r, THEIR VALUE IS ZERO, WHICH IS OK
	for(int i=0;i<numSteps;++i)
	{
		steps[i].resize(Assembly.getTotalDOF());
	}
	r.resize(Assembly.getTotalDOF());
	u_total.resize(Assembly.getTotalDOF());
}

void NLSolver::solve()
{
	std::cout<<"\nBEGIN: NON LINEAR SOLVE ROUTINE\n";
	//NEED A LOCAL VARIABLE FOR THE CURRENT FORCE INCREMENT
	Vector<double> current_Force (Assembly.getTotalDOF());
	Vector<double> current_iForce(Assembly.getTotalDOF());
	double step_ratio;//for reducing the force
	//HAVE TO DO FOR AS MANY INCREMENTS
	//std::cout<<"LOAD STEP "<<"NONLINEAR ITERATION "<<" RESIDUUM NORM"<<"\n";
	for(int step=1;step<=numSteps;++step)
	{
		std::cout<<"LOAD STEP "<<"NONLINEAR ITERATION "<<" RESIDUUM NORM"<<"\n";
		std::cout<<"        "<<step;
		step_ratio=(double)step/(double)numSteps;//make sure it is a double
		current_Force=Assembly.getGlobalVector();
		current_Force*=step_ratio;
		r=current_Force-current_iForce;
		//AT SOME POINT WE BEGIN TO ITERATE THE NON LINEAR PROBLEM
		int nlIterations=0;
		std::cout<<"                "<<nlIterations<<"            "<<r.norm()<<"\n";
		while(nlIterations<maxIterations && r.norm()>tolerance)
		{
			//pass matrix and current residuum
			//linear solver goes here
			lSolver->solve();
			steps[step-1]+=lSolver->getU();//Implements update
			nlIterations++;
			current_iForce=Assembly.getGlobalMatrix()*steps[step-1];//update of internal force vector
			r=current_Force-current_iForce;//update of residuum within same load step
			std::cout<<"        "<<step<<"                "<<nlIterations<<"            "<<r.norm()<<"\n";
		}
		u_total=steps[step-1];
		//here the K matrix would be generated again...since its a reference it will change value here as well
		//assembleGlobalMatrix();
		std::cout<<"\nIN STEP: "<< step<<" THE DISPLACEMENT SO FAR: "<<steps[step-1]<<"\n";
		if(step<numSteps)
			steps[step]=u_total;
		//steps[step]+=steps[step]+steps[step-1];
	}
}
void NLSolver::printNLSolver()
{
	std::cout<<"\nBEGIN: PRINT NON-LINEAR SOLVER\n";
	std::cout<<"	IMPLEMENTS NEWTON RAPHSON FOR A LOAD INCREMENTAL APPROACH\n";
	std::cout<<"	NL SOLVER PROPERTIES: \n";
	std::cout<<"	MAX NUMBER OF ITERATIONS: "<<maxIterations<<" TOLERANCE: "
			 <<tolerance<<" STEPS: "<<numSteps<<"\n";
	std::cout<<"		LINEAR SOLVER IS: "<<lSolver->getType();
	std::cout<<"		LINEAR SOLVER PROPERTIES: \n";
	std::cout<<"		MAX NUMBER OF ITERATIONS: "<<lSolver->getMaxIterations()<<" TOLERANCE: "
			 <<lSolver->getTolerance()<<"\n";
	std::cout<<"END: PRINT NON-LINEAR SOLVER\n";
}