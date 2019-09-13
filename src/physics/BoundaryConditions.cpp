#include"BoundaryConditions.h"
BoundaryConditions::BoundaryConditions(int degOF/*=0*/, std::string name,
									   Vector<double> values/*=Vector<double>(0)*/,
									   Vector<bool> fixed/*=Vector<bool>(0)*/,
									   Vector<int> indices/*=Vector<int>(0)*/
									   ):dof(degOF), type(name),   node_indices(indices), 
									   value_conditions(values), fixed_conditions(fixed)                                 
{
	//left empty on purpose
}
Vector<double>& BoundaryConditions::getValues()
{
	return value_conditions;
}
Vector<bool>& BoundaryConditions::getFixed()
{
	return fixed_conditions;
}
Vector<int>& BoundaryConditions::getIndices()
{
	return node_indices;
}

void BoundaryConditions::addNode(int index)
{
	node_indices.push_back(index);
}
void BoundaryConditions::addNode(Node* node)
{
	node_indices.push_back(node->getNodeNumber());
}
void BoundaryConditions::setNodes(Vector<int> indices)
{

	node_indices=indices;  
} 
int BoundaryConditions::getDOF()const
{
	return dof;
}
std::string BoundaryConditions::getType()
{
	return type;
}
void BoundaryConditions::setValue(double value, int i)
{
	value_conditions[i]=value;
}
void BoundaryConditions::fixDOF(int i)
{
	fixed_conditions[i]=true;
}
void BoundaryConditions::print()
{
	std::cout<<"TYPE:"<<type<<"\n";
	std::cout<<"DOFs:"<<dof<<"\n";
	std::cout<<"NODE SET:( ";
	for(int i=0;i<node_indices.size();++i)
	{
		std::cout<<node_indices[i]<<" ";
	}
	std::cout<<")\n";
	
}