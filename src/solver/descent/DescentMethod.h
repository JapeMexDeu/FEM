#ifndef DESCENTMETHOD_H
#define DESCENTMETHOD_H

#include"../../algebra/Vector.h"
#include"../../algebra/Matrix.h"

class DescentMethod
{
	protected:
		DescentMethod(Matrix<double>& A_, Vector<double>& b_,
					  double tolerance=10e-4, int maxIterations=3000);
	private:
		virtual void setDescentDirection()=0;
		
	protected:
		Matrix<double>& A;
		Vector<double>& b;
		Vector<double> u;
		Vector<double> residuum;
		Vector<double> descentDirection;
		int maxIterations;
		double tolerance;
	//FOR PLOTTING SOME SHIT
	protected:
		std::vector<double> iterates;
		std::vector<double> error;
	//SETTERS AND GETTERS	
	public:
		Vector<double>& getU();
		void setTolerance(double e);
		double getTolerance();
		void setMaxIterations(int m);
		int getMaxIterations();
		std::vector<double> getIterates();
		std::vector<double> getError();
		virtual void solve()=0;
};
#endif