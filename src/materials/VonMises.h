/**
  FILE: VonMises.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: VONMISES is an abstract class interface, NON-INSTANTIABLE, pure virtual. Its implementations must
			   "implement" the assembleTensors method. Most likely it will be derived into Plane stress/strain. In this class
			   we are only implementing isotropic Hardening.
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
				
				3.-INHERITED VIRTUAL MEHTODS
				virtual void setConstitutiveMatrix()=0;
				virtual void assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)=0;
				
				INHERITED VRITUAL MEHTODS FROM ElastoPlasticMaterial.h
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
		/*\brief Implements strain-hardening dK, must receive the plastic strain
		 *
		 */
		double plasticWork(Tensor& strain_ep);
		/*!\brief Implements elastic predictor-plastic corrector algorithm
		 *DESCRIPTION: 
		 *Input stresses are already the trial stresses, the strains are needed for the plastic-work scalar
		 */
		virtual void radialReturn(Tensor& strains, Tensor& stresses)override;
		/*!\brief Returns the result of evaluating the yield function on a stress state
		 */
		virtual double yieldFunction(Tensor& stress, Tensor& strain_ep);
	//ALL THE AMOUNTS FOR THE CALCULATIONS
	protected:
		Vector<double> dF_dSigma=Vector<double>(6);/**<Associative plastic flow direction, normal to yield surface*/
		double df_dK;/**<Derivative of yield function wrt K, in isotropic hardening it is equal to plasticModulus (H)*/
		double dLambda;/**<Plastic multiplier for plastic strain increment*/
		double dK;/**<Delta lambda hardening increment dependent on plastic work*/
		double eqStrain;/**<Equivalent Strain, we have to keep track of it to avoid starting from zero....maybe*/
		Matrix<double> Cel=Matrix<double>(6);/**<Elastic Constitutive Matrix in 6x6 form*/
	protected:
		void initializeModel();
		void derivativeFSigma(Tensor& stress);
		double updateYieldStress();
		void equationsSystem(Tensor& stress);
};
#endif