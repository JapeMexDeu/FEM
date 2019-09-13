#ifndef STRAIN_H
#define STRAIN_H

#include"Tensor.h"

class Strain: public Tensor
{
	public:
		Strain(std::size_t sz=6);
		Strain deviatoricTensor();
		virtual double hydrostaticPressure()override;
	public:
		using Tensor::Tensor;
		using Tensor::operator=;
};
#endif