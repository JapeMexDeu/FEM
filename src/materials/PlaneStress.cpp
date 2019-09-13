#include"PlaneStress.h"

PlaneStress::PlaneStress(double mu, double E):ElasticMaterial(mu,E)
{
		type="Elastic-PlaneStress";
		setConstitutiveMatrix();
}
void PlaneStress::setConstitutiveMatrix()
{
	C.matrixResize(3,3);
	//Diagonal first
	C(0,0)=1;
	C(1,1)=1;
	C(2,2)=(1-mu)/2;
	//Other terms
	C(0,1)=mu;
	C(1,0)=C(0,1);
	C*=(E)/(1-mu*mu);
}
std::string PlaneStress::getType()
{
	return type;
}