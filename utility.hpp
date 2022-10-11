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
	static const T value = v;

	typedef T						value_type;
	typedef integral_constant<T, v> type;

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
// long long is not c++ 98

// const variants
template <>
struct is_integral<const bool> : integral_constant<bool, true> {};
template <>
struct is_integral<const char> : integral_constant<bool, true> {};
template <>
struct is_integral<const signed char> : integral_constant<bool, true> {};
template <>
struct is_integral<const unsigned char> : integral_constant<bool, true> {};
template <>
struct is_integral<const wchar_t> : integral_constant<bool, true> {};
template <>
struct is_integral<const short> : integral_constant<bool, true> {};
template <>
struct is_integral<const unsigned short> : integral_constant<bool, true> {};
template <>
struct is_integral<const int> : integral_constant<bool, true> {};
template <>
struct is_integral<const unsigned int> : integral_constant<bool, true> {};
template <>
struct is_integral<const long> : integral_constant<bool, true> {};
template <>
struct is_integral<const unsigned long> : integral_constant<bool, true> {};

// enable if

template <bool B, class T = void>
struct enable_if;
template <class T>
struct enable_if<true, T> {
	typedef T type
};

} // namespace ft

#endif // UTILITY_HPP
