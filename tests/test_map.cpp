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

bool all()
{
	bool success = true;

	std::cout << "-- Test map --" << std::endl;
	debug::run_test("map construction", test_map::construction);

	// debug::run_test("relational operators", test_relational_operators);
	return success;
}
} // namespace test_map
