#ifndef IMATRIX_H
#define IMATRIX_H

#include"Vector.h"

class IMatrix
{
	
	public:
		
		//****SETTERS AND GETTERS
		virtual void setRows(int r)=0;
		virtual void setColumns(int c)=0;
		
		virtual int getRows()=0;
		virtual int geColumns()=0;
		
		//******OVERLOADED OPERATORS*****
		virtual friend std::ostream &operator<<(std::ostream &out, Matrix &m)=0;

		virtual Matrix& operator+(const Matrix &m)=0;
		virtual Matrix& operator-(const Matrix &m)=0;
		virtual Matrix& operator*(const Matrix &m)=0;
		//Matrix& operator*=(double number);
		virtual Matrix& operator*(const double a)=0;
		

	protected:
		
		
		int rows;
		int columns;
};
#endif