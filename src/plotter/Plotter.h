#include"gnuplot_i.hpp"
#include"../fem/ImplAssembly.h"
class Plotter:public Gnuplot
{
	public:
		Plotter(ImplAssembly* model=nullptr, string style="points", string title="NODAL FORCE-DISPLACEMENT");
	
		
		
		void updateNodeData();
		void updateElementData();
		void addX(double x);
		void addY(double y);
		void printData();
		void plot();
		void plotElement();
		//setters and getters
		void setNode(int n);
		void setElement(int n);
		void setPlotter(string xlabel, string ylabel, ImplAssembly* mod, int dir, int node);
		void setSPlotter(string xlabel, string ylabel, ImplAssembly* mod, int dir, int element);
		void setModel(ImplAssembly* model);
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
		string xlabel;
		string ylabel;
};