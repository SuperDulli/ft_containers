#ifndef UTILITY_HPP
#define UTILITY_HPP

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace ft
{

template<typename T>
void swap(T& a, T& b)
{
	T tmp(a);
	a = b;
	b = tmp;
}

} // namespace ft

#endif // UTILITY_HPP

