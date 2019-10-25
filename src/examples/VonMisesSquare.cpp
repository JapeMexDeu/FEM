
#include<cstdlib>

#include"../meshing/NaiveMesh.h"




#include"../physics/MechanicalBoundaryConditions.h"

#include"../materials/VonMisesPlaneStress.h"
#include"../materials/VonMisesPlaneStrain.h"
#include"../plotter/gnuplot_i.hpp"
#include"../fem/ImplAssembly.h"


#include"../solver/descent/ConjugateGradientDescent.h"

#include"../solver/NLSolverCG.h"

#include <unistd.h>
#include"meshing/CustomMesh.h"

#include"tensors/Tensor.h"
#include"tensors/Stress.h"

using std::cout;

int main(int argc, char* argv[])
{
	VonMisesPlaneStrain mat1(210,0.25, 350, 10);

	
	Force f(20,0);
	NaiveMesh mesh(1,1);
	mesh.setElementMaterial(&mat1);
	mesh.getNode(2)->setPointForce(&f);
	mesh.getNode(4)->setPointForce(&f);
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
	//mesh.print();
	//disc.print();
	
	ImplAssembly ass(&disc);

	//ass.printImplAssembly();
	
	ass.matrixAssemblyRoutine();
	ass.vectorAssemblyRoutine();
	
	ConjugateGradientDescent solver(ass.getGlobalMatrix(), ass.getGlobalVector(), 10e-12, 200, true);
	
	//solver.solve();
	if(true)
	{
		NLSolverCG nlCG(ass,10e-8,20,400);
		nlCG.printNLSolver();
		nlCG.solve();
		/* cout<<nlCG.getAbscissae();
		cout<<nlCG.getOrdinates();
		Gnuplot g2=Gnuplot("lines");
		g2.plot_xy(nlCG.getAbscissae(), nlCG.getOrdinates(),"funny");
		sleep(50); */  
		
	}
	
	
	
}