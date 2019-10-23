#ifndef QUAD2_H
#define QUAD2_H	

#include"Element.h"

class Quad2:public Element
{
	public:
		Quad2(Node* n1=nullptr, Node* n2=nullptr, Node* n3=nullptr, Node* n4=nullptr, Material* mat=nullptr);

		virtual void print()override;
		/*!\brief Stiffness matrix (K) generation
		 *We assume that since we apply Gauss Integration on the matrices which are a fuction of ksi and epsilon, then we just have
		 *to implement the multiplication of all the matrices to get K, as seen on steps. Everything using a 1-point rule
		 *In Steps: 1.-calculate Jacobian and detJ
		 *			2.-calculate A matrix
		 *			3.-Calculate G
		 *			4.-calculate B=GA
		 *			5.-implement K=detJ*B_T*D*B
		 */
		virtual void calculateMatrix()override;
		//Setters and getters
		//virtual void setNode(Node* n, int i)override;
	private:
		virtual void calculateInternalForce()override;
		virtual void calculateBReducedIntegration()override;
		virtual void calculateJacobian(Matrix<double>& Jacobian)override;
		virtual void calculateG(Matrix<double>& G)override;
		virtual void assembleA(Matrix<double>& A, Matrix<double>& Jacobian)override;
	//DECLARATION OF THE JACOBIAN ELEMENT AND THE DERIVATIVES OF THE SHAPE FUNCTIONS
	private:
		class Jacobian1:public Function
		{
			private:
				double x1,x2,x3,x4;/*<<Four node position elements to use in evaluation routine*/
			public:
				Jacobian1(double x1=0, double x2=0, double x3=0, double x4=0):x1(x1),x2(x2),x3(x3),x4(x4)
				{
					//Left empty
				}
				void setConstants(double x1, double x2, double x3, double x4)
				{
					this->x1=x1;
					this->x2=x2;
					this->x3=x3;
					this->x4=x4;

				}
				void showConstants()
				{
					std::cout<<"("<<x1<<x2<<x3<<x4<<")\n";
				}
				virtual double eval(double ksi, double eta)override
				{
					return -(1-eta)*x1+(1-eta)*x2+(1+eta)*x3-(1+eta)*x4;
				}
			
		};
		class Jacobian2:public Function
		{
			private:
				double x1,x2,x3,x4;/*<<Four node position elements to use in evaluation routine*/
			public:
				Jacobian2(double x1=0, double x2=0, double x3=0, double x4=0):x1(x1),x2(x2),x3(x3),x4(x4)
				{
					//Left empty
				}
				void setConstants(double x1, double x2, double x3, double x4)
				{
					this->x1=x1;
					this->x2=x2;
					this->x3=x3;
					this->x4=x4;

				}
				void showConstants()
				{
					std::cout<<"("<<x1<<x2<<x3<<x4<<")\n";
				}
				virtual double eval(double ksi, double eta)override
				{
					return -(1-ksi)*x1-(1+ksi)*x2+(1+ksi)*x3+(1-ksi)*x4;
				}
			
		};
		class dNdksiNeg:public Function
		{
			public:
			virtual double eval(double ksi, double eta)override
			{
				return (1-eta);
			}
		};
		class dNdksiPos:public Function
		{
			virtual double eval(double ksi, double eta)override
			{
				return (1+eta);
			}
		};
		class dNdetaNeg:public Function
		{
			virtual double eval(double ksi, double eta)override
			{
				return (1-ksi);
			}
		};
		class dNdetaPos:public Function
		{
			virtual double eval(double ksi, double eta)override
			{
				return (1+ksi);
			}
		};
	private:
		Jacobian1 j1;
		Jacobian2 j2;
		dNdksiNeg g1;/*<<Function: derivative of shape function w.r.t. ksi, with negative of form (1-eta)*/
		dNdksiPos g2;/*<<Function: derivative of shape function w.r.t. ksi, with positive of form (1+eta)*/
		dNdetaNeg g3;/*<<Function: derivative of shape function w.r.t. eta, with negative of form (1-ksi)*/
		dNdetaPos g4;/*<<Function: derivative of shape function w.r.t. eta, with positive of form (1+ksi)*/
};
#endif