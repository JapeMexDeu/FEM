/**
  FILE: Tensor.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Tensor is an instantiable class which implements basic functionalities like
  		 
*/
#ifndef TENSOR_H
#define TENSOR_H

#include"../algebra/Vector.h"


class Tensor:public Vector<double> 
{
	public:
	
		Tensor(std::size_t sz=6);
	
	//bring from std::vector
	public:
	
		/*!\brief Inherit the initializaiton list constructor from indirect base class
		 */
		using Vector<double>::Vector;
		using Vector<double>::operator=;
		/*!\brief Assignment operator, to receive a BASE CLASS
		 */
		Tensor& operator=(const Vector<double>& V);
		virtual double hydrostaticPressure();
		
	/*
		using std::vector<T>::vector;
		using std::vector<T>::resize;
		using std::vector<T>::size;
		using std::vector<T>::operator[];
		using std::vector<T>::empty;
		using std::vector<T>::begin;
    	using std::vector<T>::end;
    	using std::vector<T>::clear;
	*/
	public:
		//virtual double secondInvariant()=0;
		
		//OPERATOR OVERLOADS
		/*
		Tensor operator+(const Tensor& s);
		Tensor& operator+=(const Tensor& s);
		Tensor operator-(const Tensor& s);
		Tensor& operator-+=(const Tensor& s);
		Tensor& operator*(double scalar);
		Tensor& operator=(double value);
		*/
};
#endif