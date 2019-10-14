#ifndef CONJUGATEGRADIENTDESCENT_H
#define CONJUGATEGRADIENTDESCENT_H
#include"DescentMethod.h"
class ConjugateGradientDescent:public DescentMethod
{
	public:
		ConjugateGradientDescent(Matrix<double>& A_, Vector<double>& b_,
						double tolerance=10e-13, int maxIterations=3000, bool verbose=false);
		virtual void solve()override;
		
	private:
		virtual void setDescentDirection()override;
};

#endif