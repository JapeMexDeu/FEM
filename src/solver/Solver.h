#ifndef SOLVER_H
#define SOLVER_H

#include"LinearIteration.h"

class Solver
{
	protected:
		
	private:
		LinearIterator* iterator;
		LinearIteration iteration;
		
	public:
		Solver(Matrix<double>* A, Vector<double>* b, LinearIterator* iterator=nullptr);
		void solve();
		void setLinearIterator(LinearIterator* it);
		Vector<double>& getU();
		LinearIteration& getLinearIteration();
		
	public: 
		std::vector<double> getIterates();
		std::vector<double> getError();
		
};
#endif