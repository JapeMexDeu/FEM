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
	VonMisesPlaneStress mat1(210,0.25, 350, 10);
	
	Tensor strainState {0,0,0,0,0,0};

	


return 0;
}