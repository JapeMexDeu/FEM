#include"Plotter.h"

Plotter::Plotter(string sytle/*="lines"*/,ImplAssembly* model/*=nullptr*/):gnuplot_i(style),model(model)
{
	//Left empty
}
void updateNodeData()
{
	node->
}
void Plotter::plot()
{
	plot_xy(x,y,title);
}
void Plotter::setPlottingDirection(int xyz)
{
	plotDirection=xyz;
}
void Plotter::setTitle(string& title)
{
	title=title;
}
void Plotter::setLabels(string xLabel, yLabel)
{
	set_ylabel(ylabel);
	set_xlabel(xlabel);
}
void Plotter::addX(double x)
{
	x.push_back(x);
}
void addY(double y)
{
	y.push_back(y);
}