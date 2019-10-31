
#include"Element.h"

int Element::totalElements=0;
//std::string Element::type="Element";
void Element::print()
{
	std::cout<<"ELEMENT: "<<globalNum<<"\n";
	std::cout<<"TYPE: "<<type<<"\n";
	std::cout<<"NODES: ";
	for(int i=0;i<nodes.size();++i)
	{
		std::cout<<nodes[i]->getNodeNumber()<<" ";
	}
	std::cout<<"\n";
	if(!solution.empty())
	{
		std::cout<<"NODAL VALUES ARE:\n";
		std::cout<<solution;
	}
	std::cout<<"\n";
}


Element::Element(Material* mat):material(mat)
{
	
}
Matrix<double>& Element::getMatrix()
{
	return K;
}
Vector<double>& Element::getElementSolutionVector()
{
	return solution;
}
Vector<double>& Element::getInternalForce()
{
	return internalForce;
}
void Element::setMaterial(Material* mat)
{
	this->material=mat;
}
Material* Element::getMaterial()
{
	return material;
}
Tensor& Element::getStress()
{
	return stress;
}
Tensor& Element::getStrain()
{
	/* if(!(material->isPlastic()))
		return strain;
	if(material->isPlastic())
		return material->getPlasticStrain(); */
	return strain;
}
void Element::setNode(Node* n, int i)
{
	nodes[i]=n;
}
std::string Element::getElementType()
{
	return type;
}
int Element::getTotalElements()
{
	return totalElements;
}
int Element::getElementNum()
{
	return globalNum;
}
Vector<Node*> Element::getElementNodes()
{
	return nodes;
}
void Element::resizeElementSolutionVector(int n)
{
	if(solution.size()==n)
	{
		return;
	}
	solution.resize(n);
}
void Element::computeTensorialResults()
{
	setNodalValues();
	
	//calculateBReducedIntegration();
	calculateInternalForce();
	setNodalInternalForces();
	calculateBReducedIntegration();
	Vector<double> strain_vec=B*solution;//solution is the displacement
	material->assembleTensors(strain_vec, strain, stress);
	
}
void Element::setNodalValues()
{
	nodes[0]->getDOFs()[0]=solution[0];
	nodes[0]->getDOFs()[1]=solution[1];
	nodes[1]->getDOFs()[0]=solution[2];
	nodes[1]->getDOFs()[1]=solution[3];
	nodes[2]->getDOFs()[0]=solution[4];
	nodes[2]->getDOFs()[1]=solution[5];
	nodes[3]->getDOFs()[0]=solution[6];
	nodes[3]->getDOFs()[1]=solution[7];
}
void Element::setNodalInternalForces()
{
 	nodes[0]->getInternalForce()[0]+=internalForce[0];
	nodes[0]->getInternalForce()[1]+=internalForce[1];
	nodes[1]->getInternalForce()[0]+=internalForce[2];
	nodes[1]->getInternalForce()[1]+=internalForce[3];
	nodes[2]->getInternalForce()[0]+=internalForce[4];
	nodes[2]->getInternalForce()[1]+=internalForce[5];
	nodes[3]->getInternalForce()[0]+=internalForce[6];
	nodes[3]->getInternalForce()[1]+=internalForce[7];  
/*  	nodes[0]->getInternalForce()[0]=internalForce[0];
	nodes[0]->getInternalForce()[1]=internalForce[1];
	nodes[1]->getInternalForce()[0]=internalForce[2];
	nodes[1]->getInternalForce()[1]=internalForce[3];
	nodes[2]->getInternalForce()[0]=internalForce[4];
	nodes[2]->getInternalForce()[1]=internalForce[5];
	nodes[3]->getInternalForce()[0]=internalForce[6];
	nodes[3]->getInternalForce()[1]=internalForce[7];  */
}
std::ostream& operator<<(std::ostream& out, Element& el)
{
out<<"MATERIAL: ";

if(el.material==nullptr)
{
	out<<"NON ASSIGNED\n";
}
else
{
	out<<el.material->getType()<<"\n";
}/**/
	//out<<el.material->getType()<<"\n";
	out<<el.getElementNum()<<" | ";
		for(int i=0;i<el.nodes.size();++i)
	{
		out<<el.getElementNodes()[i]->getNodeNumber()<<"  ";
	}
	std::cout<<"\n";
	if(!el.solution.empty())
	{
		out<<"NODAL VALUES ARE:\n";
		out<<el.solution;
		out<<"STRAINS ARE: \n";
		out<<el.strain;
		out<<"STRESSES ARE: \n";
		out<<el.stress;
		out<<"INTERNAL FORCE IS: \n";
		out<<el.internalForce;
	}
	out<<"\n";
}