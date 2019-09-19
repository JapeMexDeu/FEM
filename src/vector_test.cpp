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
#include"plotter/gnuplot_i.hpp"
#include"fem/ImplAssembly.h"
#include"solver/Solver.h"
#include"solver/Jacobi.h"
#include"solver/descent/ConjugateGradientDescent.h"
#include"solver/descent/GradientDescent.h"
#include"solver/descent/DescentMethod.h"
#include <unistd.h>
#include"meshing/CustomMesh.h"

#include"tensors/Tensor.h"
#include"tensors/Stress.h"
using std::cout;
int main(int argc, char* argv[])
{
	/*
	std::vector<double> v{1,2,3,4,5};
	Vector<double> v1{1,2,3,4};
	//Vector<double> v2=v;
	Stress s1;
	s1=10;
	s1*=3;
	
	cout<<s1;
	cout<<s1[0];
	cout<<s1.deviatoricTensor();
	Tensor t1{1,2,3};
	t1=20.0;
	cout<<t1;
	
	PlaneStress mat1(0.2,3000000);
	Tensor t2;
	t2=mat1.getConstitutiveMatrix()*t1;
	s1=mat1.getConstitutiveMatrix()*t1;
	cout<<s1;
	cout<<mat1.getConstitutiveMatrix();
	cout<<t2;
	cout<<mat1.getConstitutiveMatrix()*t1;
	cout<<t2.hydrostaticPressure();
	*/
	PlaneStress mat1(3000000,0.2);
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
	//Solver solver(&(ass.getGlobalMatrix()), &(ass.getGlobalVector()), &jac);
	ConjugateGradientDescent solver(ass.getGlobalMatrix(), ass.getGlobalVector());
	solver.solve();//solver2.solve();
	ass.localSolutionVectorAssemblyRoutine(solver.getU());
	cm.print();
	Gnuplot g1=Gnuplot("lines");
	 g1.reset_plot();
	 g1.cmd("set yrange[0:1]");
	g1.plot_xy(solver.getIterates(), solver.getError(),"funny");
	sleep(50);
		
	
	return 0;
}