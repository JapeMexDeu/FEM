/**
  FILE: Force.h
  
  AUTHOR: Jose P Escobar
  
  DESCRIPTION: This class describes a POINT NODE, in order to expand this into traction and body forces, we would have to have a proper geometrical 
			   description

		   
*/

#ifndef FORCE_H
#define FORCE_H

#include"Vector.h"

class Force
{
	public:
		Force(double f1=0, double f2=0, double f3=0);
		double magnitude();
		//setters and getters
		void setComponent(double f, int i);
		void setComponent1(double f);
		void setComponent2(double f);
		void setComponent3(double f);
		double getComponent(int i);
		double getComponent1();
		double getComponent2();
		double getComponent3();
		Vector<double>& getForce();
		
	private:
		Vector<double> force=Vector<double>(3);
};
#endif