#include <iomanip>
#include <iostream>
#include <string>

#include <functional> // less

#include "../debug_utility.hpp"

#include "../tree.hpp"
// #ifdef USE_STL // CREATE A REAL STL EXAMPLE
// #include <map>
// namespace ft = std;
// #else
// #include "../tree.hpp"
// #endif


namespace test_tree
{
bool construction()
{
	bool result = true;

	RB_tree<int, int, std::less<int> > empty;

	return result;
}

bool insert()
{
	bool result = true;

	RB_tree<int, ft::pair<int, int>, std::less<int> > empty;

	empty.insert(ft::make_pair<int, int>(3, 42));

	return result;
}

bool all()
{
	bool success = true;

	std::cout << "-- Test Red-Black tree --" << std::endl;
	debug::run_test("tree construction", test_tree::construction);
	debug::run_test("tree insert", test_tree::insert);

	// debug::run_test("relational operators", test_relational_operators);
	return success;
}
} // namespace test_map
