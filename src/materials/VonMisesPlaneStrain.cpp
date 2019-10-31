#include"VonMisesPlaneStrain.h"

VonMisesPlaneStrain::VonMisesPlaneStrain(double E, double mu/*=0*/, 
										 double yS/*=0*/, double pM/*=0*/):VonMises(E,mu,yS,pM)
{
	type="PLASTIC-VON MISES PLANE STRAIN";
	setConstitutiveMatrix();
}
void VonMisesPlaneStrain::assembleTensors(Vector<double>& v, Tensor& strains, Tensor& stresses)
{
	bool res=false;
	//vector s is the vectorial stress increment
	Vector<double> s;
	s=C*v;
	strains[0]+=v[0];
	strains[1]+=v[1];
	strains[3]+=v[2];
	if(false)
	{
		stresses[0]=s[0];
		stresses[1]=s[1];
		stresses[3]=s[2];
		stresses[2]=E*mu*(v[0]+v[1])/((1+mu)*(1-2*mu));
	}
 	 

	//HERE WE CHECK for plastic behavior with the strains
	if(true)
		stresses=radialReturn(strains);
	//setConstitutiveMatrix();

	
}
void VonMisesPlaneStrain::setConstitutiveMatrix()
{
	C.matrixResize(3,3);
	if(plastic==false)//loading same values as Cel
	{
		//Diagonal first
		C(0,0)=(1-mu);
		C(1,1)=1-mu;
		C(2,2)=(1-2*mu)/2;
		//Other terms
		C(0,1)=mu;
		C(1,0)=C(0,1);
		C*=(E)/((1-(2*mu))*(1+mu));
	}
	if(plastic==true)
	{
		//have to choose some values from Cep
		C(0,0)=Cep(0,0);
		C(1,1)=Cep(1,1);
		C(2,2)=Cep(3,3);
	
		//Other terms
		C(0,1)=Cep(0,1);
		C(1,0)=C(0,1);
		
	}
}