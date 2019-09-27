
#ifndef LSOLVER
#define LSOLVER

#include"../algebra/Vector.h"
#include"../algebra/Matrix.h"

#include<string>

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
		std::string type;
	public:
		LSolver(Matrix<double>& A, Vector<double>& b, double tolerance, int maxIterations);
		Vector<double>& getU();
		std::vector<double>& getIterates();
		std::vector<double>& getError();
		//void setMatrix(Matrix<double>& A_);
		//void setVector(Vector<double>& b_);
		void setTolerance(double e);
		double getTolerance();
		void setMaxIterations(int m);
		int getMaxIterations();
		std::string getType();
	public:
		virtual void solve()=0;
};
#endif