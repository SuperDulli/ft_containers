#ifndef DEBUG_UTILITY_HPP
#define DEBUG_UTILITY_HPP

#ifdef USE_STL //CREATE A REAL STL EXAMPLE
	#include <utility>
	namespace ft = std;
#else
	#include "pair.hpp"
#endif

#include <iostream>
#include <string>
#include "Color.hpp"

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

#endif // DEBUG_UTILITY_HPP
