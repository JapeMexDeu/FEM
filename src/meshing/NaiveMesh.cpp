#include"NaiveMesh.h"

NaiveMesh::NaiveMesh(int n/*=2*/, int m/*=2*/):n(n),m(m)
{
	//std::cout<<"\nInitalize mesh\n";
	a=0;
	c=0;
	b=10;
	d=10;
	typeOfElement="4-NODE QUAD";
	setNumElements(n,m);
	setNumNodes(n,m);
	nodes.resize(numNodes);
	elements.resize(numElements);
	local_elements.resize(numElements);
	
	InitializeMesh();
}
void NaiveMesh::print()
{
	Mesh::print();
	std::cout<<"   TYPE: "<<typeOfElement<<"\n";
	
	for(int i=0;i<nodes.size();++i)
	{
		std::cout<<"   "<<nodes[i];
	}
	for(int i=0;i<elements.size();++i)
	{
		std::cout<<"   "<<local_elements[i];
	}
	std::cout<<"END: PRINTING OF MESH******\n";
}
/* Vector<Element>& NaiveMesh::getElements()
{
	return elements;
} */
void NaiveMesh::setNumElements(int n, int m)
{
	numElements=n*m;
}
void NaiveMesh::setNumNodes(int n, int m)
{
	numNodes=(n+1)*(m+1);
}
void NaiveMesh::setElementMaterial(Material* mat)
{
	for(int i=0;i<local_elements.size();++i)
	{
		local_elements[i].setMaterial(mat);
	}
}
void NaiveMesh::InitializeMesh()
{
	std::cout<<"BEGIN: INITIALIZE MESH****\n";
	double h=(double)(b-a)/(double)n;
	double k=(double)(d-c)/(double)m;
	//std::cout<<"h: "<<h<<" k:"<<k<<"\n";
	//std::cout<<"NumNodes: "<<numNodes<<"\n";
	//std::cout<<"Size of Nodes: "<<nodes.size()<<"\n";
	//std::cout<<"Total Nodes so far: "<<Node::getNodesTotalNumber()<<"\n";
	double x_incr, y_incr;
	//Start on 1 like algorithm says
	int i=1;
	int j=1;
	int z=0;
	//generate all increments and assign Nodal coordinates
	for(j;j<=(m+1);++j)
	{
		for(i;i<=(n+1);++i)
		{
			x_incr=a+(i-1)*h;
			y_incr=c+(j-1)*k;
			nodes[z].setPosition(x_incr,y_incr,0);
			//std::cout<<"\nNODE"<<z+1<<" :"<<x_incr<<","<<y_incr<<" z: "<<z<<"\n";
			//std::cout<<nodes[z];
			z++;
		}
		i=1;		
	}	
	
	//Assign all elements
	int index=0;
	
 	for(i=0;i<elements.size();++i)
	{
		if((i+1+index)%(n+1)==0)
		{
			++index;
		}
		//std::cout<<"\nValue of i: "<<i<<" index is: "<<index<<"\n";
		//Quad2 el(&nodes[i+index],&nodes[i+1+index],&nodes[i+2+n+index],&nodes[i+1+n+index]);
		local_elements[i].setNode(&nodes[i+index],0);
		local_elements[i].setNode(&nodes[i+1+index],1);
		local_elements[i].setNode(&nodes[i+2+n+index],2);
		local_elements[i].setNode(&nodes[i+1+n+index],3);
		//local_elements[i]=el;
		elements[i]=&(local_elements[i]);
		//elements[i]->print();

		//std::cout<<(*elements[i]);
		
	} 
		
	std::cout<<"   NODES CREATED: "<<numNodes<<"\n";
	std::cout<<"   ELEMENTS CREATED: "<<numElements<<"\n";
	std::cout<<"END: INITIALIZE MESH****\n";
	
}
Vector<int> NaiveMesh::setLeftInclusive()
{
	Vector<int> set;
	for(int i=0;i<nodes.size();++i)
	{
		for(int j=0;j<=m;++j)
		{
			if(nodes[i].getNodeNumber()==(1+(n+1)*j))
			{
				set.push_back(nodes[i].getNodeNumber());
			}
		}
		
	}
	return set;
}
Vector<int> NaiveMesh::setRightInclusive()
{
	Vector<int> set;
	for(int i=0;i<nodes.size();++i)
	{
		for(int j=0;j<=m+1;++j)
		{
			if(nodes[i].getNodeNumber()==(n+1)*(j+1))
			{
				set.push_back(nodes[i].getNodeNumber());
			}
		}
		
	}
	return set;
}