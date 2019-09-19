/**
  FILE: Material.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: 
  		   
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include<iostream>
#include<string>
#include"../algebra/Matrix.h"
#include"../algebra/Vector.h"
#include"../tensors/Tensor.h"

class Material
{
	public:
		Material(double E, double mu=0, double yS=0, double pM=0);
		//SETTERS AND GETTERS
	    Matrix<double>& getConstitutiveMatrix();
		virtual std::string getType();
		double getPoisson();
		double getModulus();
		double getYieldStress();
		double getPlasticModulus();
		/*!\brief Receives strain as vector and modifies tensors to 6x1 results
		 */
		virtual void assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)=0;
		friend std::ostream& operator<<(std::ostream &out, Material& mat);
		
		//PLASTIC MODEL FUNCTIONS
	private:
		//These two are pure virtual in elastoplastic model
		//virtual void radialReturn()=0;
		//virtual double yieldFunction()=0;
		
	private:
		virtual void setConstitutiveMatrix()=0;
	
	protected:
		std::string type;
		
		//ELASTIC PARAMETERS
		Matrix<double> C;
		double mu;
		double E;
		
		
		//PLASTIC PARAMETERS
		double yieldStress;
		double plasticModulus;
};
#endif