#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>

template < typename T>
class Array {
public:
	Array<T>(); // creates an empty array
	Array<T>(Array<T> const & src);
	Array<T>(unsigned int n);  // creates an array of n elements, initialized by default. 
	virtual ~Array<T>(void);

	Array & operator=( Array const & rhs);
	T & operator[](unsigned int i);

	// When accessing an element with the operator[], if this element is out of the limits, a std::exception is thrown.

	unsigned int size() const; // 
private :
	T * datas;
	unsigned int _size;
};


template < typename T>
Array<T>::Array(void)
{
	datas = new T[0];
}

template < typename T>
Array<T>::Array(unsigned int n)
{
	datas = new T[n];
	_size = n;
}

template < typename T>
Array<T>::Array(Array<T> const & src) {
	*this = src;
}

template < typename T>
Array<T>::~Array<T>(void)
{

}

template < typename T>
Array<T> & Array<T>::operator=( Array<T> const & rhs) {
	datas = rhs.datas;
	_size = rhs.size;
}

template < typename T>
T & Array<T>::operator[](unsigned int i) {
	if (i >= _size)
		throw std::exception();
	return datas[i];
}

template < typename T>
unsigned int Array<T>::size() const
{
	return _size;
}

#endif