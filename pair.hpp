#ifndef PAIR_HPP
#define PAIR_HPP

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace ft
{

template <class T1, class T2>
struct pair {
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	// constructors

	pair() : first(), second()
	{
#ifdef DEBUG
		// std::cout << "pair constructor (default)" << std::endl;
#endif
	}

	template <class U, class V>
	pair(const ft::pair<U, V>& other)
		: first(other.first),
		  second(other.second){
#ifdef DEBUG
	// std::cout << "pair constructor (copy template)" << std::endl;
#endif
		  }

		  pair(const ft::pair<T1, T2>& other)
		: first(other.first),
		  second(other.second){
#ifdef DEBUG
	// std::cout << "pair constructor (copy)" << std::endl;
#endif
		  }

		  pair(const first_type& a, const second_type& b)
		: first(a),
		  second(b){
#ifdef DEBUG
	// std::cout << "pair constructor (initialization)" << std::endl;
#endif
		  }

			  // public member function

			  pair
			  & operator=(const pair& other)
	{
#ifdef DEBUG
		std::cout << "pair copy assignment operator" << std::endl;
#endif
		first = other.first;
		second = other.second;
		return *this;
	}

	// swap is c++11
	// void swap(pair& other)
	// {
	// 	ft::swap(first, other.first);
	// 	ft::swap(second, other.second);
	// }
};

template <class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y)
{
	return (pair<T1, T2>(x, y));
}

// relational operators

template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return lhs.first < rhs.first ||
		   (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return rhs < lhs;
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return !(lhs < rhs);
}

} // namespace ft

#endif // PAIR_HPP
