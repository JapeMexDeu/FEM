#include"Jacobi.h"

Jacobi::Jacobi(Matrix<double>*  a)
{
	
	this->A=a;
	this->type="Jacobi\n";
	      
}
void Jacobi::inverseMultiply(Vector<double>& r, Vector<double>& c)
{
	if(r.size()!=c.size())
		std::cout<<"ERROR: DIMENSIONAL ERROR, OPERATION WILL FAIL";
	for(int i=0;i<r.size();++i)
	{
		c[i]=(r[i]/(A->operator()(i,i)));
	}
	//std::cout<<c;
}