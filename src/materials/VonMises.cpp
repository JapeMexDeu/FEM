#include"VonMises.h"

VonMises::VonMises(double E, double mu, double yS, double pM):ElastoPlasticMaterial(E,mu,yS,pM)
{
	initializeModel();
	/* Cel(0,0)=1-mu;
	Cel(1,1)=Cel(0,0);
	Cel(2,2)=Cel(0,0);
	Cel(3,3)=(1-2*mu)/(2.0);
	Cel(4,4)=Cel(3,3);
	Cel(5,5)=Cel(3,3);
	
	Cel(0,1)=mu;
	Cel(0,2)=mu;
	Cel(1,2)=mu;
	Cel(1,0)=Cel(0,1);
	Cel(2,0)=Cel(0,2);
	Cel(2,1)=Cel(1,2);
	
	Cel*=(E)/((1+v)*(1-2*mu)); */
}
void VonMises::radialReturn(Tensor& strains, Tensor& stresses)
{
	//HERE WE WILL HAVE SO FAR THE PLASTIC STRAIN, ALTHOUGH THIS IS WRONG
	Tensor plastic_strain;
	plastic_strain=0;//initiates as zero
	//1.-LOCAL PLASTIC VALUES WHICH THE USER MUST NOT SEE
	double dLambda=0;
	double dK=0;//also called dP, freakin hardening parameter
	double yielding=0;//stores
	//Trial stress
	
	//Check yield function
	yielding=yieldFunction(stresses, plastic_strain);
	if(yielding>0)
	{
		std::cout<<"\nELEMENT IS YIELDING\n";
		//Have to increase plastic strains
	}
	if(yielding<0)
	{
		std::cout<<"\nELEMENT IS NOT YIELDING\n";
	}
}
double VonMises::yieldFunction(Tensor& stresses, Tensor& strain_ep)
{
	double eqStress=0;
	double sigmaHat=0;
	eqStress=equivalentStress(stresses);
	sigmaHat=yieldStress+plasticWork(strain_ep);
	//std::cout<<"THE EQUILENT STRESS IS: "<<eqStress<<"\n";
	//std::cout<<"THE SIGMA HAT IS: "<<sigmaHat<<"\n";
	return eqStress-sigmaHat;
}
double VonMises::equivalentStress(Tensor& stresses)
{
/* 	Matrix<double> P {{2/3,-1/3,-1/3,0,0,0},
		              {-1/3,2/3,-1/3,0,0,0},
				      {-1/3,-1/3,2/3,0,0,0},
					  {0,0,0,2,0,0},
					  {0,0,0,0,2,0},
					  {0,0,0,0,0,2}}; */
	Matrix<double> P(6,6);
	P(0,0)=2.0/3.0;
	P(1,1)=P(0,0);
	P(2,2)=P(1,1);
	P(3,3)=2;
	P(4,4)=2;
	P(5,5)=2;
	P(0,1)=-1.0/3.0;
	P(1,0)=P(0,1);
	P(2,0)=P(0,1);
	P(0,2)=P(2,0);
	P(2,1)=P(0,1);
	P(1,2)=P(1,0);
	return sqrt((stresses*(P*stresses))*(3.0/2.0)); 
}
double VonMises::plasticWork(Tensor& strain_ep)
{
	Matrix<double> Q(6,6);
	Q(0,0)=2.0/3.0;
	Q(1,1)=Q(0,0);
	Q(2,2)=Q(1,1);
	Q(3,3)=0.5;
	Q(4,4)=0.5;
	Q(5,5)=0.5;
	Q(0,1)=-1.0/3.0;
	Q(1,0)=Q(0,1);
	Q(2,0)=Q(0,1);
	Q(0,2)=Q(2,0);
	Q(2,1)=Q(0,1);
	Q(1,2)=Q(1,0);
	
	return plasticModulus*sqrt((strain_ep*(Q*strain_ep))*(3.0/2.0)); 
}
void VonMises::derivativeFSigma(Tensor& stress)
{
	double scalar=0.5/yieldStress;
	dF_dSigma[0]=2*stress[0]-stress[1]-stress[2];
	dF_dSigma[1]=2*stress[1]-stress[0]-stress[2];
	dF_dSigma[2]=2*stress[2]-stress[1]-stress[0];
	dF_dSigma[3]=6*stress[3];
	dF_dSigma[4]=6*stress[4];
	dF_dSigma[5]=6*stress[5];
	dF_dSigma*=scalar;
}

void VonMises::initializeModel()
{
	//initialize full elastic tensor
	Cel(0,0)=1-mu;
	Cel(1,1)=C(0,0);
	Cel(2,2)=C(1,1);
	
	Cel(3,3)=(1-2*mu)/2;
	Cel(4,4)=Cel(3,3);
	Cel(5,5)=Cel(4,4);
	Cel(0,1)=mu;
	Cel(1,0)=Cel(1,0);
	Cel(2,0)=Cel(1,0);
	Cel(0,2)=Cel(2,0);
	
	Cel(2,1)=Cel(0,1);
	Cel(1,2)=Cel(2,1);
	Cel*=E/((1+mu)*(1-2*mu));
	//initialize plastic parameters
	df_dK=plasticModulus;
	dLambda=0;
	dK=0;
}
void VonMises::equationsSystem(Tensor& stress)
{
	
}