#include"Tensor.h"

Tensor::Tensor(std::size_t sz/*=6*/):Vector(sz)
{
	
}
Tensor& Tensor::operator=(const Vector<double>& v)
{
	Vector<double>::operator=(v);
	return *this;
}
double Tensor::hydrostaticPressure()
{
	double hp=0;
	int s=size();
	if(s==6)
	{
		hp=this->operator[](0)+this->operator[](1)+this->operator[](2);
		return hp/3;
	}
	else if(s==3)
	{
		hp=this->operator[](0)+this->operator[](1);
		return hp/3;
	}
	else
	{
		std::cout<<"NOT DEFINED IN CODE\n";
		return 0;
	}
	return hp;//should never happen
}