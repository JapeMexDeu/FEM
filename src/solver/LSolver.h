
#ifndef LSOLVER
#define LSOLVER

#include"../algebra/Vector.h"
#include"../algebra/Matrix.h"


class LSolver
{
	protected:
		Matrix<double>& A;
		Vector<double>& b;
		std::vector<double> iterates;
		std::vector<double> error;
		Vector<double> u;
		int maxIterations;
		double tolerance;
		
	public:
		LSolver(Matrix<double>& A, Vector<double>& b, double tolerance, int maxIterations);
		Vector<double>& getU();
		std::vector<double> getIterates();
		std::vector<double> getError();
		void setTolerance(double e);
		double getTolerance();
		void setMaxIterations(int m);
		int getMaxIterations();
		
	public:
		virtual void solve()=0;
};
#endif