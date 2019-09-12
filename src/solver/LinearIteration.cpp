#include"LinearIteration.h"
LinearIteration::LinearIteration(Matrix<double>* A, Vector<double>* b, 
								 LinearIterator* iterator, 
								 double tolerance/*=10e-9*/, int maxIterations/*=100*/):A(A),b(b),B(iterator),tolerance(tolerance),
																						maxIterations(maxIterations)
{
	if(b!=nullptr)
	{
		u.resize(b->size());
	}
	           
}
void LinearIteration::iterate()
{
	int count=1;
	std::cout<<"BEGIN:ITERATION\n";
	//create and calculate residuum
	Vector<double> residuum(b->size());
	Vector<double> residuum_temp(b->size());
	Vector<double> c(b->size());
	calculateResiduum(residuum);
	
	double max=residuum.norm();
	//std::cout<<"ITERATION"<<"    RESIDUUM NORM\n";
	
	//std::setprecision(5);
	
	
	while(residuum.norm()>tolerance&&count<maxIterations)
	{
		
		//std::cout<<"     "<<count<<"              ";
		iterates.push_back(count);
		//std::cout<<residuum.norm()<<"\n";
		error.push_back(residuum.norm());
		//calculate corrector
		calculateCorrector(residuum, c);
		c*=0.9;
		this->u+=c;
		//std::cout<<"        "<<u<<residuum<<c;
		//update residuum
		//residuum_temp=(*A)*c;
		//residuum-=residuum_temp;
		calculateResiduum(residuum);
		error[count-1]=error[count-1]/max;
		count++;
		
	}
	
	//std::cout<<"SIZE OF ERROR IS: "<<error.size()<<"\n";
	//std::cout<<"SIZE OF COUNT IS: "<<iterates.size()<<"\n";
	std::cout<<"SOLUTION VECTOR IS: \n"<<u;
	//std::cout<<(*A);
	std::cout<<(*b);
}
//SETTERS AND GETTERS
void LinearIteration::setLinearIterator(LinearIterator* iterator)
{
	this->B=iterator;
	u.resize(this->b->size());
}
LinearIterator* LinearIteration::getLinearIterator()
{
	return B;
}
double LinearIteration::getTolerance()
{
	return tolerance;
}
void LinearIteration::setTolerance(double t)
{
	tolerance=t;
}
int LinearIteration::getMaxIterations()
{
	return maxIterations;
}
void LinearIteration::setMaxIterations(int m)
{
	maxIterations=m;
}
void LinearIteration::setU(double s)
{
	u=s;
}
Vector<double>& LinearIteration::getU()
{
	return u;
}
//PRIVATE METHODS
void LinearIteration::calculateResiduum(Vector<double>& r)
{
	r=0;
	r=(*b)-(*A)*(this->u);
	
}
void LinearIteration::calculateCorrector(Vector<double>& r, Vector<double>& c)
{
	B->inverseMultiply(r,c);
}

std::vector<double> LinearIteration::getIterates()
{
	return iterates;
}
std::vector<double> LinearIteration::getError()
{
	return error;
}