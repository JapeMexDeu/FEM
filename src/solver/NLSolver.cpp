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
	Plotter plotter(nullptr, "linespoints");
	Plotter splotter(nullptr, "linespoints");
	plotter.setPlotter("D","F",&Assembly,0,2);
	splotter.setSPlotter("D","F",&Assembly,0,1);
	std::cout<<"\nBEGIN: NON LINEAR SOLVE ROUTINE\n";
	//NEED A LOCAL VARIABLE FOR THE CURRENT FORCE INCREMENT
	Vector<double> current_Force (Assembly.getTotalDOF());//External force
	Vector<double> current_iForce(Assembly.getTotalDOF());//Internal force
	Vector<double> temp(Assembly.getTotalDOF());//Internal force
	double tl=10e-3;
	double step_ratio;//for setting the force increments
	current_iForce=0;
	Vector<double> firstInternal;
	//HAVE TO DO FOR AS MANY INCREMENTS numSteps (LOAD STEPS)
	for(int step=1;step<=numSteps;++step)
	{
		
		std::cout<<"****LOAD STEP "<<"NONLINEAR ITERATION "<<" RESIDUUM NORM"<<"	  RELATIVE ERROR"<<
		"   FORCE CRITERION****\n";
		std::cout<<"        "<<step;
		step_ratio=(double)step/(double)numSteps;//make sure it is a double
		current_Force=Assembly.getGlobalVector();
		current_Force*=step_ratio;
		
		
		r=current_Force-current_iForce;
		//AT SOME POINT WE BEGIN TO ITERATE THE NON LINEAR PROBLEM
		int nlIterations=0;
		//std::cout<<"                "<<nlIterations<<"            "<<r.norm()<<"	"<<r.norm()/current_Force.norm()<<"\n";
		while(nlIterations<maxIterations && r.norm()>tolerance)
		{
			//This would represent the  FULL newton raphson
			Assembly.matrixAssemblyRoutine();
			
			lSolver->solve();
			steps[step-1]+=lSolver->getU();//Implements update, ,sum increment
			nlIterations++;
			//cout<<steps[step-1];
			//steps[step-1]*=ls;
			//AFTER ITERATION WE UPDATE OUR WHOLE PROBLEM
			Assembly.localSolutionVectorAssemblyRoutine(steps[step-1]);//This will find the plastic behavior
			splotter.updateElementData();
			
			Assembly.matrixAssemblyRoutine();
			current_iForce=Assembly.getGlobalMatrix()*steps[step-1];//update of internal force vector
			std::cout<<"GLOBAL INTERNAL FORCE; CALCULATED:"<<current_iForce;
			std::cout<<"NORM IS: "<<(current_Force-current_iForce).norm()<<"\n";
			Assembly.globalInternalForceAssembly();
			std::cout<<"GLOBAL INTERNAL FORCE VECTOR ASSEMBLED:";
			std::cout<<Assembly.getGlobalInternalForce();
			std::cout<<"NORM IS: "<<(current_Force-Assembly.getGlobalInternalForce()).norm()<<"\n";
			//current_iForce=Assembly.getGlobalInternalForce();
			
			//********************************************
			if(nlIterations==1)
				firstInternal=current_Force-current_iForce;
			//********************************************
			
			r=current_Force-current_iForce;//update of residuum within same load step, to see CONVERGENCE
			std::cout<<"        "<<step<<"                "<<nlIterations<<"            "<<r.norm()<<"	";
			std::cout<<r.norm()/current_Force.norm()<<"   "<<firstInternal.norm()*tl<<"\n";
			
			std::cout<<"\nVALUE IS: "<<(current_Force-Assembly.getGlobalInternalForce()).norm()<<"\n";
			plotter.updateNodeData();
		}

		
		
		std::cout<<"\n*******IN STEP: "<< step<<" THE DISPLACEMENT SO FAR: "<<steps[step-1]<<"********\n";
		if(step<numSteps)
			steps[step]=steps[step-1];
		
	}
	
	plotter.printData();
	plotter.plot();
	splotter.plot();
	sleep(50);
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