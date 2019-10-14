/**
  FILE: ElastoPlasticMaterial.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: ELASTOPLASTICMATERIAL inherits from the super-class material. It is a non-instantiable ABSTRACT class. 
			   Provides PLASTICITY functionalities, principally the calculation of the plastic stresses and strains in
			   the form of material model implementations, however the radialReturn algorithm must be generalized so it 
			   can be found here (hope it works). Some commented code is included as reference avoiding thus going back
			   to the MATERIAL class. Implements a non-public constructor to initialize the Material parameters.
  SOME DETAILS: part of what is inherited from the Super class Material is:
				
				std::string type;
		
				1.-ELASTIC PARAMETERS
				Matrix<double> C;
				double mu;
				double E;
				std::string type;
				
				2.-PLASTIC PARAMETERS
				double yieldStress;
				double plasticModulus;
				
				3.-INHERITED VRITUAL MEHTODS
				virtual void setConstitutiveMatrix()=0;
				virtual void assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)=0;
				
				NON INHERITED VRITUAL MEHTODS
				virtual double yieldFunction()=0;
				virtual void radialReturn()=0;
*/
#ifndef ELASTOPLASTICMATERIAL
#define ELASTOPLASTICMATERIAL

#include"Material.h"
class ElastoPlasticMaterial:public Material
{
	protected:
		ElastoPlasticMaterial(double E, double mu, double yS, double pM);
		
		
		//PLASTIC MODEL FUNCTIONS: these are to be used within assembleTensors function
	private:
		/*\brief Implements elastic predictor-plastic corrector algorithm
		 * The outcome of this algorithm must be the plastic strains and the updating of the stress state
		 param@[in]
		 */
		virtual void radialReturn(Tensor& strains, Tensor& stresses)=0;
		/*!\brief Returns the result of evaluating the yield function on a stress state
		 */
		//virtual double yieldFunction()=0;
	public:
	
		
		
};
#endif