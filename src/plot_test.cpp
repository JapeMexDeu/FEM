#include"plotter/gnuplot_i.hpp"
#include"algebra/Vector.h"

using namespace std;

int main()
{
	Vector<double> v1(10);
	v1.random();
	Vector<double> v2(10);
	v2.random();
	std::cout<<v1;
	cout<<v2;
	Vector<double> v3(10);
	v3=5;
	Vector<double> v4(10);
	v4=6;
	Gnuplot g1=Gnuplot("lines");
	 g1.reset_plot();
	g1.plot_xy(v1, v2,"Test");
	g1.plot_x(v4,"Test");
	g1.plot_x(v3,"Test"); 	 	
	sleep(50);
	
	return 0;
}