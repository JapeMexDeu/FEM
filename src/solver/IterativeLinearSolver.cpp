#include"LinearIterativeSolver.h"

LinearIterativeSolver::LinearIterativeSolver(Matrix<double>& A, Vector<double>& b, 
											 LinearIterator* iterator):LSolver(A,b),iterator(iterator)
{
	//left empty
}
void LinearIterativeSolver::setLinearIterator(LinearIterator* linearit)
{
	iteration.setLinearIterator(linearit);
}
void LinearIterativeSolver::solve()
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