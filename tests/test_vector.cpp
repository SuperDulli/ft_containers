#include <iomanip>
#include <iostream>
#include <string>

#include "../debug_utility.hpp"

#ifdef USE_STL // CREATE A REAL STL EXAMPLE
#include <vector>
namespace ft = std;
#else
#include "../vector.hpp"
#endif

bool test_vector_construction()
{
	ft::vector<int> empty;
	ft::vector<int> intVec;
	// ft::vector<int, > emptyCstmAlloc;
	ft::vector<int> init(4, 21);

	std::string		 s("Hello World!");
	ft::vector<char> charVec(s.begin(), s.end());

	intVec.push_back(5);
	intVec.push_back(35);

	ft::vector<int> iter(intVec.begin(), intVec.end());
	ft::vector<int> copy(init);

#ifdef DEBUG
	std::cout << "empty " << empty << std::endl;
	std::cout << "intVec " << intVec << std::endl;
	std::cout << "init " << init << std::endl;
	std::cout << "charVec " << charVec << std::endl;
	std::cout << "iter " << iter << std::endl;
	std::cout << "copy " << copy << std::endl;
#endif
	return (
		empty.size() == 0 && intVec.size() == 2 &&
		charVec.size() == s.length() && iter.size() == intVec.size() &&
		copy.size() == init.size());
}

bool test_vector_copy()
{
	bool result;

	int intArray[] = {1, 2, 3, 4};
	ft::vector<int> x(intArray, intArray + 4);
	ft::vector<int> y;

#if DEBUG
	std::cout << "before assignment:" << std::endl;
	std::cout << "x " << x << std::endl;
	std::cout << "y " << y << std::endl;
#endif
#if DEBUG
	std::cout << "try self assignment:" << std::endl;
#endif
	x = x; // should not copy anything
	y = x;
	result = y == x;
	x[2] = 0;
#if DEBUG
	std::cout << "after assignment (and change to x):" << std::endl;
	std::cout << "x " << x << std::endl;
	std::cout << "y " << y << std::endl;
#endif

	return result && y != x;
}



bool test_vector()
{
	bool success = true;

	std::cout << "-- Test vector --" << std::endl;
	debug::run_test("vector construction", test_vector_construction);
	debug::run_test("vector copy", test_vector_copy);
	// debug::run_test("relational operators", test_relational_operators);
	return success;
}
