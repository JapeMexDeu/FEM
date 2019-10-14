#include"DescentMethod.h"

DescentMethod::DescentMethod(Matrix<double>& A_, Vector<double>& b_,
					  double tolerance, int maxIterations/*=3000*/,bool verbose/*=false*/)
					  :LSolver(A_,b_,tolerance,maxIterations, verbose)
{
						  
}

