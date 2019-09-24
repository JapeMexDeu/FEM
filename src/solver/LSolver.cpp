#include"LSolver.h"

LSolver::LSolver(Matrix<double>& A_, Vector<double>& b_,
				 double tolerance, int maxIterations/*=3000*/)
				 :A(A_),b(b_),tolerance(tolerance),maxIterations(maxIterations)
{
	
}

Vector<double>& LSolver::getU()
{
	return u;
} 
std::vector<double> LSolver::getIterates()
{
	return iterates;
}
std::vector<double> LSolver::getError()
{
	return error;
}
void LSolver::setTolerance(double e)
{
	tolerance=e;
}
double LSolver::getTolerance()
{
	return tolerance;
}
void LSolver::setMaxIterations(int m)
{
	maxIterations=m;
}
int LSolver::getMaxIterations()
{
	return maxIterations;
}
std::string LSolver::getType()
{
	return type;
}
/* void LSolver::setMatrix(Matrix<double>& A_)
{
	A=A_;
}
void LSolver::setVector(Vector<double>& b_)
{
	b=b_;
} */