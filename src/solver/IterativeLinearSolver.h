
#ifndef LINEARITERATIVESOLVER_H
#define LINEARITERATIVESOLVER_H

#include"LinearIterator.h"

class LinearIterativeSolver: public LSolver
{
		
	private:
		LinearIterator* iterator;
		
		
	public:
		Solver(Matrix<double>* A, Vector<double>* b, LinearIterator* iterator=nullptr);
		virtual void solve()override;
		void setLinearIterator(LinearIterator* it);
	public:
	
	private:
		void calculateCorrector(Vector<double>& r, Vector<double>& c);
		void calculateResiduum(Vector<double>& r);
	
		
};
#endif