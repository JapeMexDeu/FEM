#ifndef PLANESTRESS_H
#define PLANESTRESS_H
#include"ElasticMaterial.h"
class PlaneStress:public ElasticMaterial
{
	public:
		PlaneStress(double mu, double E);
		virtual std::string getType()override;
	private:
	
	virtual void setConstitutiveMatrix()override;

};
#endif