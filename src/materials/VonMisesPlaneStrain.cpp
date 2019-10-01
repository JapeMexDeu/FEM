#include"VonMisesPlaneStrain.h"

VonMisesPlaneStrain::VonMisesPlaneStrain(double E, double mu/*=0*/, 
										 double yS/*=0*/, double pM/*=0*/):VonMises(E,mu,yS,pM)
{
	type="PLASTIC-VON MISES PLANE STRAIN";
	setConstitutiveMatrix();
}
void VonMisesPlaneStrain::assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)
{
	//vector s is the vectorial stress
Vector<double> s;
	s=C*v;
	strains[0]=v[0];
	strains[1]=v[1];
	strains[3]=v[2];
	
	stresses[0]=s[0];
	stresses[1]=s[1];
	stresses[3]=s[2];
	
	stresses[2]=E*mu*(v[0]+v[1])/((1+mu)*(1-2*mu));
	//std::cout<<"\nTHE EQUIVALENT STRESS IS: "<<equivalentStress(stresses)<<"\n";
	//Once the two tensors have been assembled (evaluated on 1 Gauss Point for now) we correct everything
	//Mind you this is not the correct place to have this function, it must be at the place where we calculate the
	//values of the displacements...but we have to start somewhere...MAYBE ALL THESE IS NOT TOTALLY TRUE; PERHAPS
	//PERHAPS THIS IS THE CORRECT PLACE TO DO SO
	//HERE WE CHECK
	
}
void VonMisesPlaneStrain::setConstitutiveMatrix()
{
	C.matrixResize(3,3);
	//Diagonal first
	C(0,0)=(1-mu);
	C(1,1)=1-mu;
	C(2,2)=(1-2*mu)/2;
	//Other terms
	C(0,1)=mu;
	C(1,0)=C(0,1);
	C*=(E)/((1-(2*mu))*(1+mu));
}