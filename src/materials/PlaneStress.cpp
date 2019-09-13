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

void PlaneStress::assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)
{
	//vector s is the vectorial stress
	Vector<double> s;
	s=C*v;
	strains[0]=v[0];
	strains[1]=v[1];
	strains[3]=v[3];
	
	stresses[0]=s[0];
	stresses[1]=s[1];
	stresses[3]=s[3];
	
	strains[2]=(-1*mu)*(s[0]+s[1])/E;
}