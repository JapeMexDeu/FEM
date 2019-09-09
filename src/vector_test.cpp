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
	
	PlaneStress mat1(0.2,3000000);
	/*
	Node n1(0,5);
	Node n2(6,5);
	Node n3(20,12);
	Node n4(0,12);
	cout<<mat1;
	Quad2 q1(&n1,&n2,&n3,&n4);
	q1.setMaterial(&mat1);
	q1.calculateMatrix();
	*/
	CustomMesh cm(8,3);
	cm.getNodes()[0].setPosition(0,5,0);
	cm.getNodes()[1].setPosition(0,12,0);
	cm.getNodes()[2].setPosition(6,0,0);
	cm.getNodes()[3].setPosition(6,5,0);
	cm.getNodes()[4].setPosition(20,0,0);
	cm.getNodes()[5].setPosition(20,12,0);
	cm.getNodes()[6].setPosition(54,0,0);
	cm.getNodes()[7].setPosition(54,12,0);
	
	//set the elements
	cm.getElements()[0]->setNode(&(cm.getNodes()[0]),0);
	cm.getElements()[0]->setNode(&(cm.getNodes()[3]),1);
	cm.getElements()[0]->setNode(&(cm.getNodes()[5]),2);
	cm.getElements()[0]->setNode(&(cm.getNodes()[1]),3);
	
	cm.getElements()[1]->setNode(&(cm.getNodes()[2]),0);
	cm.getElements()[1]->setNode(&(cm.getNodes()[4]),1);
	cm.getElements()[1]->setNode(&(cm.getNodes()[5]),2);
	cm.getElements()[1]->setNode(&(cm.getNodes()[3]),3);
	
	cm.getElements()[2]->setNode(&(cm.getNodes()[4]),0);
	cm.getElements()[2]->setNode(&(cm.getNodes()[6]),1);
	cm.getElements()[2]->setNode(&(cm.getNodes()[7]),2);
	cm.getElements()[2]->setNode(&(cm.getNodes()[5]),3);
	cm.setElementMaterial(&mat1);
	cm.print();
	Force f2(0,-2000);
	Force f6(0,-5400);
	cm.getNode(2)->setPointForce(&f2);
	cm.getNode(6)->setPointForce(&f6);
	Discretization disc(2,cm);
	//cm.print();
	MechanicalBoundaryConditions nodes12(true,false,false);
	MechanicalBoundaryConditions nodes78(true,true,false);
	Vector<int> indeces1={1,2};
	Vector<int> indeces2={7,8};
	
	nodes12.setNodes(indeces1);
	nodes78.setNodes(indeces2);
	
	disc.addBoundaryCondition(nodes12);
	disc.addBoundaryCondition(nodes78);
	
	disc.DOFenum();
	//cm.print();
	//disc.print();
	
	ImplAssembly ass(&disc);

	//ass.printImplAssembly();
	ass.vectorAssemblyRoutine();
	ass.matrixAssemblyRoutine();
	//
	//std::cout<<ass.getGlobalVector();
	//std::cout<<ass.getGlobalMatrix();
	Jacobi jac(&(ass.getGlobalMatrix()));
	Solver solver(&(ass.getGlobalMatrix()), &(ass.getGlobalVector()), &jac);
	
	solver.solve();
	ass.localSolutionVectorAssemblyRoutine();
	Gnuplot g1=Gnuplot("points");
	 g1.reset_plot();
	 g1.cmd("set yrange[0:1]");
	g1.plot_xy(solver.getLinearIteration().getIterates(), solver.getLinearIteration().getError(),"funny");
	sleep(15);
	/*
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
	sleep(15);*/		
	
	return 0;
}