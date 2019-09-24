
#ifndef DESCENTMETHOD_H
#define DESCENTMETHOD_H


#include"../LSolver.h"
class DescentMethod:public LSolver
{
	protected:
		DescentMethod(Matrix<double>& A_, Vector<double>& b_,
					  double tolerance=10e-4, int maxIterations=3000);
	private:
		virtual void setDescentDirection()=0;
		
	protected:
	//INHERITED FROM LSOLVER
/* 		Matrix<double>& A;
		Vector<double>& b;
		Vector<double> u;
		int maxIterations;
		double tolerance; 
		//FOR PLOTTING SOME SHIT
		std::vector<double> iterates;
		std::vector<double> error;
*/
	protected:
	//PROPER OF THIS CLASS
		Vector<double> residuum;
		Vector<double> descentDirection;
		
	//FOR PLOTTING SOME SHIT
		
	//SETTERS AND GETTERS	
	public:
	//INHERITED FROM LSOLVER
/* 		Vector<double>& getU();
		void setTolerance(double e);
		double getTolerance();
		void setMaxIterations(int m);
		int getMaxIterations();
		std::vector<double> getIterates();
		std::vector<double> getError(); */
		//virtual void solve()=0;
};
#endif