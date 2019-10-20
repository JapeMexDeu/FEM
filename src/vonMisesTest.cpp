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
#include"materials/VonMisesPlaneStrain.h"
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
	Vector<double> u {1,2,3,4};
	Vector<double> v {1,2,3};
	Matrix<double> m;
	
	m.OuterProduct(u,v);
	
	cout<<m;
	cout<<"TESTING THE MATERIAL\n";
	VonMisesPlaneStress mat1(210,0.25, 350, 10);
	VonMisesPlaneStrain mat2(210, 0.25, 350, 10);
	Tensor strainState {4,0,0,0,0,0};
	cout<<"THE STRAIN STATE IS: "<<strainState;
	cout<<mat1;
	cout<<mat2;
	mat2.rr(strainState);

return 0;
}