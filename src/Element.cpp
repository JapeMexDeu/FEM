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

}


Element::Element(ElasticMaterial* mat):material(mat)
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
void Element::setMaterial(ElasticMaterial* mat)
{
	this->material=mat;
}
ElasticMaterial* Element::getMaterial()
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
	solution.resize(n);
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
	out<<"\n";
}