#include"DescentMethod.h"

DescentMethod::DescentMethod(Matrix<double>& A_, Vector<double>& b_,
					  double tolerance, int maxIterations/*=3000*/)
					  :LSolver(A_,b_,tolerance,maxIterations)
{
						  
}

