#ifndef MECHANICALBOUNDARYCONDITIONS_H
#define MECHANICALBOUNDARYCONDITIONS_H
#include"BoundaryConditions.h"
class MechanicalBoundaryConditions:public BoundaryConditions
{
	//Vector<double> value_conditions;/*<<Vector of given initial values, lower precedence than fixed_conditions*/
	//Vector<bool> fixed_conditions;/*<<Set that indicates if any DOFs are fixed or free, this variable is implementation dependent*/
	//Vector<int> node_indices;/*<<Set of node pointers where BC is being applied to*/
	//int dof;/*<<Degrees of freedom for a type of BC, some of them will be constrained*/
	//std::string type;
	public:
		MechanicalBoundaryConditions(bool i=false, bool j=false, bool k=false);
		virtual void print()override;
		friend std::ostream& operator<<(std::ostream& out, MechanicalBoundaryConditions& bc);


};

#endif