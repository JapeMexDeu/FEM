#include"Force.h"

Force::Force(double f1, double f2, double f3)
{
	force[0]=f1;
	force[1]=f2;
	force[2]=f3;
}


//setters and getters
void Force::setComponent(double f, int i)
{
	force[i]=f;
}
void Force::setComponent1(double f)
{
	force[0]=f;
}
void Force::setComponent2(double f)
{
	force[1]=f;
}
void Force::setComponent3(double f)
{
	force[2]=f;
}
double Force::getComponent(int i)
{
	return force[i];
}
double Force::getComponent1()
{
	return force[0];
}
double Force::getComponent2()
{
	return force[1];
}
double Force::getComponent3()
{
	return force[2];
}
Vector<double>& Force::getForce()
{
	return this->force;
}