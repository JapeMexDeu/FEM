#include"Discretization.h"

Discretization::Discretization(int dof, Mesh& mesh): dofPerNode(dof), mesh(mesh)
{
	resizeMeshDof();
}
void Discretization::DOFenum()
{
	resizeMeshDof();
}
void Discretization::addDOF()
{
	
}
Vector<BoundaryConditions>* Discretization::modify_boundary_conditions()
{
	return &boundary_conditions;
}
void Discretization::addBoundaryCondition(BoundaryConditions bc)
{
	boundary_conditions.push_back(bc);
}
void Discretization::print()
{
	std::cout<<"DISCRETIZATION OF :"<<dofPerNode<<"\n";
	std::cout<<"DISCRETIZING: "<<mesh.getNumElements()<<" ELEMENTS OF TYPE: "<<mesh.getElements()[0]->getElementType()<<"\n";
	std::cout<<"DOF ASSIGNED :"<<totalDOF<<"\n";
	std::cout<<"HAS "<<boundary_conditions.size()<<" BOUNDARY CONDITIONS\n";
	std::cout<<"BOUNDARY CONDITIONS ARE: \n";
	for(int i=0;i<boundary_conditions.size();++i)
	{
		std::cout<<"BC:"<<i+1;
		boundary_conditions[i].print();
	}
	std::cout<<"\n";
}
//************PRIVATE METHODS
int Discretization::DOFenumHelper(int index, Node* node)
{
	for(int i=0;i<node->getDOFnumbers().size();++i)
	{
		if(node->getDOFnumbers()[i]!= -1)
		{
			node->getDOFnumbers()[i]=index;
			++index;
		}
	}
	return index;
}
void Discretization::applyBoundaryConditions()
{
	for(int i=0;i<boundary_conditions.size();++i)
	{
		for(int j=0;j<boundary_conditions[i].getFixed().size();++j)
		{
			//we have to access every node inside every bc[i] and apply the bc
			for(int k=0;k<boundary_conditions[i].getIndices().size();++k)
			{
				Node* currentNode=mesh.getNode(boundary_conditions[i].getIndices()[k]);
				applyBoundaryConditionsHelper(&boundary_conditions[i], &currentNode);
				
			}
			
		}
	}
}
void Discretization::applyBoundaryConditionsHelper(BoundaryConditions* bc, Node** node)
{
	//manipulate dfnumbers of node in accordance to bc values, true is fixed
	for(int i=0;i<(*node)->getDOFnumbers().size();++i)
	{
		if(bc->getFixed()[i]==true)
		{
			(*node)->getDOFnumbers()[i]=-1;
		}
	}
}
void Discretization::resizeMeshDof()
{
	std::cout<<"\nBEGIN: DISCRETIZATION OF MESH\n";
	//numDof is a static member so we can call it directly through its functions
	Node::setNumDof(dofPerNode);
	std::cout<<"   THE NUMBER OF DOFs IS: "<<Node::getNumDof()<<"\n";
	//Check if boundary conditions exist, if so apply them else do nothing, just proceed.
	if(boundary_conditions.empty())
	{
		std::cout<<"   THERE ARE NO BOUNDARY CONDITIONS\n";
	}
	else
	{
		std::cout<<"   THER ARE: "<<boundary_conditions.size()<<" BCs\n";
		std::cout<<   "BEGIN: APPLY BOUNDARY CONDITONS\n";
		applyBoundaryConditions();
		std::cout<<"   END: APPLY BOUNDARY CONDITONS\n";
	}
	int numberNodes=mesh.getNodes().size();
	std::cout<<"   THERE ARE: "<<numberNodes<<" NODES\n";
	//Nodes::setDOF(dofPerNode);
	int index=1;
	for(int i=0;i<numberNodes;++i)
	{
		mesh.getNodes()[i].setDOF(dofPerNode);
		index=DOFenumHelper(index, &mesh.getNodes()[i] );
	}
	totalDOF=index-1;
	std::cout<<"\nEND: DISCRETIZATION OF MESH\n";
}

//setters and getters
int Discretization::getTotalDOF()
{
	return totalDOF;
}
int Discretization::getDofPerNode()
{
	return dofPerNode;
}
Mesh& Discretization::getMesh()
{
	return mesh;
}