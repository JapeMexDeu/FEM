#ifndef PLANESTRAIN_H
#define PLANESTRAIN_H
#include"ElasticMaterial.h"
class PlaneStrain:public ElasticMaterial
{
	public:
		PlaneStrain(double mu, double E);
		virtual void assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)override;
		virtual std::string getType()override;
	private:
	
	virtual void setConstitutiveMatrix()override;

};
#endif