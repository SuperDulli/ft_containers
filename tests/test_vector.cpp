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

namespace test_vector
{
bool construction()
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

bool copy()
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

bool assign()
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

bool capacity()
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
	std::cout << "Try to reserve more than max size and catch exeption"
			  << std::endl;
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
	} catch (const std::length_error& e)
	{
		exceptionThrown = true;
		std::cerr << e.what() << std::endl;
	} catch (const std::exception& e)
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

bool data()
{
	bool result;

	ft::vector<int> ints;

	const int count = 4;
	for (int i = 0; i < count; i++)
	{
		ints.push_back(i);
	}

	const int* pointer = ints.data();
#ifdef DEBUG
	std::cout << "Demonstrate that the elements stored contiguously:"
			  << std::endl;
	for (size_t i = 0; i < ints.size(); ++i)
		std::cout << (pointer + i) << ": " << pointer[i] << std::endl;
	std::cout << std::endl;
#endif
	result = true;
	for (size_t i = 0; i < ints.size(); i++, pointer++)
	{
		result = result && *pointer == static_cast<int>(i);
	}
	result = result && ints.front() == 0 && ints.back() == count - 1;

	return result;
}

bool reverse_iteration()
{
	bool					result = true;
	const int				ints[] = {1, 2, 4, 8, 16};
	ft::vector<int>			nums(ints, ints + 5);
	const std::string		strings[] = {"orange", "apple", "raspberry"};
	ft::vector<std::string> fruits(strings, strings + 3);
	ft::vector<char>		empty;

#ifdef DEBUG
	std::cout << "reverse of nums:" << std::endl;
#endif
	int i = 0;
	for (ft::vector<int>::reverse_iterator rit = nums.rbegin();
		 rit != nums.rend();
		 ++rit)
	{
#ifdef DEBUG
		std::cout << *rit << " ";
#endif
		*rit = ++i;
	}
	std::cout << std::endl;
#ifdef DEBUG
	std::cout << "nums " << nums << std::endl;
#endif
	result = result && *nums.rbegin() == 1;

#ifdef DEBUG
	std::cout << "reverse of fruits:" << std::endl;
#endif
	for (ft::vector<std::string>::reverse_iterator rit = fruits.rbegin();
		 rit != fruits.rend();
		 ++rit)
	{
#ifdef DEBUG
		std::cout << *rit << " ";
#endif
	}
	std::cout << std::endl;
	result = result && *fruits.rbegin() == "raspberry";

	if (empty.rbegin() == empty.rend())
	{
#ifdef DEBUG
		std::cout << "vector 'empty' is indeed empty." << std::endl;
#endif
	}
	result = result && empty.rbegin() == empty.rend();

	return result;
}

bool clear()
{
	bool result = true;

	ft::vector<int>			ints(5, 0);
	ft::vector<std::string> empty;

#ifdef DEBUG
	std::cout << "ints " << ints << std::endl;
	std::cout << "empty " << empty << std::endl;
#endif

	ints.clear();
	empty.reserve(7);
	empty.clear();

#ifdef DEBUG
	std::cout << "ints " << ints << std::endl;
	std::cout << "empty " << empty << std::endl;
#endif
	result = result && ints.size() == 0 && ints.capacity() == 5;
	result = result && empty.size() == 0 && empty.capacity() == 7;

	return result;
}

bool insert()
{
	bool result = true;

	const int				ints[] = {1, 2, 3, 4, 5};
	ft::vector<int>			nums(ints, ints + 5);
	ft::vector<std::string> empty;
	const std::string		strings[] = {
			  "orange",
			  "apple",
			  "raspberry",
			  "bananna",
			  "mango",
			  "kiwi",
			  "strawberry"};
	ft::vector<std::string> fruits(strings, strings + 7);

	ft::vector<int> numbers(3, 42);

	// makes sure the iterators in the next line stay valid, else it would be UB
	numbers.reserve(numbers.capacity() + numbers.size());

	numbers.insert(numbers.end(), numbers.begin(), numbers.end());

#ifdef DEBUG
	std::cout << "nums " << nums << std::endl;
	std::cout << "numbers " << numbers << std::endl;
	std::cout << "empty " << empty << std::endl;
#endif

	// ft::vector<int>::const_iterator cit = nums.begin();

	// insert one value at a time
	nums.insert(nums.begin(), -1);
	nums.insert(nums.begin() + 3, -2);
	nums.insert(nums.end(), -3);

	// insert multiple copies at once
	empty.insert(empty.begin(), 2, "hi");

	#ifdef DEBUG
	std::cout << "nums " << nums << std::endl;
	std::cout << "empty " << empty << std::endl;
#endif

	// insert range
	empty.insert(empty.begin() + 1, fruits.begin(), fruits.end());
	nums.insert(nums.end(), numbers.begin(), numbers.end());

#ifdef DEBUG
	std::cout << "nums " << nums << std::endl;
	std::cout << "empty " << empty << std::endl;
#endif

	return result;
}

bool all()
{
	bool success = true;

	std::cout << "-- Test vector --" << std::endl;
	debug::run_test("vector construction", test_vector::construction);
	debug::run_test("vector copy", test_vector::copy);
	debug::run_test("vector assign", test_vector::assign);
	debug::run_test("vector capacity", test_vector::capacity);
	debug::run_test("vector data", test_vector::data);
	debug::run_test("vector reverse_iteration", test_vector::reverse_iteration);
	debug::run_test("vector clear", test_vector::clear);
	debug::run_test("vector insert", test_vector::insert);
	// debug::run_test("relational operators", test_relational_operators);
	return success;
}
} // namespace test_vector
