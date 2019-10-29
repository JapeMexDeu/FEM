#include"Plotter.h"

Plotter::Plotter(ImplAssembly* model/*=nullptr*/, string style/*="lines"*/,
				 string title)
				 :Gnuplot(style),model(model), title(title)
{
	//Left empty
}
void Plotter::setPlotter(string xlabel, string ylabel, ImplAssembly* mod, int dir, int node)
{
	xlabel=xlabel;
	ylabel=ylabel;
	setLabels(xlabel,ylabel);
	setModel(mod);
	setPlottingDirection(dir);
	setNode(node);
}
void Plotter::setSPlotter(string xlabel, string ylabel, ImplAssembly* mod, int dir, int element)
{
	xlabel=xlabel;
	ylabel=ylabel;
	setLabels(xlabel,ylabel);
	setModel(mod);
	setPlottingDirection(dir);
	setElement(element);
}
void Plotter::setElement(int n)
{
	element=model->getDiscretization()->getMesh().getElement(n);
}
void Plotter::setNode(int n)
{
	node=model->getDiscretization()->getMesh().getNode(n);
}
void Plotter::setModel(ImplAssembly* mod) 
{
	model=mod;
}
void Plotter::updateNodeData()
{
	addY(abs(node->getInternalForce()[plotDirection]));
	addX(abs(node->getDOFs()[plotDirection]));
	//addY(node->getInternalForce().norm());
	//addX(node->getDOFs().norm());
	
}
void Plotter::updateElementData()
{
	addY(abs(element->getStress()[plotDirection]));
	addX(abs(element->getStrain()[plotDirection]));
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
void Plotter::setLabels(string& xLabel, string& yLabel)
{
	set_ylabel(yLabel);
	set_xlabel(xLabel);
}
void Plotter::addX(double x_)
{
	x.push_back(x_);
}
void Plotter::addY(double y_)
{
	y.push_back(y_);
}
void Plotter::printData()
{
	std::cout<<x;
	std::cout<<y;
}