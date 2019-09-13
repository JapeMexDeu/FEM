#include"MechanicalBoundaryConditions.h"

MechanicalBoundaryConditions::MechanicalBoundaryConditions(bool i/*=false*/, 
														   bool j/*=false*/, bool k/*=false*/):BoundaryConditions(2,"Constraint")
{
	
	fixed_conditions.resize(dof);
	if(fixed_conditions.size()>=2)
	{
		fixed_conditions[0]=i;
		fixed_conditions[1]=j;
		if(fixed_conditions.size()==3)
		{
			fixed_conditions[0]=i;
			fixed_conditions[1]=j;
			fixed_conditions[2]=k;
		}
	}
	
}
void MechanicalBoundaryConditions::print()
{
	BoundaryConditions::print();
}
std::ostream& operator<<(std::ostream& out, MechanicalBoundaryConditions& bc)
{
	out<<"TYPE: "<<bc.getType()<<" SIZE: "<<bc.getDOF()<<"\n";
	out<<"ASSIGNED NODES: ";
	for(int i=0;i<bc.node_indices.size();++i)
	{
		out<<bc.node_indices[i]<<" ";
	}
	out<<"\n";
	out<<"( ";
	for(int i=0;i<bc.fixed_conditions.size();++i)
	{
		if(bc.fixed_conditions[i]==true)
		{
			out<<"fixed ";
		}
		else
		{
			out<<"free ";
		}
	}
	out<<")\n";
	return out;
}