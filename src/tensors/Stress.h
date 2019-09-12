#ifndef STRESS_H
#define STRESS_H

#include"Tensor.h"

class Stress:public Tensor
{
	public: 
		Stress(std::size_t sz=6);
		Stress deviatoricStress();
		virtual double hydrostaticPressure()override;
		
	public:
		using Tensor::Tensor;
		using Tensor::operator=;
};

#endif