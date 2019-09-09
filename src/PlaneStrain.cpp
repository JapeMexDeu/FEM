#include"PlaneStrain.h"

PlaneStrain::PlaneStrain(double mu, double E):ElasticMaterial(mu,E)
{
	type="Elastic-PlaneStrain";
	setConstitutiveMatrix();
}
void PlaneStrain::setConstitutiveMatrix()
{
	C.matrixResize(3,3);
	//Diagonal first
	C(0,0)=(1-mu);
	C(1,1)=1-mu;
	C(2,2)=(1-2*mu)/2;
	//Other terms
	C(0,1)=mu;
	C(1,0)=C(0,1);
	C*=(E)/((1-(2*mu))*(1+mu));
}

std::string PlaneStrain::getType()
{
	return type;
}