#ifndef PLANESTRESS_H
#define PLANESTRESS_H
#include"ElasticMaterial.h"
class PlaneStress:public ElasticMaterial
{
	public:
		PlaneStress(double mu, double E);
		virtual void assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)override;
		virtual std::string getType()override;
	private:
	
	virtual void setConstitutiveMatrix()override;

};
#endif