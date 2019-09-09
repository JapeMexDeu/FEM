#include"Vector.h"

template<typename T>
Vector<T>::Vector(std::size_t sz)
{
	resize(sz);
}

template<typename T>
Vector<T>::Vector(int sz)
{
	resize(sz);
}

//*****OPERATOR OVERLOADS******
template<typename T>
Vector<T>& Vector<T>::operator+(const Vector<T>& v)
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
template<typename T>
Vector<T>& Vector<T>::operator-(const Vector<T>& v)
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
template<typename T>
std::ostream &operator<<(std::ostream& out, const Vector<T>& v)
{
	if(v.empty())
	{
		out<<"\n()\n";
	}
	else
	{
		out<<"\n(";
		for(std::size_t i=0;i<v.size()-1;++i)
		{
			out<<v[i]<<" ";
		}
		out<<")\n";
	}
	return out;
}