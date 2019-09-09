/**
  FILE: GaussIntegration.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Will receive a class Function to calculate an scalar value, the integration on n=4 points will be taken as unique. Class still needs 
			   development and a smarter way of assigning the guass points, we also dont include the weights since for this case they are always equal to one.
			   
*/

#ifndef GAUSSINTEGRATION_H
#define GAUSSINTEGRATION_H
#include"Function.h"
#include<vector>
#include<cmath>
#include<iostream>
class GaussIntegration
{
	private:
		static double eval_point_x;/*<<Can be set by external classes to evaluate*/
		static double eval_point_y;/*<<Can be set by external classes to evaluate*/
		static std::vector<std::vector<double>> points;/*<<4 pairs of coordinates going from lower left clockwise until lower right*/
	public:
		/*!\brief Calculate the Gauss Integral of received class Function, does onl
		 */
		static double evaluate(Function& func);
		static double evaluate1Point(Function& func);
		static double evaluateAtPoint(Function& func);
		static void showPoints();
		//Setters and getters for customized evaluation and getting the four points
		static void setPoint(double x, double y);
		static double getKsiGP(int i);
		static double getEtaGP(int i);
		//following functions only apply to 2x2 integration rule
		static void setPoint2GPi(int i);
		static void showCurrentPoint();
		
		
};
#endif