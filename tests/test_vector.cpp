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

bool test_vector_construction()
{
	ft::vector<int> empty;
	// ft::vector<int, > emptyCstmAlloc;
	ft::vector<int> init(4, 21);

	empty.push_back(5);
	empty.push_back(35);

	ft::vector<int> iter(empty.begin(), empty.end());
	ft::vector<int> copy(init);

#ifdef DEBUG
	std::cout << "size() of empty = " << empty.size() << std::endl;
	std::cout << "size() of init = " << init.size() << std::endl;
	std::cout << "size() of copy = " << copy.size() << std::endl;
	std::cout << "empty " << empty << std::endl;
	std::cout << "init " << init << std::endl;
	std::cout << "iter " << iter << std::endl;
	std::cout << "copy " << copy << std::endl;
#endif
	return true;
}

bool test_vector()
{
	bool success = true;

	std::cout << "-- Test vector --" << std::endl;
	debug::run_test("vector construction", test_vector_construction);
	// debug::run_test("pair swap", test_swap);
	// debug::run_test("relational operators", test_relational_operators);
	return success;
}
