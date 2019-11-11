#include"ArcLength.h"



void ArcLength::solve()
{
	Assembly.matrixAssemblyRoutine();
	Kt=Assembly.getGlobalMatrix();
}
void ArcLength::setLSolver()
{
	lSolver=&cg;
}