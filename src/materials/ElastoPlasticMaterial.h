#ifndef ELASTOPLASTICMATERIAL
#define ELASTOPLASTICMATERIAL

#include"Material.h"
class ElastoPlasticMaterial:public Material
{
	public:
		ElastoPlasticMaterial(double E, double mu=0, double yS=0, double pM=0);
		
		/*!\brief Receives strain as vector and modifies tensors to 6x1 results
		 */
		//virtual void assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)=0;
		
		//PLASTIC MODEL FUNCTIONS: these are to be used within assembleTensors function
	private:
		/*\brief Implements elastic predictor-plastic corrector algorithm
		 */
		virtual void radialReturn()=0;
		/*!\brief Returns the result of evaluating the yield function on a stress state
		 */
		virtual double yieldFunction()=0;
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
		
		
	private:
		virtual void setConstitutiveMatrix()=0;
};
#endif