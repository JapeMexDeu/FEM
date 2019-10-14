
#ifndef LSOLVER
#define LSOLVER

#include"../algebra/Vector.h"
#include"../algebra/Matrix.h"

#include<string>

class LSolver
{
	protected:
		Matrix<double>& A;/**<Matrix A to invert*/
		Vector<double>& b;/**<Rhs vector*/
		std::vector<double> iterates;
		std::vector<double> error;
		Vector<double> u;/**<Vector of unknowns*/
		int maxIterations;
		double tolerance;
		bool verbose;/**<Control for printing*/
		std::string type;
	public:
		LSolver(Matrix<double>& A, Vector<double>& b, double tolerance, int maxIterations, bool verbose);
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
		void setVerbose(bool type);
	public:
		virtual void solve()=0;
};
#endif