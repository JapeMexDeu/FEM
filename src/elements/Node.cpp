#include"Node.h"

//Start amount of Nodes
int Node::totalNodes=0;
int Node::numDOF=0;

Node::Node(double X, double Y, double Z)
{
	position[0]=X;
	position[1]=Y;
	position[2]=Z;
	pointForce=nullptr;
	++totalNodes;
	globalNum=totalNodes;
}
Node::Node(Vector<double> &pos)
{
	position=pos;
	++totalNodes;
	globalNum=totalNodes;
}


//*******SETTERS AND GETTERS******
int Node::getNodesTotalNumber()
{
	return totalNodes;
}
void Node::setPosition(double x, double y, double z)
{
	position[0]=x;
	position[1]=y;
	position[2]=z;
}
void Node::setPosition(Vector<double> &vector)
{
	position=vector;
}
void Node::setX(double a)
{
	position[0]=a;
}
void Node::setY(double a)
{
	position[1]=a;
}
void Node::setZ(double a)
{
	position[2]=a;
}
Vector<double> Node::getPosition()
{
	return position;
}
void Node::setPointForce(Force* f)
{
	pointForce=f;
}
Force* Node::getPointForce()
{
	return pointForce;
}
Vector<int>& Node::getDOFnumbers()
{
	return dofNumbers;
}
Vector<double> Node::getDOFs()
{
	return dofs;
}
int Node::getNodeNumber()
{
	return globalNum;
}
void Node::print()
{
	std::cout<<"\nNODE "<<globalNum<<"/"<<totalNodes<<"\n";
	std::cout<<position;
	std::cout<<dofNumbers;
	std::cout<<"FORCE APPLIED:";
	if(pointForce==nullptr)
		std::cout<<"NO FORCE\n";
	else
		std::cout<<pointForce;
}
void Node::setDOF(int dof)
{
	dofNumbers.resize(dof);
	dofs.resize(dof);
}
void Node::setNumDof(int n)
{
	numDOF=n;
}
int Node::getNumDof()
{
	return numDOF;
}
std::ostream& operator<<(std::ostream& out, Node& n)
{
	out<<"\nNODE "<<n.getNodeNumber()<<" from a total of "<<Node::totalNodes<<":( ";
	for(size_t i=0;i<n.getPosition().size();++i)
	{
		out<<n.getPosition()[i]<<" ";
	}
	out<<" )\n";
	out<<"DOFs numbers are: "<<":( ";
	for(size_t i=0;i<n.getDOFnumbers().size();++i)
	{
		out<<n.getDOFnumbers()[i]<<" ";
	}
	out<<")\n";
	if(n.pointForce!=nullptr)
	{
		out<<"FORCE: "<<":( ";
		for(size_t i=0;i<n.getPointForce()->getForce().size();++i)
		{
			out<<n.getPointForce()->getForce()[i]<<" ";
		}
		out<<" )\n";
	}
	
	return out;
}