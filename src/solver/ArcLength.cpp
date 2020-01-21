#include"ArcLength.h"
using std::cout;
ArcLength::ArcLength(ImplAssembly& assembly, double ds, int maxSteps,
				     double tol/*=10e-10*/, int maxIterations/*=10*/)
					 :Assembly(assembly), Kt(Assembly.getGlobalMatrix()), maxSteps(maxSteps),
					 tolerance(tol), maxIterations(maxIterations), ds(ds), dofs(Assembly.getTotalDOF())
{
	initializeSolver();
	initialValues();
	debug=true;
	verbose=true;
}


void ArcLength::solve()
{
	double error;
	//local copies
	Vector<double> Lfhat(dofs);
	Vector<double> Lu(dofs);
	Vector<double> Lda(dofs);
	
	//1.- the load steps begin here
	while(Lambda<maxLambda && steps<maxSteps)
	{
		steps++;
		Lfhat=fext;
		Lu=u_total;
		Lda=da;
		error=1;
		lIts=0;
		if(debug)
		{
			cout<<"STEP: "<<steps<<"\n";
			cout<<"TOTAL VALUES: "<<Lu;
			cout<<"INCREMENT VALUES: "<<Lda;
			cout<<"LAMBDA: "<<Lambda<<"\n";
		}
		//2.- PREDICTOR STEP
		Vector<double> da1(dofs);//local storage of predicted solution
		double dLambda1;//local storage of predicted lambda
		//2.1.1- IF FIRST LOAD STEP
		if(steps==1)
		{
			dLambda1=Lambda;
			Assembly.matrixAssemblyRoutine();
			Lfhat*=Lambda;
			BiCGStab cg=BiCGStab(Kt,Lfhat);
			cg.solve();
			da1=cg.getU();
			if(debug)
			{
				cout<<"FIRST LOAD STEP\n";
				cout<<da1;
			}
			
		}
		//2.1.2- IF NOT FIRST LOAD STEP
		else
		{
			da1=uprev;
			dLambda1=lambdaprev;
		}
		//2.2 UPDATE TOTAL AND INCREMENTAL LOCAL VALUES
		Lu+=da1;
		Lda=da1;
		dLambda=dLambda1;
		if(debug)
		{
			cout<<"AFTER PREDICTOR\n";
			cout<<"VALUES: "<<Lu;
			cout<<"LAMBDA: "<<dLambda<<"\n";
		}
		//END OF PREDICTOR STEP
		
		//3  CONVERGENCE CHECK BY CALCULATING NEW STIFFNES MATRIX AND NEW RESIDUAL
		//3.1 ASSIGN NEW SOLUTION TO NODES	
		Assembly.localSolutionVectorAssemblyRoutine(Lu);
		Assembly.globalInternalForceAssembly();
		fint=Assembly.getGlobalInternalForce();
		r=(Lfhat*Lambda)-fint;
		if(debug)
		{
			cout<<"THE EXTERNAL FORCE VECTOR IS: "<<Lfhat*Lambda;
			cout<<"RESIDUAL BEFORE ITERATION START\n";
			cout<<r;
			cout<<"RESIDUAL NORM BEFORE ITERATION START\n";
			cout<<r.norm()<<"\n";
			cout<<"INTERNAL FORCE VECTOR IS: "<<fint;
			
		}
		//ADDITION: UPDATE STIFFNESS MATRIX
		Assembly.matrixAssemblyRoutine();
		//4 BEGIN OF ITERATIONS
		//4.1 CHECK RESIDUUM ERROR
		while(error>tolerance)
		{
			lIts++;
			//1.-SOLVE FOR THE TWO COMPONENTS OF increment of values
			BiCGStab sd1=BiCGStab(Kt,Lfhat);
			sd1.solve();
			daI=sd1.getU();
			BiCGStab sd2=BiCGStab(Kt,r);
			sd2.solve();
			daII=sd2.getU();
			
			//2.- SOLVE FOR dLambda
			//use last converged step...predictor value
			dLambda=
			
		}
		
	}
}

void ArcLength::printArcLength()
{
	std::cout<<"\nARC LENGTH METHOD WITH CRISFIELD APPROACH\n";
	std::cout<<"THE PARAMETERS ARE: \n";
	std::cout<<"PATH LENGTH INCREMENT IS: "<<ds<<"\n";
	std::cout<<"TOLERANCE IS: "<<tolerance<<"\n";
	std::cout<<"THE MAX. NUMBER OF LOAD STEPS: "<<maxSteps<<"\n";
	std::cout<<"THE MAX. NUMBER OF ITERATIONS PER STEP IS: "<<maxIterations<<std::endl;
	std::cout<<"AFTER INITIALIZATION THE ASSIGNED VALUES ARE: \n";
	std::cout<<"THE NORMALIZED EXTERNAL FORCE VECTOR IS: "<<fext<<"\n";
	std::cout<<"THE NORM OF THE EXTERNAL FORCE IS: "<<normfext<<"\n";
}
//PRIVATE METHODS THAT NEED NOT BE SEEN
void ArcLength::initializeSolver()
{
	//Resize all what needs resizing
	uprev.resize(dofs);
	fint.resize(dofs);
	r.resize(dofs);
	u_total.resize(dofs);
	daI.resize(dofs);
	daII.resize(dofs);
	fext=Assembly.getGlobalVector();
	normfext=fext.norm();
	fext*=1/normfext;
	if(fext.norm()!=1.0)
	{
		std::cout<<"\nInitial error, cannot normalize\n";
		std::cout<<fext.norm()<<"\n";
	}
	Lambda=1;
}
void ArcLength::initialValues()
{
	lambdaprev=0;
	dLambda=0;
	lIts=0;
	steps=0;
	r=0;
	u_total=0;
	daI=0;
	daII=0;
	da=0;
}