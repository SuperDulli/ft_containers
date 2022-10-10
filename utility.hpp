#ifndef UTILITY_HPP
#define UTILITY_HPP

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace ft
{

// not needed
template <typename T>
void swap(T& a, T& b)
{
	T tmp(a);
	a = b;
	b = tmp;
}

// needed as base clas for is integral?
template <class T, T v>
struct integral_constant {
	typedef value_type				T;
	typedef integral_constant<T, v> value;

	static const T value = v;

	operator value_type() const
	{
		return value;
	}
};

// specialization of integral_constant are C++11

template <typename T>
struct is_integral : integral_constant<bool, false> {};
template <>
struct is_integral<bool> : integral_constant<bool, true> {};
template <>
struct is_integral<char> : integral_constant<bool, true> {};
template <>
struct is_integral<signed char> : integral_constant<bool, true> {};
template <>
struct is_integral<unsigned char> : integral_constant<bool, true> {};
template <>
struct is_integral<wchar_t> : integral_constant<bool, true> {};
template <>
struct is_integral<char16_t> : integral_constant<bool, true> {};
template <>
struct is_integral<char32_t> : integral_constant<bool, true> {};
template <>
struct is_integral<short> : integral_constant<bool, true> {};
template <>
struct is_integral<unsigned short> : integral_constant<bool, true> {};
template <>
struct is_integral<int> : integral_constant<bool, true> {};
template <>
struct is_integral<unsigned int> : integral_constant<bool, true> {};
template <>
struct is_integral<long> : integral_constant<bool, true> {};
template <>
struct is_integral<unsigned long> : integral_constant<bool, true> {};
template <>
struct is_integral<long long> : integral_constant<bool, true> {};
template <>
struct is_integral<unsigned long long> : integral_constant<bool, true> {};

// TODO: and const variants

} // namespace ft

#endif // UTILITY_HPP
