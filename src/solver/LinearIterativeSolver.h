
#ifndef LINEARITERATIVESOLVER_H
#define LINEARITERATIVESOLVER_H

#include"LinearIterator.h"
#include"LSolver.h"
class LinearIterativeSolver: public LSolver
{
		
	private:
		LinearIterator* iterator;/**<Represents the B matrix*/
		
		
	public:
		LinearIterativeSolver(Matrix<double>& A, Vector<double>& b, 
							  double tolerance=10e-4, int maxIterations=2000, bool verbose=false, LinearIterator* iterator=nullptr);
		virtual void solve()override;
		void setLinearIterator(LinearIterator* it);
	public:
	
	private:
		void calculateCorrector(Vector<double>& r, Vector<double>& c);
		void calculateResiduum(Vector<double>& r);
	
		
};
#endif