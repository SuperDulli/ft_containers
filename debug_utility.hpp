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

#include <stdlib.h> // rand
#include <time.h>

#include "Color.hpp"
#include <iostream>
#include <string>

namespace debug
{

bool run_test(const std::string& name, bool (*test_f)(void));
void test_result(const std::string& name, bool result);
template <class C>
void insert_random(C& container, size_t count);

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
	os << "vector(capacity=" << vec.capacity() << ", size="
	   << vec.size()
	   //    << ", front=" << vec.front()
	   << ", max_size=" << vec.max_size() << ")" << std::endl;

	if (vec.size())
	{
		typename ft::vector<T>::const_iterator it;
		// typename ft::vector<T>::iterator it; // TODO: why not this?
		for (it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << ", ";
		}
	}
	return os;
}

template <typename InputIterator>
void printIterValues(InputIterator first, InputIterator last)
{
	while (first != last)
	{
		std::cout << *first << ", ";
		++first;
	}
	std::cout << std::endl;
}

template <class C>
void debug::insert_random(C& container, size_t count)
{
	ft::vector<int> ints;
	for (size_t i = 0; i < count; i++)
	{
	int rand_number = rand() % 100;
		container.insert(rand_number);
		ints.push_back(rand_number);
	}

	std::cout << "inserted: " << ints << std::endl;

}

#endif // DEBUG_UTILITY_HPP
