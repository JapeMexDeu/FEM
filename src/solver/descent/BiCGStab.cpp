#include"BiCGStab.h"

BiCGStab::BiCGStab(Matrix<double>& A_, Vector<double>& b_,
				   double tolerance/*=10e-12*/, int maxIterations/*=3000*/, 
				   bool verbose/*=false*/):DescentMethod(A_,b_,tolerance,maxIterations, verbose)
{
	setMethod();	   
}
void BiCGStab::setMethod()
{
	size=b.size();
	alpha=1;
	betha=1;
	ro=1;
	w=1;
	v.resize(size);
	t.resize(size);
	s.resize(size);
	p.resize(size);
	u.resize(size);
}
void BiCGStab::setDescentDirection()
{
	
}
void BiCGStab::solve()
{
	u=0;
	Vector<double> u_old;
	Vector<double> r_old;
	Vector<double> p_old;
	u_old.resize(size);
	r_old.resize(size);
	p_old.resize(size);
	//cpmpute residuum
	residuum=b-A*u;
	//*******
	double norm;
	norm=residuum.norm();
	double max=norm;
	//*******
	
	rhat=residuum;
	p=residuum;
	int count =0;
	if(verbose)
		std::cout<<"\nBEGIN: LINEAR SOLVER: BICONJUGATE GRADIENT STABILIZED METHOD\n";
	if(verbose)
		std::cout<<"LINEAR ITERATION "<<" RESIDUUM NORM\n";
	while(count<maxIterations && residuum.norm()>tolerance)
	{
		if(verbose)
			std::cout<<"        "<<count<<"                "<<residuum.norm()<<"\n";
		//*******
		error.push_back(norm/max);
		iterates.push_back(count);
		//*******
		ro=residuum*rhat;
		v=A*p;
		alpha=ro/(v*rhat);
		s=residuum-(v*alpha);
		t=A*s;
		w=(t*s)/(t*t);
		u=u_old+p*alpha+s*w;
		//r_old=residuum;
		residuum=s-t*w;
		norm=residuum.norm();
		betha=(alpha/w)*(residuum*rhat)/ro;
		p_old=p;
		p=residuum+(p_old-v*w)*betha;
		u_old=u;
		count++;
	}
	if(verbose)
			std::cout<<"        "<<count<<"                "<<residuum.norm()<<"\n";
		
	//*******
	error.push_back(norm/max);
	iterates.push_back(count);
	//*******
	
	if(verbose)
	{
		std::cout<<"AFTER "<<count<<" ITERATIONS\n";
		std::cout<<"SOLUTION VECTOR IS: \n";
		std::cout<<u;
		std::cout<<"END: DESCENT METHOD\n";
	}
	if(residuum.norm()>tolerance)
		std::cout<<"\nLINEAR PROBLEM DID NOT CONVERGE: "<<residuum.norm()<<"\n";
}