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

	int				intArray[] = {1, 2, 3, 4};
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

bool test_vector_assign()
{
	ft::vector<char>	   chars;
	ft::vector<char>	   chars2;
	ft::vector<char>	   chars3;
	ft::vector<char>	   chars4;
	const ft::vector<char> extra(6, 'b');

	chars.assign(5, 'a');
#ifdef DEBUG
	std::cout << "chars " << chars << std::endl;
#endif

	chars2.assign(extra.begin(), extra.end());
#ifdef DEBUG
	std::cout << "chars2 " << chars2 << std::endl;
#endif

	std::cout << "first extend capacity, then assign" << std::endl;

	chars3.reserve(15);
	chars3.assign(3, 'c');
#ifdef DEBUG
	std::cout << "chars3 " << chars3 << std::endl;
#endif

	chars4.reserve(10);
	chars4.assign(extra.begin(), extra.end());
#ifdef DEBUG
	std::cout << "chars4 " << chars4 << std::endl;
#endif
	return (
		chars.size() == 5 && chars2 == extra && chars3.size() == 3 &&
		chars4 == extra);
}

bool test_vector_capacity()
{
	bool result;

	ft::vector<int>			ints;
	ft::vector<char>		chars;
	ft::vector<std::string> strings;
	ft::vector<int>			large(20, 5);

	result = ints.empty() == true && ints.size() == 0 &&
			 chars.empty() == true && chars.size() == 0 &&
			 strings.empty() == true && strings.size() == 0 &&
			 large.empty() == false && large.size() == 20;
#ifdef DEBUG
	std::cout << "ints " << ints << std::endl;
	std::cout << "chars " << chars << std::endl;
	std::cout << "strings " << strings << std::endl;
	std::cout << "large " << large << std::endl;
#endif

	unsigned size = 100;
	unsigned cap = ints.capacity();
#ifdef DEBUG
	std::cout << "Initial size: " << ints.size() << ", capacity: " << cap
			  << std::endl;
	std::cout << "\nDemonstrate the capacity's growth policy."
				 "\nSize:  Capacity:  Ratio:"
			  << std::left << std::endl;
#endif
	unsigned i = size;
	while (i-- > 0)
	{
		ints.push_back(i);
		if (cap != ints.capacity())
		{
#ifdef DEBUG
			std::cout << std::setw(7) << ints.size() << std::setw(11)
					  << ints.capacity() << std::setw(10)
					  << ints.capacity() / static_cast<float>(cap) << std::endl;
#endif
			cap = ints.capacity();
		}
	}
#ifdef DEBUG
	std::cout << "\nFinal size: " << ints.size()
			  << ", capacity: " << ints.capacity() << std::endl;
#endif
	result = result && ints.size() == size && ints.capacity() > size;

#ifdef DEBUG
	std::cout << "Try to reserve more than max size and catch exeption" << std::endl;
#endif
	bool exceptionThrown = false;
	try
	{
		unsigned long newCap = strings.max_size();
		newCap += 10;
#ifdef DEBUG
	std::cout << "max_size:\n" << strings.max_size() << std::endl;
	std::cout << "newCap:\n" << newCap << std::endl;
#endif
		strings.reserve(newCap);
	}
	catch(const std::length_error& e)
	{
		exceptionThrown = true;
		std::cerr << e.what() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
#ifdef DEBUG
	std::cout << "strings " << strings << std::endl;
#endif
	result = result && exceptionThrown && strings.capacity() == 0;

#ifdef DEBUG
	std::cout << "use reserve() to expand capacity" << std::endl;
#endif
	chars.reserve(5);
	#ifdef DEBUG
	std::cout << "chars " << chars << std::endl;
#endif
	result = result && chars.capacity() == 5;

	return result;
}

bool test_vector()
{
	bool success = true;

	std::cout << "-- Test vector --" << std::endl;
	debug::run_test("vector construction", test_vector_construction);
	debug::run_test("vector copy", test_vector_copy);
	debug::run_test("vector assign", test_vector_assign);
	debug::run_test("vector capacity", test_vector_capacity);
	// debug::run_test("relational operators", test_relational_operators);
	return success;
}
