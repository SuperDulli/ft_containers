#ifndef UTILITY_HPP
#define UTILITY_HPP

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace ft
{

// not needed
template<typename T>
void swap(T& a, T& b)
{
	T tmp(a);
	a = b;
	b = tmp;
}

// // needed as base clas for is integral?
// template <class T, T v>
// struct integral_constant;

// template <typename T>
// struct is_integral
// {

// public:
// 	static const bool value;

// 	bool operator bool()

// };

} // namespace ft

#endif // UTILITY_HPP

