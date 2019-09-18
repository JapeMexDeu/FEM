#include"DescentMethod.h"

DescentMethod::DescentMethod(Matrix<double>& A_, Vector<double>& b_,
					  double tolerance, int maxIterations/*=3000*/):A(A_),b(b_),tolerance(tolerance),maxIterations(maxIterations)
{
						  
}

Vector<double>& DescentMethod::getU()
{
	return u;
}
void DescentMethod::setTolerance(double e)
{
	tolerance=e;
}
double DescentMethod::getTolerance()
{
	return tolerance;
}
void DescentMethod::setMaxIterations(int m)
{
	maxIterations=m;
}
int DescentMethod::getMaxIterations()
{
	return maxIterations;
}
std::vector<double> DescentMethod::getIterates()
{
	return iterates;
}
std::vector<double> DescentMethod::getError()
{
	return error;
}
