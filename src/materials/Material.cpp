#include"Material.h"


Material::Material(double E_, double mu_, double yS/*=0*/, double pM/*=0*/):E(E_),mu(mu_),yieldStress(yS),plasticModulus(pM)
{
	//Left empty
	//C_el
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
	out<<"\n";
}