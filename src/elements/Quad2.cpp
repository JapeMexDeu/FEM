#include"Quad2.h"

std::string Element::type="4-NODE QUAD";

Quad2::Quad2(Node* n1, Node* n2, Node* n3, Node* n4, Material* mat):Element(mat)
{
	nodes.resize(4);
	nodes[0]=n1;
	nodes[1]=n2;
	nodes[2]=n3;
	nodes[3]=n4;
	//material=mat;
	totalElements++;
	globalNum=totalElements;
}

/* void Quad2::setNode(Node* n, int i)
{
	nodes[i]=n;
} */
void Quad2::print()
{
	Element::print();

}
/*
void Quad2::calculateMatrix()
{
	
	Matrix<double> Jacobian(2,2);
	Matrix<double> G(4,8);
	Matrix<double> A(3,4);
	Matrix<double> B(3,8);
	K.matrixResize(B.getColumns(),B.getColumns());
	calculateJacobian(Jacobian);
	
	std::cout<<"JACOBIAN MATRIX IS: \n";
	std::cout<<Jacobian;
	calculateG(G);
	std::cout<<"THE G MATRIX: \n";
	std::cout<<G;
	assembleA(A,Jacobian);
	std::cout<<"THE A MATRIX: \n";
	std::cout<<A;
	std::cout<<"THE B MATRIX IS: \n";
	B=A*G;
	std::cout<<B;
	//std::cout<<~B;
	//provisional determinant of Jacobian calculation
	double detJ=Jacobian(0,0)*Jacobian(1,1)-Jacobian(0,1)*Jacobian(1,0);
	std::cout<<"THE DET OF J IS: \n";
	std::cout<<detJ<<"\n";
	//K=(~B*material->getConstitutiveMatrix())*B;
	std::cout<<"\n"<<~B*material->getConstitutiveMatrix();
	K=~B*material->getConstitutiveMatrix();
	K*=B;
	//K*=detJ;
	std::cout<<"THE K MATRIX: \n";
	std::cout<<K;
	
}
*/
void Quad2::calculateMatrix()
{
	K=0;//Make sure it wont overlap different load step values
	Matrix<double> Jacobian(2,2);
	Matrix<double> G(4,8);
	Matrix<double> A(3,4);
	Matrix<double> B_gp(3,8);
	Matrix<double> K_gp(8,8);
	B.matrixResize(B_gp.getColumns(),B_gp.getColumns());
	K.matrixResize(B.getColumns(),B.getColumns());
	for(int i=0;i<4;++i)
	{
		//std::cout<<"FOR GAUSS POINT"<<i+1<<"\n";
		
		GaussIntegration::setPoint2GPi(i);//must have an i
		//GaussIntegration::showCurrentPoint();
		calculateJacobian(Jacobian);
		calculateG(G);
		assembleA(A,Jacobian);
		B_gp=A*G;
		/*
		std::cout<<"JACOBIAN MATRIX IS: \n";
		std::cout<<Jacobian;

		std::cout<<"THE G MATRIX: \n";
		std::cout<<G;

		std::cout<<"THE A MATRIX: \n";
		std::cout<<A;
		std::cout<<"THE B MATRIX IS: \n";
		std::cout<<B_gp;
		*/
		double detJ=Jacobian(0,0)*Jacobian(1,1)-Jacobian(0,1)*Jacobian(1,0);
		K_gp=~B_gp*material->getConstitutiveMatrix();
		
		K_gp*=B_gp;
		K_gp*=detJ;
		K_gp*=4;
		K+=K_gp;
		//std::cout<<"THE K FOR GP: "<<i<<"\n";
		//std::cout<<K_gp;
		Jacobian=0;
		G=0;
		A=0;
		B_gp=0;
		K_gp=0;
	}
	//std::cout<<"The ELEMENT K IS\n";
	/**/
	//K*=4;
	//std::cout<<K;
	for(int i=0;i<K.getColumns();++i)
	{
		for(int j=0;j<K.getColumns();++j)
		{
			if(abs(K(i,j))<1e-5)
				K(i,j)=0;
		}
	}
	
	//std::cout<<K;
	
}
/*PRIVATE METHODS FOR CALCULATION OF STIFFNESS MATRIX AND OTHER STUFF*/
void Quad2::calculateBReducedIntegration()
{
	GaussIntegration::setPoint(0,0);
	Matrix<double> Jacobian(2,2);
	Matrix<double> G(4,8);
	Matrix<double> A(3,4);
	calculateJacobian(Jacobian);
	calculateG(G);
	assembleA(A, Jacobian);
	
	B=A*G;
}
void Quad2::calculateJacobian(Matrix<double>& Jacobian)
{
	//For the first row
	j1.setConstants(nodes[0]->getPosition()[0], nodes[1]->getPosition()[0],
					nodes[2]->getPosition()[0], nodes[3]->getPosition()[0]);
	Jacobian(0,0)=GaussIntegration::evaluateAtPoint(this->j1);
	//j1.showConstants();
	j1.setConstants(nodes[0]->getPosition()[1], nodes[1]->getPosition()[1],
					nodes[2]->getPosition()[1], nodes[3]->getPosition()[1]);
	Jacobian(0,1)=GaussIntegration::evaluateAtPoint(this->j1);
	//j1.showConstants();
	//For the second row
	j2.setConstants(nodes[0]->getPosition()[0], nodes[1]->getPosition()[0],
					nodes[2]->getPosition()[0], nodes[3]->getPosition()[0]);
	Jacobian(1,0)=GaussIntegration::evaluateAtPoint(this->j2);
	//j2.showConstants();
	j2.setConstants(nodes[0]->getPosition()[1], nodes[1]->getPosition()[1],
					nodes[2]->getPosition()[1], nodes[3]->getPosition()[1]);
	Jacobian(1,1)=GaussIntegration::evaluateAtPoint(this->j2);
	//j2.showConstants();
	Jacobian*=0.25;
}
void Quad2::calculateG(Matrix<double>& G)
{
	//dNdksiNeg g1;/*<<Function: derivative of shape function w.r.t. ksi, with negative of form (1-eta)*/
	//dNdksiPos g2;/*<<Function: derivative of shape function w.r.t. ksi, with positive of form (1+eta)*/
	//dNdetaNeg g3;/*<<Function: derivative of shape function w.r.t. eta, with negative of form (1-ksi)*/
	//dNdetaPos g4;/*<<Function: derivative of shape function w.r.t. eta, with positive of form (1+ksi)*/
	//Do all the first row
	G(0,0)=-GaussIntegration::evaluateAtPoint(this->g1);
	G(0,2)=GaussIntegration::evaluateAtPoint(this->g1);
	G(0,4)=GaussIntegration::evaluateAtPoint(this->g2);
	G(0,6)=-GaussIntegration::evaluateAtPoint(this->g2);
	//Do second row afterwards
	G(1,0)=-GaussIntegration::evaluateAtPoint(this->g3);
	G(1,2)=-GaussIntegration::evaluateAtPoint(this->g4);
	G(1,4)=GaussIntegration::evaluateAtPoint(this->g4);
	G(1,6)=GaussIntegration::evaluateAtPoint(this->g3);
	//Third row is copy of first row
	G(2,1)=G(0,0);
	G(2,3)=G(0,2);
	G(2,5)=G(0,4);
	G(2,7)=G(0,6);
	//Fourth row is copy of second
	G(3,1)=G(1,0);
	G(3,3)=G(1,2);
	G(3,5)=G(1,4);
	G(3,7)=G(1,6);
	G*=0.25;
}
void Quad2::assembleA(Matrix<double>& A, Matrix<double>& Jacobian)
{
	A(0,0)=Jacobian(1,1);
	A(0,1)=-Jacobian(0,1);
	A(1,2)=-Jacobian(1,0);
	A(1,3)=Jacobian(0,0);
	A(2,0)=-Jacobian(1,0);
	A(2,1)=Jacobian(0,0);
	A(2,2)=Jacobian(1,1);
	A(2,3)=-Jacobian(0,1);
	//std::cout<<"THE DET OF J IS: \n";
	//std::cout<<(Jacobian(0,0)*Jacobian(1,1)-Jacobian(1,0)*Jacobian(0,1))<<"\n";
	A*=1/(Jacobian(0,0)*Jacobian(1,1)-Jacobian(1,0)*Jacobian(0,1));
}
