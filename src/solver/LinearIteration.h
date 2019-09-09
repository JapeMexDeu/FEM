#ifndef LINEARITERATION_H
#define LINEARITERATION_H

#include"LinearIterator.h"


class LinearIteration
{
	private:
		Vector<double>* b;
		Matrix<double>* A;
		LinearIterator* B;
		
		Vector<double> u;
		
		double tolerance;
		int maxIterations;
		
	private:
		std::vector<double> iterates;
		std::vector<double> error;
	public: 
		std::vector<double> getIterates();
		std::vector<double> getError();
		
	private:
		void calculateCorrector(Vector<double>& r, Vector<double>& c);
		void calculateResiduum(Vector<double>& r);
		
		
	public:
		LinearIteration(Matrix<double>* A, Vector<double>* b, 
						LinearIterator* iterator=nullptr, 
						double tolerance=10e-12, int maxIterations=3000);
		
		//setters and getters
		void setLinearIterator(LinearIterator* b);
		LinearIterator* getLinearIterator();
		void setU(double s);
		Vector<double>& getU();
		void setTolerance(double tolerance);
		double getTolerance();
		void setMaxIterations(int m);
		int getMaxIterations();
		void iterate();
		
};
#endif