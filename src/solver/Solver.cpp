#include"Solver.h"

Solver::Solver(Matrix<double>* A, Vector<double>* b, LinearIterator* iterator):iteration(A,b,iterator)
{
	//iteration(A,b,iterator);
}
void Solver::setLinearIterator(LinearIterator* linearit)
{
	iteration.setLinearIterator(linearit);
}
LinearIteration& Solver::getLinearIteration()
{
	return iteration;
}
void Solver::solve()
{
	iteration.iterate();
}