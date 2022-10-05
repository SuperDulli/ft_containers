#include <iostream>
#include <string>
#include <iomanip>

#include "../debug_utility.hpp"

#ifdef USE_STL	   // CREATE A REAL STL EXAMPLE
#include <vector>
namespace ft = std;
#else
#include "../vector.hpp"
#endif

bool test_construction()
{
	ft::vector<int> empty;
	// ft::vector<int, > emptyCstmAlloc;
	ft::vector<int> init(4, 21);
	// ft::vector<int> iter(init.begin(), init.end());
	ft::vector<int> copy(init);

#ifdef DEBUG
	// std::cout << empty.si
#endif
	return true;
}

bool test_vector()
{
	bool success = true;

	std::cout << "-- Test vector --" << std::endl;
	debug::run_test("vector construction", test_construction);
	// debug::run_test("pair swap", test_swap);
	// debug::run_test("relational operators", test_relational_operators);
	return success;
}
