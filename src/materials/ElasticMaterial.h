/**
  FILE: ElasticMaterial.h
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: 
  		 
*/
#ifndef ELASTICMATERIAL_H
#define ELASTICMATERIAL_H

#include"IMaterial.h"

class ElasticMaterial:public IMaterial
{
	public:
		ElasticMaterial(double mu, double E);
		virtual Matrix<double>& getConstitutiveMatrix()override;
		//Setters and getters
		virtual std::string getType()=0;
		double getPoisson();
		double getModulus();
		
		friend std::ostream& operator<<(std::ostream &out, ElasticMaterial& mat);
	protected:
		Matrix<double> C;
		double mu;
		double E;
		std::string type;
		
	private:
		virtual void setConstitutiveMatrix()=0;
};

#endif