#include<cstdlib>

#include"../meshing/NaiveMesh.h"




#include"../physics/MechanicalBoundaryConditions.h"

#include"../materials/VonMisesPlaneStress.h"
#include"../materials/VonMisesPlaneStrain.h"
#include"../materials/PlaneStrain.h"
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
	
	PlaneStrain mat1(210,0.25);
	
	NaiveMesh mesh(15,15);
	Vector<int> leftInclusive=mesh.setLeftInclusive();
	Vector<int> rightInclusive=mesh.setRightInclusive();
	//mesh.print();
	mesh.setElementMaterial(&mat1);
	
	Force f(100,0);
	for(int i=0;i<rightInclusive.size();++i)
	{
		mesh.getNode(rightInclusive[i])->setPointForce(&f);
	}
	
	Discretization disc(2,mesh);
	
	MechanicalBoundaryConditions encastre(true,true,false);
	encastre.setNodes(leftInclusive);
	
	//mesh.getNode(2)->setPointForce(&f);
	//mesh.getNode(4)->setPointForce(&f);
	//mesh.print();
	disc.addBoundaryCondition(encastre);
	disc.DOFenum();
	//mesh.print();
	ImplAssembly ass(&disc);
	
	ass.printImplAssembly();
	
	ass.matrixAssemblyRoutine();
	ass.vectorAssemblyRoutine();
	
	
	
	ConjugateGradientDescent solver(ass.getGlobalMatrix(), ass.getGlobalVector(), 10e-10, 200, true);
	
	solver.solve();
	
 	ass.localSolutionVectorAssemblyRoutine(solver.getU());
	//mesh.print();
}
