/**
  FILE: Matrix.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: includes Vector, provides matrix functionalities. TEMPLATE CLASS. Overloaded operators only work with numerical types.
			   
*/
#ifndef MATRIX_H
#define MATRIX_H

#include<iomanip>
#include"Vector.h"

template<typename T>
class Matrix
{
	public:
		Matrix(int r=2, int c=2):rows(r),columns(c)
		{
			data.resize(r);
			for(int i=0; i<r;++i)
			{
				data[i].resize(c);
			}
		}
		
		//****SETTERS AND GETTERS
		int getRows()const
		{
			return rows;
		}
		int getColumns()const
		{
			return columns;
		}
		void setRows(int r)
		{
			rows=r;
		}
		void setColumns(int c)
		{
			columns=c;
		}
		void matrixResize(int r, int c)
		{
			setRows(r);
			setColumns(c);
			data.resize(r);
			for(int i=0; i<r;++i)
			{
				data[i].resize(c);
			}
		}
		//******OVERLOADED OPERATORS*******
		/*!\brief Fills matrix with value in all entries
		 */
		Matrix& operator=(T value)
		{
			for(int i=0;i<rows;++i)
			{
				for(int j=0;j<columns;++j)
				{
					data[i][j]=value;
				}
			}
			return (*this);
		}
		Matrix operator+(const Matrix& m)
		{
			Matrix m1(m.getRows(), m.getColumns());
			for(int i=0;i<rows;++i)
			{
				for(int j=0;j<columns;++j)
				{
					m1.data[i][j]=(*this).data[i][j]+m.data[i][j];
				}
			}
			return m1;
		}
		Matrix& operator+=(const Matrix& m)
		{
			for(int i=0;i<rows;++i)
			{
				for(int j=0;j<columns;++j)
				{
					data[i][j]+=m.data[i][j];
				}
			}
			return (*this);
		}
		Matrix operator-(const Matrix& m)
		{
			Matrix m1(m.getRows(), m.getColumns());
			for(int i=0;i<rows;++i)
			{
				for(int j=0;j<columns;++j)
				{
					m1.data[i][j]=(*this).data[i][j]-m.data[i][j];
				}
			}
			return m1;
		}
		Matrix& operator-=(const Matrix& m)
		{
			for(int i=0;i<rows;++i)
			{
				for(int j=0;j<columns;++j)
				{
					data[i][j]-=m.data[i][j];
				}
			}
			return (*this);
		}
		/*!\brief MATRIX-MATRIX multiplication
		 */
		Matrix operator*(const Matrix& m)
		{
			gemm_dimensions_check(this, &m);
			Matrix m1(this->getRows(), m.getColumns());
			for(int i=0;i<m1.rows;++i)
			{
				for(int j=0;j<m1.columns;++j)
				{
					for(int k=0;k<m.getRows();++k)
					{
						m1.data[i][j]+=(*this).data[i][k]*m.data[k][j];
					}
					
				}
			}
			
			return m1;
			
		}
		/*!\brief MATRIX-MATRIX multiplication
		 */
		Matrix& operator*=(const Matrix& m)
		{
			gemm_dimensions_check(this, &m);
			Matrix m1(this->getRows(), m.getColumns());
			
			for(int i=0;i<m1.rows;++i)
			{
				for(int j=0;j<m1.columns;++j)
				{
					for(int k=0;k<m.getRows();++k)
					{
						m1.data[i][j]+=(*this).data[i][k]*m.data[k][j];
					}
					
				}
			}
			(*this)=m1;
			return (*this);
			
		}
		/*!\brief MATRIX-SCALAR multiplication
		 */
		Matrix& operator*=(double scalar)
		{
			for(int i=0;i<rows;++i)
			{
				for(int j=0;j<columns;++j)
				{
					data[i][j]*=scalar;
				}
			}
			return (*this);
		}
		/*!\brief MATRIX-VECTOR multiplication
		 */
		Vector<T> operator*(const Vector<T>& v)
		{
			gemv_dimensions_check(this, &v);
			Vector<T> v1((*this).getRows());
			for(int i=0;i<rows;++i)
			{
				for(int j=0;j<columns;++j)
				{
					v1[i]+=data[i][j]*v[j];
				}
			}
			return v1;
		}
		/*!\brief TRANSPOSE of the matrix, customised operator
		 */
		Matrix operator~()
		{
			Matrix m(columns, rows);
			for(int i=0;i<rows;++i)
			{
				for(int j=0;j<columns;++j)
				{
				m.data[j][i]=data[i][j];
				}
			}
			return m;
		}
		/*!\brief Equivalent to getElement(i,j)
		 */
		T operator()(int r, int c)const
		{
			if(r>=rows || c>=columns)
				std::cout<<"Out of bounds index\n";
			return data[r][c];
		}
		/*!\brief Mutable function for a matrix entry
		 *Function enables us to access an entry of the matrix and modiy with any value T
		 *@param[in] r,c indices of the entry
		 *@param[out] T& non-constant reference to the entry, modifiable by reference
		 */
		T & operator()(int r, int c)
		{
			if(r>=rows || c>=columns)
				std::cout<<"Out of bounds index\n";
			return data[r][c];
		}
		

	private:
		/*!\brief General Matrix-Matrix multiplication dimensions check, for performing m3=m*m2
		 *
		 *@param[in] m should be this pointer (left-side element)
		 *@param[out] m2 the other matrix
		 */
		bool gemm_dimensions_check(const Matrix<T>* m, const Matrix<T>* m2)
		{
			if(m->getColumns()==m2->getRows())
			{
				return true;
			}
			else
			{
				std::cout<<"\nDimension mismatch this GEMM operation will fail\n";
				return false;
			}
		}
		/*!\brief General Matrix-Vector multiplication dimensions check, for performing v2=m*v, or f=Au
		 *
		 *@param[in] m should be this pointer (left-side element)
		 *@param[out] v vector for multiplication
		 */
		bool gemv_dimensions_check(const Matrix<T>* m, const Vector<T>* v)
		{
			if(m->getColumns()==v->size())
				return true;
			else
			{
				std::cout<<"\nDimension mismatch this GEMV operation will fail\n";
				return false;
			}
		}
	protected:
		int rows;
		int columns;
		std::vector<std::vector<T>> data;/**<Elements of the matrix, vector of vectors of type T*/
};
template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T> m)
{
	out<<"\n";
	for(int i=0; i<m.getRows();i++)
	{
		for(int j=0;j<m.getColumns();j++)
		{
			out<<std::setprecision(3)<<std::setw(10)<<std::right;
			out<<m(i,j)<<"   ";
		}
		out<<"\n";
	}
	return out;
}
#endif