#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H
#include"DescentMethod.h"
class GradientDescent:public DescentMethod
{
	public:
		GradientDescent(Matrix<double>& A_, Vector<double>& b_,
						double tolerance=10e-3, int maxIterations=3000, bool verbose=false);
		virtual void solve()override;
		
	private:
		virtual void setDescentDirection()override;
};

#endif