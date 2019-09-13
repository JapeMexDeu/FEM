#include"Strain.h"

Strain::Strain(std::size_t sz/*=6*/):Tensor(sz)
{
	
}
double Strain::hydrostaticPressure()
{
	double hp=0;
	int s=size();
	if(s==6)
	{
		hp=this->operator[](0)+this->operator[](1)+this->operator[](2);
		return hp/3;
	}
	else
	{
		std::cout<<"THIS IS NOT A 6-ELEMENT STRESS TENSOR, SOMETHING IS WRONG\n";
	}
	return 0;
}
Strain Strain::deviatoricTensor()
{
	Strain deviatoric;
	Strain mean{1,1,1,0,0,0};
	mean*=hydrostaticPressure();
	
	deviatoric=(*this)-mean;
	return deviatoric;
}