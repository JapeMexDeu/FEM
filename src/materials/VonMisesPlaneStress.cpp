#include"VonMisesPlaneStress.h"

VonMisesPlaneStress::VonMisesPlaneStress(double E, double mu/*=0*/, 
										 double yS/*=0*/, double pM/*=0*/):VonMises(E,mu,yS,pM)
{
	type="PLASTIC-VON MISES PLANE STRESS";
	setConstitutiveMatrix();
}
void VonMisesPlaneStress::assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)
{
	//vector s is the vectorial stress
	Vector<double> s;
	s=C*v;
	//std::cout<<s<<v;
	strains[0]=v[0];
	strains[1]=v[1];
	strains[3]=v[2];
	
	stresses[0]=s[0];
	stresses[1]=s[1];
	stresses[3]=s[2];
	
	strains[2]=(-1*mu)*(s[0]+s[1])/E;
	std::cout<<"\nTHE EQUIVALENT STRESS IS: "<<equivalentStress(stresses)<<"\n";
	//Once the two tensors have been assembled (evaluated on 1 Gauss Point for now) we correct everything
	//Mind you this is not the correct place to have this function, it must be at the place where we calculate the
	//values of the displacements...but we have to start somewhere
	//HERE WE CHECK
	
}
void VonMisesPlaneStress::setConstitutiveMatrix()
{
	C.matrixResize(3,3);
	//Diagonal first
	C(0,0)=1;
	C(1,1)=1;
	C(2,2)=(1-mu)/2;
	//Other terms
	C(0,1)=mu;
	C(1,0)=C(0,1);
	C*=(E)/(1-mu*mu);
}