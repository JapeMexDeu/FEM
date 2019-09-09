#include"GaussIntegration.h"

std::vector<std::vector<double>> GaussIntegration::points={{-sqrt(3)/3,-sqrt(3)/3},
														{-sqrt(3)/3,sqrt(3)/3},
														{sqrt(3)/3,sqrt(3)/3},
														{sqrt(3)/3,-sqrt(3)/3}
													   };
double GaussIntegration::eval_point_x=0;
double GaussIntegration::eval_point_y=0;
													   
double GaussIntegration::evaluate(Function& func)
{
	double result=0;
	for(int i=0;i<4;++i)
	{
		std::cout<<i<<" ksi: "<<points[i][0]<<", eta: "<<points[i][1]<<"\n";
		result+=func.eval(points[i][0],points[i][1]);
	}
	return result;
}
double GaussIntegration::evaluate1Point(Function& func)
{
	double result=0;
	
	result+=func.eval(0,0);
	
	return result;
}
double GaussIntegration::evaluateAtPoint(Function& func)
{
	return func.eval(eval_point_x, eval_point_y);
}
void GaussIntegration::showPoints()
{
	for(int i=0;i<4;++i)
	{
		std::cout<<i<<" ksi: "<<points[i][0]<<", eta: "<<points[i][1]<<"\n";
	}
}
void GaussIntegration::setPoint(double x, double y)
{
	GaussIntegration::eval_point_x=x;
	GaussIntegration::eval_point_y=y;
}
double GaussIntegration::getKsiGP(int i)
{
	return points[i][0];
}
double GaussIntegration::getEtaGP(int i)
{
	return points[i][1];
}
void GaussIntegration::setPoint2GPi(int i)
{
	GaussIntegration::setPoint(getKsiGP(i),getEtaGP(i));
	
}
void GaussIntegration::showCurrentPoint()
{
	std::cout<<" ksi: "<<eval_point_x<<", eta: "<<eval_point_y<<"\n";
}