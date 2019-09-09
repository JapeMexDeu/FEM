/**
  FILE: Vector.h
  
  AUTHOR: J Alfonso P Escobar
  
  DESCRIPTION: derived class from STL vector, provides vector functionalities. TEMPLATE CLASS. Overloaded operators only work with numerical types.
			   
*/

#ifndef VECTOR_H
#define VECTOR_H

#include<vector>
#include<iostream>
#include<ctime>
#include<cmath>



template<typename T>
class Vector:public std::vector<T>
{
	//bring from std::vector
	public:
		using std::vector<T>::vector;
		using std::vector<T>::resize;
		using std::vector<T>::size;
		using std::vector<T>::operator[];
		using std::vector<T>::empty;
		using std::vector<T>::begin;
    	using std::vector<T>::end;
    	using std::vector<T>::clear;
	public:
		//typedef T vector_type;
		
	public:
		Vector(std::size_t sz=0)
		{
			resize(sz);
		}
		/* Vector(int sz=1)
		{
			resize(sz);
		} */
		/*!\brief Performs a quick random fill
		 */
		void random()
		{
			std::srand(time(0));
			std::size_t s=size();
			for(std::size_t i=0;i<size();++i)
			{
				operator[](i)=std::rand()%10;
			}
		}
		/*!\brief Euclidean norm
		 */
		double norm()
		{
			if(empty())
			{
				return 0;
			}
			else
			{
				std::size_t s=size();
				double result=0;
				//Dimensions must match
				for(std::size_t i=0;i<size();++i)
				{
					result+=operator[](i)*operator[](i);
				}
				return sqrt(result);
			}
				
		}
		//***OPERATOR OVERLOAD*****
		//Vector& operator=(const Vector&);
		Vector operator+(const Vector &v)
		{
			std::size_t s=size();
			Vector new_vector(s);
			//Dimensions must match
			for(std::size_t i=0;i<size();++i)
			{
				new_vector[i]=operator[](i)+v[i];
			}
			return new_vector;
		}
		Vector& operator+=(const Vector &v)
		{
			std::size_t s=size();
			//Dimensions must match
			for(std::size_t i=0;i<size();++i)
			{
				operator[](i)+=v[i];
			}
			return *this;
		}
		Vector& operator-=(const Vector &v)
		{
			std::size_t s=size();
			//Dimensions must match
			for(std::size_t i=0;i<size();++i)
			{
				operator[](i)-=v[i];
			}
			return *this;
		}
		Vector operator-(const Vector &v)
		{
			std::size_t s=size();
			Vector new_vector(s);
			//Dimensions must match
			for(std::size_t i=0;i<size();++i)
			{
				new_vector[i]=operator[](i)-v[i];
			}
			return new_vector;
		}
		/*!\brief Vector-scalar mutiplication
		 */
		Vector& operator*=(double scalar)
		{
			std::size_t s=size();
			for(std::size_t i=0;i<size();++i)
			{
				operator[](i)*=scalar;
			}
			return *this;
		}
		/*!\brief DOT PRODUCT operation
		 */
		double operator*(const Vector &v)
		{
			std::size_t s=size();
			double result=0;
			//Dimensions must match
			for(std::size_t i=0;i<size();++i)
			{
				result+=(operator[](i)*v[i]);
			}
			return result;
		}
		/*!\brief Assignment of a value to all elements, added a posteriori
		 */
		Vector& operator=(T value)
		{
			std::size_t s=size();
			for(std::size_t i=0;i<size();++i)
			{
				operator[](i)=value;
			}
			return *this;
		}
		
		
		
};
template<typename T>
std::ostream &operator<<(std::ostream& out, const Vector<T>& v)
{
	if(v.empty())
	{
		out<<"\n()\n";
	}
	else
	{
		out<<"\n( ";
		for(std::size_t i=0;i<v.size();++i)
		{
			out<<v[i]<<" ";
		}
		out<<")\n";
	}
	return out;
}


#endif