/**
  FILE: LinearIterator.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Abstract class, implements the <B>B</B> operator used within a LINEAR ITERATION
			   
*/

#ifndef LINEARITERATOR_H
#define LINEARITERATOR_H
#include"../algebra/Matrix.h"
#include"../algebra/Vector.h"
class LinearIterator
{
	public:
		/*!\brief Implements the calculation of the corrector
		 *The operation to be calculated is:
		 *\f$c=B^{-1}r\f$ 
		 *@param[in] r is received by reference, it is the residuum
		 *@param[in] c is the corrector, modified by reference
		 */
		virtual void inverseMultiply(Vector<double>& r, Vector<double>& c)=0;
		void printLinearIterator()
		{
			std::cout<<"LINEAR ITERATOR: "<<type;
		}
	protected:
		Matrix<double>* A;/**<Pointer to the real matrix, A*/
		std::string type;
};     
#endif