#include"Vector.h"
#include"Node.h"
#include"Quad2.h"
#include<cstdlib>
#include"Matrix.h"
#include"NaiveMesh.h"
#include"Discretization.h"
#include"TestFunction.h"
#include"GaussIntegration.h"
//#include"BoundaryConditions.h"
#include"MechanicalBoundaryConditions.h"
#include"PlaneStrain.h"
#include"PlaneStress.h"
#include"plotter/gnuplot_i.hpp"
#include"ImplAssembly.h"
#include"solver/Solver.h"
#include"solver/Jacobi.h"
#include <unistd.h>
#include"CustomMesh.h"
using std::cout;
int main(int argc, char* argv[])
{
	
	std::cout<<"\nTEST OF MATERIAL\n";
	PlaneStrain mat1(0.25,600);
    cout<<mat1;
	
	cout<<"*****CREATION OF MESH\n";
	Force f(0,1);
	NaiveMesh mesh(1,1);
	mesh.setElementMaterial(&mat1);
	mesh.getNode(2)->setPointForce(&f);
	mesh.print();

	Discretization disc(2,mesh);
	
	MechanicalBoundaryConditions mbc(false,true,false);
	
	MechanicalBoundaryConditions mbc2(true,false,false);
	Vector<int> indices={1};
	Vector<int>indices2={4};
	mbc.setNodes(indices);
	mbc2.setNodes(indices2);
	
	disc.addBoundaryCondition(mbc);
	disc.addBoundaryCondition(mbc2);
	
	disc.print();
	disc.DOFenum();
	mesh.print();
	disc.print();
	
	ImplAssembly ass(&disc);

	ass.printImplAssembly();
	
	ass.matrixAssemblyRoutine();
	ass.vectorAssemblyRoutine();
	
	
	Jacobi jac(&(ass.getGlobalMatrix()));
	
	Solver solver(&(ass.getGlobalMatrix()), &(ass.getGlobalVector()), &jac);
	
	solver.solve();
	//
	//
	//
	/*
	std::vector<double> displacements(solver.getLinearIteration().getU().size());
	std::vector<double> iterates(solver.getLinearIteration().getU().size());
	
	for(size_t i=0;i<iterates.size();++i)
	{
		iterates[i]=(double)(i+1);
		displacements[i]=(double)(solver.getLinearIteration().getU()[i]/solver.getLinearIteration().getU()[i]);
	}
	
	Gnuplot g1=Gnuplot("points");
	
	std::vector<double> x;
    std::vector<double> y;
	cout << endl << endl << "*** user-defined lists of doubles" << endl;
    for (int i = 0; i < 50; i++)
        x.push_back((double)i * (double)i);
    g1.reset_plot();
    g1.set_style("impulses");
    g1.plot_x(x,"user-defined doubles");
    sleep(5);
	cout << endl << endl << "*** user-defined lists of points" << endl;
    x.clear();
    for (int i = 0; i < 50; i++)
      {
        x.push_back((double)i);
        y.push_back((double)i * (double)i);
      }
    g1.reset_plot();
    g1.set_style("points");
    g1.plot_xy(x,y,"user-defined points");
    sleep(5);
	
	 g1.reset_plot();
	 g1.cmd("set yrange[0:1]");
	g1.plot_xy(solver.getLinearIteration().getIterates(), solver.getLinearIteration().getError(),"funny");
	sleep(15);
	
return 0;
}