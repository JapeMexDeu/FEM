/**
  FILE: Jacobi.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: instantiation of abstract class LINEAR ITERATOR. Implements the method <TT> inverseMultiply</TT> for a Jacobi scheme. The formula is:
  \f[
		B_{Jacobi}=D 
  \f]
			   
*/
#include"LinearIterator.h"
#ifndef JACOBI_H
#define JACOBI_H

class Jacobi:public LinearIterator
{
	public: 
		Jacobi(Matrix<double>* A);
		/*!\brief Implements the calculation of the corrector.
		 *\f$c=\frac{1}{D_{ii}}r_{i}\f$
		 */
		virtual void inverseMultiply(Vector<double>& r, Vector<double>& c)override;
	
};
#endif