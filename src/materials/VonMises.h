/**
  FILE: VonMises.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: VONMISES is an abstract class interface, NON-INSTANTIABLE, pure virtual. Its implementations must
			   "implement" the assembleTensors method. Most likely it will be derived into Plane stress/strain. 
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
#ifndef VONMISES_H
#define VONMISES_H

#include"ElastoPlasticMaterial.h"

class VonMises:public ElastoPlasticMaterial
{
	public:
		
		VonMises(double E, double mu, double yS, double pM);
		//THIS IS WHY THIS CLASS MUST REMAIN BEING ABSTRACT; HAS TO BE CONVERTED INTO PLANE STRESS OR STRAIN
		//virtual void assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)=0;
	protected:
		/*ALL ARE INHERITED FROM MATERIAL
		std::string type;
		
		//ELASTIC PARAMETERS
		Matrix<double> C;
		double mu;
		double E;
		std::string type;
		
		//PLASTIC PARAMETERS
		double yieldStress;
		double plasticModulus;
		*/
		/*!\brief Implements \f$\sqrt{3J_2}\f$: second invariant of deviatoric stress
		 *
		 */
		double equivalentStress(Tensor& stress);
		/*\brief Implements strain-hardening dK
		 *
		 */
		double hardeningEvolution(Tensor& strain);
		/*!\brief Implements elastic predictor-plastic corrector algorithm
		 */
		//virtual void radialReturn()override;
		/*!\brief Returns the result of evaluating the yield function on a stress state
		 */
		//virtual double yieldFunction()=0
	//ALL THE AMOUNTS FOR THE CALCULATIONS
	protected:
		Vector<double> dF_dSigma=Vector<double>(6);
		double df_dK;
		Matrix<double> Cel=Matrix<double>(6);
	protected:
		void initializeModel();
		void derivativeFSigma();
		
};
#endif