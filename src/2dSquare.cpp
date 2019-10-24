#include"algebra/Vector.h"
#include"elements/Node.h"
#include"elements/Quad2.h"
#include<cstdlib>
#include"algebra/Matrix.h"
#include"meshing/NaiveMesh.h"
#include"fem/Discretization.h"
#include"fem/TestFunction.h"
#include"fem/GaussIntegration.h"

#include"physics/MechanicalBoundaryConditions.h"
#include"materials/PlaneStrain.h"
#include"materials/PlaneStress.h"
#include"materials/VonMisesPlaneStress.h"
#include"plotter/gnuplot_i.hpp"
#include"fem/ImplAssembly.h"
#include"solver/LinearIterativeSolver.h"
#include"solver/Jacobi.h"
#include"solver/descent/ConjugateGradientDescent.h"
#include"solver/descent/GradientDescent.h"
#include"solver/descent/DescentMethod.h"
#include"solver/NLSolverCG.h"

#include <unistd.h>
#include"meshing/CustomMesh.h"

#include"tensors/Tensor.h"
#include"tensors/Stress.h"

using std::cout;

int main(int argc, char* argv[])
{
	//VonMisesPlaneStress mat1(210,0.25, 350, 10);
	//std::cout<<"\nTEST OF MATERIAL\n";
	PlaneStrain mat1(210,0.25);
    //cout<<mat1;
	
	cout<<"*****CREATION OF MESH\n";
	Force f(1000,0);
	NaiveMesh mesh(1,1);
	mesh.setElementMaterial(&mat1);
	mesh.getNode(2)->setPointForce(&f);
	mesh.print();

	Discretization disc(2,mesh);
	
	MechanicalBoundaryConditions mbc(true,true,false);
	
	//MechanicalBoundaryConditions mbc2(true,false,false);
	Vector<int> indices={1,3};
	Vector<int>indices2={4};
	mbc.setNodes(indices);
	//mbc2.setNodes(indices2);
	
	disc.addBoundaryCondition(mbc);
	//disc.addBoundaryCondition(mbc2);
	
	disc.print();
	disc.DOFenum();
	mesh.print();
	disc.print();
	
	ImplAssembly ass(&disc);

	ass.printImplAssembly();
	
	ass.matrixAssemblyRoutine();
	ass.vectorAssemblyRoutine();
	
	
	
	ConjugateGradientDescent solver(ass.getGlobalMatrix(), ass.getGlobalVector(), 10e-10, 200, true);
	
	solver.solve();
	
 	ass.localSolutionVectorAssemblyRoutine(solver.getU());
	mesh.print();
	cout<<"Global Ku: \n";
	cout<<ass.getGlobalMatrix()*solver.getU();
	cout<<"Ku: \n";
	cout<<(mesh.getElements()[0]->getMatrix()*mesh.getElements()[0]->getElementSolutionVector());
	cout<<(mesh.getElements()[0]->getMatrix()*mesh.getElements()[0]->getElementSolutionVector()).norm()<<"\n";
	cout<<"True internal force vector:\n";
	cout<<(mesh.getElements()[0]->getInternalForce());
	cout<<(mesh.getElements()[0]->getInternalForce()).norm();
	cout<<"the external forces are: \n";
	cout<<ass.getGlobalVector();
	/*
	Gnuplot g1=Gnuplot("lines");
	g1.reset_plot();
	g1.cmd("set yrange[0:1]");
	g1.plot_xy(solver.getIterates(), solver.getError(),"funny"); 
	*/
	/* NLSolverCG nlCG(ass,10e-10,100,2);
	nlCG.printNLSolver();
	nlCG.solve();
	//sleep(50);
	cout<<nlCG.getAbscissae();
	cout<<nlCG.getOrdinates();
	Gnuplot g2=Gnuplot("lines");
	g2.plot_xy(nlCG.getAbscissae(), nlCG.getOrdinates(),"funny");
	sleep(50);  */
	
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
	*/
return 0;
}