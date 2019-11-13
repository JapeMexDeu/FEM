#ifndef BICGSTAB_H
#define BICGSTAB_H
#include"DescentMethod.h"
class BiCGStab:public DescentMethod
{
	public:
		BiCGStab(Matrix<double>& A_, Vector<double>& b_,
				 double tolerance=10e-12, int maxIterations=3000, bool verbose=false);
		virtual void solve()override;
		
	private:
		virtual void setDescentDirection()override;
		void setMethod();
	private:
	//private members of the method
		Vector<double> rhat;
		Vector<double> v;/**<For Ap cached calculation*/
		Vector<double> t;/**<For As cached calculation*/
		Vector<double> s;/**<used for calculation of new residual defined as r-alphaAp*/
		Vector<double> p;/**<Descent or Search direction*/
		
		double w;/**<Stabilization parameter*/
		double betha;/**<Scalar*/
		double alpha;/**<Scalar*/
		double ro;
		
		int size;
};

#endif