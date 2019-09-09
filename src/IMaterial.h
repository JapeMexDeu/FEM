/**
  FILE: IMaterial.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Interface for material behavior. IMATERIAL_H is a "superclass" for grouping the functionalities that the Material class 
			   should provide. It is NON-INTANTIABLE. Provides no implementation. 
  		   
*/

#ifndef IMATERIAL_H
#define IMATERIAL_H
#include<iostream>
#include<string>
#include"Matrix.h"
#include"vector.h"

class IMaterial
{
	public:
	virtual Matrix<double>& getConstitutiveMatrix()=0;
};
#endif