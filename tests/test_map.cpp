#include <iomanip>
#include <iostream>
#include <string>

#include <vector> // for getting iterators

#include "../debug_utility.hpp"

#ifdef USE_STL // CREATE A REAL STL EXAMPLE
#include <map>
namespace ft = std;
#else
#include "../map.hpp"
#endif

namespace test_map
{
	using ::operator<<; // use operators from the gloabal namespace

bool construction()
{
	bool result = true;

	// default
	ft::map<int, int> empty;
	result = result && empty.empty() && empty.size() == 0;

	// range
	const int count = 20;
	int		  ints[] = {99, 8, 28, 45, 33, 22, 99, 50, 97, 8,
						48, 7, 31, 48, 78, 87, 27, 31, 4,  79};
	ft::vector< ft::pair<int, int> > number_pairs;
	for (size_t i = 0; i < count; i++)
	{
		number_pairs.push_back(ft::make_pair(ints[i], i));
	}
	ft::map<int, int> range(number_pairs.begin(), number_pairs.end());
	result = result && !range.empty() && range.size() != 0;

	// TODO: empty with custom compare and/or allocator
	// TODO: complex objects

	ft::map<int, int> empty_copy(empty);
	result = result && empty_copy == empty;

	ft::map<int, int> copy(range);
	result = result && copy == range;

	return result;
}

bool insert()
{
	bool result = true;

	ft::map<int, int> empty;

	empty.insert(ft::make_pair(120, 0));
	empty.insert(ft::make_pair(7, 0));
	empty.insert(ft::make_pair(3, 0));
	empty.insert(ft::make_pair(15, 0));
	empty.insert(ft::make_pair(16, 0));
	empty.insert(ft::make_pair(14, 0));
	empty.insert(ft::make_pair(200, 0));
	empty.insert(ft::make_pair(150, 0));
	empty.insert(ft::make_pair(250, 0));

#if defined(DEBUG) && !defined(USE_STL)
	// std::cout << empty.m_tree << std::endl;
#endif

	return result;
}

bool all()
{
	bool success = true;

	std::cout << "-- Test map --" << std::endl;
	debug::run_test("map construction", test_map::construction);
	debug::run_test("map insert", test_map::insert);

	// debug::run_test("relational operators", test_relational_operators);
	return success;
}
} // namespace test_map
