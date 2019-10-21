
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
void Element::setMaterial(Material* mat)
{
	this->material=mat;
}
Material* Element::getMaterial()
{
	return material;
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
	calculateBReducedIntegration();
	Vector<double> strain_vec=B*solution;//solution is the displacement
	material->assembleTensors(strain_vec, strain, stress);
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
	}
	out<<"\n";
}