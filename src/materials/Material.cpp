#include"Material.h"


Material::Material(double E_, double mu_, double yS/*=0*/, double pM/*=0*/):E(E_),mu(mu_),yieldStress(yS),plasticModulus(pM)
{
	
	//Left empty
	Cel(0,0)=1-mu;
	Cel(1,1)=Cel(0,0);
	Cel(2,2)=Cel(1,1);
	
	Cel(3,3)=(1-2*mu)/2;
	Cel(4,4)=Cel(3,3);
	Cel(5,5)=Cel(4,4);
	Cel(0,1)=mu;
	Cel(1,0)=Cel(0,1);
	Cel(2,0)=Cel(1,0);
	Cel(0,2)=Cel(2,0);
	
	Cel(2,1)=Cel(0,1);
	Cel(1,2)=Cel(2,1);
	Cel*=E/((1+mu)*(1-2*mu));
	plastic=false;
	
}
Matrix<double>& Material::getConstitutiveMatrix()
{
	return C;
}
std::string Material::getType()
{
	return type;
}
double Material::getPoisson()
{
	return mu;
}
double Material::getModulus()
{
	return E;
}
double Material::getYieldStress()
{
	return yieldStress;
}
double Material::getPlasticModulus()
{
	return plasticModulus;
}
std::ostream& operator<<(std::ostream& out, Material& mat)
{

	out<<mat.type<<"\n";
	out<<mat.C;
	out<<mat.Cel;
	out<<"\n";
}