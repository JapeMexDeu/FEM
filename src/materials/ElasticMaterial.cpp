#include"ElasticMaterial.h"

ElasticMaterial::ElasticMaterial(double mu, double E):mu(mu),E(E)
{
	//left empty
}

double ElasticMaterial::getPoisson()
{
	return this->mu;
}
double ElasticMaterial::getModulus()
{
	return this->E;
}
Matrix<double>& ElasticMaterial::getConstitutiveMatrix()
{
	return C;
}

std::ostream& operator<<(std::ostream& out, ElasticMaterial& mat)
{
	out<<mat.type<<"\n";
	out<<mat.C;
	out<<"\n";
}