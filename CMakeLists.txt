cmake_minimum_required(VERSION 3.0)
project(fem_test C CXX)

get_filename_component(ROOT_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
message(${ROOT_DIR}})
#Setting the outputs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/lib)

#adding the sources manually
set(SOURCES src/algebra/Vector.h
			src/algebra/Matrix.h
			
			src/meshing/Mesh.cpp
			src/meshing/NaiveMesh.cpp
			src/meshing/CustomMesh.cpp
			
			src/elements/Element.cpp
			src/elements/Quad2.cpp
			src/elements/Node.cpp
			
			src/materials/ElasticMaterial.cpp
			src/materials/PlaneStress.cpp
			src/materials/PlaneStrain.cpp
			src/materials/Material.cpp
			src/materials/VonMises.cpp
			src/materials/VonMisesPlaneStress.cpp
			src/materials/VonMisesPlaneStrain.cpp
			src/materials/ElastoPlasticMaterial.cpp
			
			src/solver/Jacobi.cpp
			#src/solver/LinearIteration.cpp
			src/solver/LinearIterativeSolver.cpp
			src/solver/descent/DescentMethod.cpp
			src/solver/descent/GradientDescent.cpp
			src/solver/descent/ConjugateGradientDescent.cpp
			src/solver/NLSolver.cpp
			src/solver/LSolver.cpp
			src/solver/NLSolverCG.cpp
			
			
			src/tensors/Tensor.cpp
			src/tensors/Stress.cpp
			
			src/fem/Function.h
			src/fem/TestFunction.h
			src/fem/GaussIntegration.cpp
			src/fem/Discretization.cpp
			src/fem/Discretization.cpp
			src/fem/ImplAssembly.cpp
			
			src/plotter/gnuplot_i.cpp
			
			
			src/physics/BoundaryConditions.cpp
			src/physics/MechanicalBoundaryConditions.cpp
			src/physics/Force.cpp						
)

#location of include directories

add_library(FEM ${SOURCES})

#creation of project
#add_executable(fem_test src/plot_test.cpp)
add_executable(fem_test src/2dSquare.cpp)
#add_executable(fem_test src/vector_test.cpp)
target_link_libraries(fem_test FEM)
target_include_directories(fem_test PUBLIC src/ src/plotter/)