#ifndef DEBUG_UTILITY_HPP
#define DEBUG_UTILITY_HPP

#ifdef USE_STL // CREATE A REAL STL EXAMPLE
#include <map>
#include <set>
#include <stack>
#include <utility>
#include <vector>
namespace ft = std;
#else
#include "map.hpp"
#include "pair.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "vector.hpp"
#endif

#include <stdlib.h> // rand
#include <ctime> // clock, time (for seed)

#include "Color.hpp"
#include <iostream>
#include <string>

namespace debug
{

bool run_test(const std::string& name, bool (*test_f)(void));
void test_result(const std::string& name, bool result);
template <class C>
void insert_random(C& container, size_t count);
template <class C>
void insert_random_pair(C& container, size_t count);
template <class C>
void insert_sorted(C& container, size_t count);
template <class C>
void insert_sorted_pair(C& container, size_t count);
template <class Iterator>
bool insertion_status(Iterator it, bool success);

} // namespace debug

template <typename U, typename V>
std::ostream& operator<<(std::ostream& os, const ft::pair<U, V>& pair)
{
	os << "pair(" << pair.first << ", " << pair.second << ")";
	return os;
}

template <typename U, typename V>
std::ostream& operator<<(std::ostream& os, const ft::pair<const U, V>& pair)
{
	os << "pair(" << pair.first << ", " << pair.second << ")";
	return os;
}

template <typename U, typename V>
std::ostream& operator<<(std::ostream& os, const ft::pair<U, const V>& pair)
{
	os << "pair(" << pair.first << ", " << pair.second << ")";
	return os;
}

template <typename U, typename V>
std::ostream&
operator<<(std::ostream& os, const ft::pair<const U, const V>& pair)
{
	os << "pair(" << pair.first << ", " << pair.second << ")";
	return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ft::vector<T>& vec)
{
	os << "vector(capacity=" << vec.capacity() << ", size=" << vec.size()
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

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const ft::map<K, V>& map)
{
	os << "map(size=" << map.size() << ", max_size=" << map.max_size() << ")"
	   << std::endl;

	if (map.empty())
	{
		os << "<empty>";
		return os;
	}
	for (typename ft::map<K, V>::const_iterator it = map.begin();
		 it != map.end();
		 ++it)
	{
		os << "[" << it->first << "]=" << it->second << ", ";
	}
	return os;
}

template <typename K>
std::ostream& operator<<(std::ostream& os, const ft::set<K>& set)
{
	os << "set(size=" << set.size() << ", max_size=" << set.max_size() << ")"
	   << std::endl;

	if (set.empty())
	{
		os << "<empty>";
		return os;
	}
	for (typename ft::set<K>::const_iterator it = set.begin(); it != set.end();
		 ++it)
	{
		os << *it << ", ";
	}
	return os;
}

template <typename T, typename Container>
std::ostream& operator<<(std::ostream& os, const ft::stack<T, Container>& stack)
{
	ft::stack<T, Container> copy(stack);
	os << "stack(size=" << stack.size() << ")" << std::endl;

	if (stack.empty())
	{
		os << "<empty>";
		return os;
	}
	os << "top -> ";
	while (!copy.empty())
	{
		os << copy.top() << ", ";
		copy.pop();
	}
	return os;
}

template <class C>
void printIterName(const C& container, typename C::const_iterator it)
{
	if (it == container.end())
		std::cout << "end()";
	else if (it == container.begin())
		std::cout << "begin()";
	else
		std::cout << *it;
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

template <class C>
void debug::insert_random_pair(C& container, size_t count)
{
	ft::vector< ft::pair<int, int> > pairs;
	for (size_t i = 0; i < count; i++)
	{
		int rand_number = rand() % 100;
		container.insert(ft::make_pair(rand_number, i));
		pairs.push_back(ft::make_pair(rand_number, i));
	}

	std::cout << "inserted: " << pairs << std::endl;
}

template <class C>
void debug::insert_sorted(C& container, size_t count)
{
	ft::vector<int> ints;
	for (size_t i = 0; i < count; i++)
	{
		container.insert(i);
		ints.push_back(i);
	}

	std::cout << "inserted: " << ints << std::endl;
}

template <class C>
void debug::insert_sorted_pair(C& container, size_t count)
{
	ft::vector< ft::pair<int, int> > pairs;
	for (size_t i = 0; i < count; i++)
	{
		container.insert(ft::make_pair(i, 0));
		pairs.push_back(ft::make_pair(i, 0));
	}

	std::cout << "inserted: " << pairs << std::endl;
}

template <class Iterator>
bool debug::insertion_status(Iterator it, bool success)
{
	(void) it;
#ifdef DEBUG
	std::cout << "insertion of " << *it << (success ? " succeded" : " failed")
			  << std::endl;
#endif
	return success;
}

#endif // DEBUG_UTILITY_HPP
