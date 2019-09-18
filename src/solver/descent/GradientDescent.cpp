#include"GradientDescent.h"

GradientDescent::GradientDescent(Matrix<double>& A_, Vector<double>& b_,
								 double tolerance, int maxIterations):DescentMethod(A_,b_,tolerance,maxIterations)
{
	residuum.resize(b_.size());
	u.resize(b_.size());	
	
}
void GradientDescent::solve()
{
	std::cout<<"BEGIN: GRADIENT DESCENT METHOD\n";

	residuum=b-A*u;
	
	int count=1;
	double num, den, alpha, norm;
	norm=residuum.norm();
	double max=norm;
	while(residuum.norm()>tolerance && count<maxIterations)
	{
		
		error.push_back(norm/max);
		iterates.push_back(count);
		setDescentDirection();
		num=residuum*descentDirection;
		den=(A*descentDirection)*descentDirection;
		alpha=num/den;
		descentDirection*=alpha;
		u+=descentDirection;
		residuum=residuum-A*descentDirection;
		norm=residuum.norm();
		
		count++;
	}
	error.push_back(norm/max);
	iterates.push_back(count);
	std::cout<<"AFTER "<<iterates.size()<<" ITERATIONS\n";
	std::cout<<"SOLUTION VECTOR IS: \n";
	std::cout<<u;
	std::cout<<"END: DESCENT METHOD\n";
}
void GradientDescent::setDescentDirection()
{
	descentDirection=residuum;
}