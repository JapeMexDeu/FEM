#ifndef LINEARITERATION_H
#define LINEARITERATION_H

#include"LinearIterator.h"


class LinearIteration
{
	private:
		Vector<double>& b;
		Matrix<double>& A;
		LinearIterator* B;
		
		Vector<double> u;
		
		double tolerance;
		int maxIterations;
		
		
	private:
		void calculateCorrector(Vector<double>& r, Vector<double>& c);
		void calculateResiduum(Vector<double>& r);
		
		
	public:
		LinearIteration(Matrix<double>& A, Vector<double>& b, 
						LinearIterator* iterator=nullptr, 
						double tolerance=10e-3, int maxIterations=3000);
		
		//setters and getters
		
		void iterate();
		
};
#endif