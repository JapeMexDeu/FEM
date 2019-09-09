cmake_minimum_required(VERSION 3.0)
project(fem_test C CXX)

get_filename_component(ROOT_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
message(${ROOT_DIR}})
#Setting the outputs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/lib)
#compiler flags
#SET(GCC_COVERAGE_COMPILE_FLAGS "-DDEBUGGA")
#SET(CMAKE_CXX_FLAGS  "${GCC_COVERAGE_COMPILE_FLAGS}")
#adding the sources manually
set(SOURCES src/Vector.h
			src/Node.cpp
			src/Mesh.cpp
			src/Element.cpp
			src/NaiveMesh.cpp
			src/Quad2.cpp
			src/Matrix.h
			src/Discretization.cpp
			src/BoundaryConditions.cpp
			src/MechanicalBoundaryConditions.cpp
			src/Function.h
			src/TestFunction.h
			src/GaussIntegration.cpp
			src/ElasticMaterial.cpp
			src/PlaneStress.cpp
			src/PlaneStrain.cpp
			src/ImplAssembly.cpp
			src/Force.cpp
			src/solver/Jacobi.cpp
			src/solver/LinearIteration.cpp
			src/solver/Solver.cpp
			src/plotter/gnuplot_i.cpp
			src/CustomMesh.cpp
)

#location of include directories

add_library(FEM ${SOURCES})

#creation of project
add_executable(fem_test src/vector_test.cpp)
target_link_libraries(fem_test FEM)
target_include_directories(fem_test PUBLIC src/ src/plotter/)