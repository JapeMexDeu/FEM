#include"../fem/Discretization.h"
#include"physics/MechanicalBoundaryConditions.h"
#include"../materials/PlaneStrain.h"
#include"../materials/PlaneStress.h"
#include"../fem/ImplAssembly.h"
#include"../solver/ArcLength.h"
#include"../meshing/CustomMesh.h"

using std::cout;
int main(int argc, char* argv[])
{
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
	
	ImplAssembly ass(&disc);

	ass.vectorAssemblyRoutine();
	ass.matrixAssemblyRoutine();

	ArcLength solver(ass,0.00001,1);
	solver.printArcLength();
	solver.solve();
		
	
	return 0;
}