#include"Function.h"
class TestFunction:public Function
{
	public:
	virtual double eval(double x, double y)override
	{
		return (1+x)/(2+y);
	}
	
};