#include"gnuplot_i.hpp"
#include"../fem/ImplAssembly.h"
class Plotter:public gnuplot_i
{
	public:
		Plotter(string sytle="lines", ImplAssembly* model=nullptr );
	
		void plot();
		void setNode(int n);
		void updateNodeData();
		void addX(double x);
		void addY(double y);
		
		//setters and getters
		void setModel(ImplAssembly* model)
		void setLabels(string& xLabel, string& yLabel);
		void setTitle(string &title);
		void setPlottingDirection(int xyz);
		Vector<double>& getX();
		Vector<double>& getY();
		
		
	private:
		ImplAssembly*  model;
		Element* element;
		Node* node;
		Vector<double> x;
		Vector<double> y;
		int plotDirection;
		string title;
};