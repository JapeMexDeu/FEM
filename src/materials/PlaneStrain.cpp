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

void PlaneStrain::assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)
{
	//vector s is the vectorial stress
	Vector<double> s;
	s=C*v;
	strains[0]=v[0];
	strains[1]=v[1];
	strains[3]=v[2];
	
	stresses[0]=s[0];
	stresses[1]=s[1];
	stresses[3]=s[2];
	
	stresses[2]=E*mu*(v[0]+v[1])/((1+mu)*(1-2*mu));
}