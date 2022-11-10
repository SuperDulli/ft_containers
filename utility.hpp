#ifndef UTILITY_HPP
#define UTILITY_HPP

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <functional> // unary function

namespace ft
{

// useful for the tree in map & set

template <class T>
struct Identity : public std::unary_function<T, T>
{
	T& operator()(T& x) const
	{
		return x;
	}

	const T& operator()(const T& x) const
	{
		return x;
	}
};

template <class Pair>
struct SelectFirst : public std::unary_function<Pair, typename Pair::first_type>
{
	typename Pair::first_type& operator()(Pair& x) const
	{
		return x.first;
	}

	const typename Pair::first_type& operator()(const Pair& x) const
	{
		return x.first;
	}
};

} // namespace ft

#endif // UTILITY_HPP
