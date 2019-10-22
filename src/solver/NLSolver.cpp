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
	Vector<double> current_Force (Assembly.getTotalDOF());//External force
	Vector<double> current_iForce(Assembly.getTotalDOF());//Internal force
	double step_ratio;//for setting the force increments
	current_iForce=0;
	//HAVE TO DO FOR AS MANY INCREMENTS numSteps (LOAD STEPS)
	for(int step=1;step<=numSteps;++step)
	{
		//current_iForce;//we dont want the previous value in every new load step
		std::cout<<"LOAD STEP "<<"NONLINEAR ITERATION "<<" RESIDUUM NORM"<<"\n";
		std::cout<<"        "<<step;
		step_ratio=(double)step/(double)numSteps;//make sure it is a double
		current_Force=Assembly.getGlobalVector();
		current_Force*=step_ratio;
		//ordinates.push_back(current_Force.norm());
		r=current_Force-current_iForce;
		//AT SOME POINT WE BEGIN TO ITERATE THE NON LINEAR PROBLEM
		int nlIterations=0;
		std::cout<<"                "<<nlIterations<<"            "<<r.norm()<<"\n";
		while(nlIterations<maxIterations && r.norm()>tolerance)
		{
			//This would represent the  FULL newton raphson
			//assembly.assembleGlobalMatrix();
			
			lSolver->solve();
			steps[step-1]+=lSolver->getU();//Implements update, ,sum increment
			//AFTER ITERATION WE UPDATE OUR WHOLE PROBLEM
			//Assembly.localSolutionVectorAssemblyRoutine(steps[step-1]);//This will find the plastic behavior
			Assembly.matrixAssemblyRoutine();
			
			
			current_iForce=Assembly.getGlobalMatrix()*steps[step-1];//update of internal force vector
			nlIterations++;
			
			r=current_Force-current_iForce;//update of residuum within same load step
			std::cout<<"        "<<step<<"                "<<nlIterations<<"            "<<r.norm()<<"\n";
		}
		//We have to disassemble the global displacement vector, and then calculate stresses and strains
		//Assembly.localSolutionVectorAssemblyRoutine(steps[step-1]);
		std::cout<<"\n*********THE RESULTS FOR THIS LOAD STEP**********\n";
		Assembly.printMesh();
		u_total=steps[step-1];
		//here the K matrix would be generated again...since its a reference it will change value within the algorithm
		//assembly.assembleGlobalMatrix();
		std::cout<<"\nIN STEP: "<< step<<" THE DISPLACEMENT SO FAR: "<<steps[step-1]<<"\n";
		if(step<numSteps)
			steps[step]=steps[step-1];
		//abscissae.push_back(steps[step-1].norm());
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

Vector<double>& NLSolver::getAbscissae()
{
	return abscissae;
}
Vector<double>& NLSolver::getOrdinates()
{
	return ordinates;
}