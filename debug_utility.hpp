#ifndef DEBUG_UTILITY_HPP
#define DEBUG_UTILITY_HPP

#ifdef USE_STL // CREATE A REAL STL EXAMPLE
#include <utility>
#include <vector>
namespace ft = std;
#else
#include "pair.hpp"
#include "vector.hpp"
#endif

#include "Color.hpp"
#include <iostream>
#include <string>

namespace debug
{

bool run_test(const std::string& name, bool (*test_f)(void));
void test_result(const std::string& name, bool result);

} // namespace debug

template <typename U, typename V>
std::ostream& operator<<(std::ostream& os, const ft::pair<U, V>& pair)
{
	os << "pair(" << pair.first << ", " << pair.second << ")";
	return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ft::vector<T>& vec)
{
	os << "vector(capacity=" << vec.capacity() << ", size=" << vec.size()
	//    << ", front=" << vec.front()
	  << ")" << std::endl;

	if (vec.size())
	{
		typename ft::vector<T>::const_iterator it;
		// typename ft::vector<T>::iterator it; // TODO: why not this?
		for (it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
	}
	return os;
}

#endif // DEBUG_UTILITY_HPP
