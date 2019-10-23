/**
  FILE: Element.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: Base class for FEM elements, ABSTRACT class. INSTANTIABLE. Should be improved by using it in other classes as pointer and 
			   making it purely virtual, and non-instantiable. Then make the necessary methods purely virtual and remove the empty implementations 
			   from the class declaration.
			   REGARDING MATERIAL: if carefully thought, it would be better and make more sense, perhaps even be more elegant, to assign the material
								   to the geometrical model, using whichever geometrical sets defined, for instance in any avergae CAD program. Here we
								   do not yet have a geometry class which can enable us to do this, therefore we have to use the next level, in our case 
								   the discretized geometry i.e. the Mesh class, and there assign element by element the material law instead of taking
								   it from the geometry. This should be a further improvement to our package. 
  		 
*/
#ifndef ELEMENT_H
#define ELEMENT_H
#include"../materials/Material.h"
#include"../algebra/Matrix.h"
#include"Node.h"
#include"../fem/Function.h"
#include"../fem/GaussIntegration.h"
#include"../tensors/Tensor.h"
class Element
{
	public:
		
		virtual void print();
		
		//Setters and getters
		static std::string getElementType();
		static int getTotalElements();
		int getElementNum();
	    void setNode(Node* n, int i);
		Vector<Node*> getElementNodes();
		void setMaterial(Material* mat);
		Material* getMaterial();
		Matrix<double>& getMatrix();
		Vector<double>& getElementSolutionVector();
		Vector<double>& getInternalForce();
		//FUNCTIONS THAT CALCULATE
		virtual void calculateMatrix()=0;
		void resizeElementSolutionVector(int n);
		void computeTensorialResults();
		//OPERATOR OVERLOAD
		friend std::ostream& operator<<(std::ostream &out, Element& el);
		
	protected:
		//Stresses and strains
		Tensor stress;/**<Default sized to 6 elements*/
		Tensor strain;/**<Default sized to 6 elements*/
		Element(Material* mat=nullptr);
		Material* material;/**<Material mode, pointer of non-instantiable class*/
		GaussIntegration g;
		Matrix<double> K;/**<Stiffness Matrix of the Element, calculation is derived-class-dependent*/
		Matrix<double> B;/**<B-operator matrix*/
		Vector<double> internalForce;/**<Internal force vector of the element*/
		Vector<Node*> nodes;/**<Stores nodes that compose the elment, size is type-dependant*/
		Vector<double> solution;/**<Stores values of solutions for each nodes and number of DOFs per node*/
		int globalNum;/**<Individual element number*/
		//double thickness;
		/******************STATIC MEMBERS******/
		static std::string type;/**<Name of element type, defined in base classes*/
		static int totalElements;/**<Elements in whole structure*/
	
	private:
		/*!\brief Calculates the B-operator only using 1 Gauss Point at (0,0) in the element
		 */
		virtual void calculateBReducedIntegration()=0;
		/*!\brief Calculates the internal force vector at the 0,0 reduced integration point, result is 8x1
		 */
		virtual void calculateInternalForce()=0;
		/*!\brief Type-dependent implementation, every element declares the jacobian matrix elements as Function instances and call Gauss integration
		 */
		virtual void calculateJacobian(Matrix<double>& Jacobian)=0;
		/*!\brief Type-dependent implementation, every element declares the G matrix elements as Function instances and call Gauss integration
		 */
		virtual void calculateG(Matrix<double>& G)=0;
		/*!\brief Used within A, receives values from Jacobian
		 */
		virtual void assembleA(Matrix<double>& A, Matrix<double>& Jacobian)=0;
		//virtual void calculateB(Matrix<double>& G, Matrix<double>& A)=0;
};
#endif