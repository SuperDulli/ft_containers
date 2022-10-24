#include <iomanip>
#include <iostream>
#include <string>

#include "../debug_utility.hpp"

#ifdef USE_STL // CREATE A REAL STL EXAMPLE
#include <map>
namespace ft = std;
#else
#include "../map.hpp"
#endif

namespace test_map
{
bool construction()
{
	bool result = true;

	ft::map<int, int> empty;

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
	std::cout << empty.m_tree << std::endl;
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
