#ifndef FUNCTION_H
#define FUNCTION_H
class Function
{
	public:
	/*!\brief 2 dimensional evaluation of function at point x,y
	 */
	virtual double eval(double x, double y)=0;
	virtual double operator()(double x, double y)
	{
		return eval(x,y);
	}
};
#endif