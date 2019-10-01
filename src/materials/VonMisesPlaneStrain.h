#ifndef VONMISESPLANESTRAIN_H
#define VONMISESPLANESTRAIN_H
#include"VonMises.h"

class VonMisesPlaneStrain:public VonMises
{
		public:
		VonMisesPlaneStrain(double E, double mu=0, double yS=0, double pM=0);
		//SAME AS ELASTIC PLANE STRESS
		virtual void assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)override;
		virtual void setConstitutiveMatrix()override;
	private:
		/*\brief Implements elastic predictor-plastic corrector algorithm
		 */
		//virtual void radialReturn()override;
		/*!\brief Returns the result of evaluating the yield function on a stress state
		 */
		//virtual double yieldFunction()=0;
};
#endif