#include"VonMises.h"

VonMises::VonMises(double E, double mu=0, double yS=0, double pM=0):ElastoPlasticMaterial(E,mu,yS,pM)
{
	//Left empty
}
double VonMises::equivalentStress(Tensor& stress)
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
	std::cout<<"\nP IS: "<<P;
	std::cout<<"\nTENSOR IS"<<stress<<"\n";
	return sqrt((stress*(P*stress))*(3.0/2.0)); 
}
double VonMises::hardeningEvolution(Tensor& strain)
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
	
	std::cout<<"\nQ IS: "<<Q;
	std::cout<<"\nTENSOR IS"<<strain<<"\n";
	return sqrt((strain*(Q*strain))*(3.0/2.0)); 
}
void VonMises::derivativeFSigma()
{
	double scalar=0.5*1;
	//dF_dSigma
}
void VonMises::initializeModel()
{
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
	
}