#include"ConjugateGradientDescent.h"

ConjugateGradientDescent::ConjugateGradientDescent(Matrix<double>& A_, Vector<double>& b_,
												   double tolerance, int maxIterations):DescentMethod(A_,b_,tolerance,maxIterations)
{
	residuum.resize(b_.size());
	u.resize(b_.size());	
	type="CONJUGATE GRADIENT DESCENT\n";
}
void ConjugateGradientDescent::solve()
{
	std::cout<<"\nBEGIN: LINEAR SOLVER: GRADIENT DESCENT METHOD\n";
		
	residuum=b-A*u;
	Vector<double> z(residuum.size());
	int count=1;
	double num, den, alpha, norm, num2;
	norm=residuum.norm();
	double max=norm;
	setDescentDirection();
	std::cout<<"LINEAR ITERATION "<<" RESIDUUM NORM\n";
	while(residuum.norm()>tolerance && count<maxIterations)
	{
		std::cout<<"        "<<count<<"                "<<residuum.norm()<<"\n";
		z=A*descentDirection;
		
		error.push_back(norm/max);
		iterates.push_back(count);
		
		num=residuum*descentDirection;
		den=z*descentDirection;
		alpha=num/den;
		
		//u=u-alpha*descentDirection;
		u=u+descentDirection*alpha;
		residuum=residuum-z*alpha;
		
		//update descent direction
		
		num2=residuum*z;
		alpha=num2/den;
		descentDirection=residuum-descentDirection*alpha;
		
		norm=residuum.norm();
		
		count++;
	}
	std::cout<<"        "<<count<<"                "<<residuum.norm()<<"\n";
	error.push_back(norm/max);
	iterates.push_back(count);
	std::cout<<"AFTER "<<count<<" ITERATIONS\n";
	std::cout<<"SOLUTION VECTOR IS: \n";
	std::cout<<u;
	std::cout<<"END: DESCENT METHOD\n";
}
void ConjugateGradientDescent::setDescentDirection()
{
	descentDirection=residuum;
}