/**
  FILE: Material.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: This class is a NON INSTANTIABLE pure abstract class which is used for implementing elastic or 
			   elastoplastic models. 
  		   
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
		/*!\brief Returns Consitutive matrix
		 */
	    Matrix<double>& getConstitutiveMatrix();
		/*!\brief Returns type of material for INSTANTIABLE class
		 */
		virtual std::string getType();
		double getPoisson();
		double getModulus();
		double getYieldStress();
		double getPlasticModulus();
		/*!\brief Receives strain as vector and modifies tensors to 6x1 results
		 *DESCRIPTION: modifies strains and stresses tensors inside the element through reference. The stress is 
					   calculated inside this function as a temporary Vector object then it is resized to a correct 6x1.
					   The strains exist already and are just redistributed but not calculated. See ELEMENT.H method
					   COMPUTETENSORIALRESULTS for more information.
		 *@param[in] v element local strains vector
		 *@param[out] strains 6x1 strain tensor in Voigt notation calculated through \f$&epsilon;=B*v\f$
		 *@param[out] stresses 6x1 stress tensor in Voigt notation calculated through \f$&sigma;=C*&epsilon;\f$
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
		Matrix<double> C;/**<Constitutive matrix for \f$ &sigma;=C&epsilon;\f$*/
		Matrix<double> Cel;/**<Constitutive Matrix for Elastic behavior*/
		double mu;/**<Poisson's ratio */
		double E;/**<Young's modulus*/
		
		
		//PLASTIC PARAMETERS
		Tensor plasticStrain;
		double yieldStress;/**<ONLY PLASTIC: stress before plastic behavior &sigma;_y*/
		double plasticModulus;/**<ONLY LINEAR ISOTROPIC HARDENING: slope of yield stress increase*/
};
#endif