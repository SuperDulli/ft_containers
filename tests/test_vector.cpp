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
using ::operator<<; // use operators from the gloabal namespace

bool construction()
{
	bool result = true;

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

	ft::vector< ft::vector<int> > empty_empty_matrix;
	ft::vector< ft::vector<int> > empty_matrix(2, ft::vector<int>());
	ft::vector< ft::vector<int> > matrix(2, ft::vector<int>(3));
	ft::vector< ft::vector<int> > iter_matrix(
		2, ft::vector<int>(intVec.begin(), intVec.end()));
	ft::vector< ft::vector<int> > copy_matrix(matrix);

#ifdef DEBUG
	std::cout << "empty " << empty << std::endl;
	std::cout << "intVec " << intVec << std::endl;
	std::cout << "init " << init << std::endl;
	std::cout << "charVec " << charVec << std::endl;
	std::cout << "iter " << iter << std::endl;
	std::cout << "copy " << copy << std::endl;
	std::cout << "empty_empty_matrix " << empty_empty_matrix << std::endl;
	std::cout << "empty_matrix " << empty_matrix << std::endl;
	std::cout << "matrix " << matrix << std::endl;
	std::cout << "iter_matrix " << iter_matrix << std::endl;
	std::cout << "copy_matrix " << iter_matrix << std::endl;
#endif
	result = result && empty.empty() && empty.size() == 0;
	result = result && !intVec.empty() && intVec.size() == 2;
	result = result && !charVec.empty() && charVec.size() == s.length();
	result = result && !iter.empty() && iter.size() == intVec.size();
	result = result && copy == init;
	result =
		result && empty_empty_matrix.empty() && empty_empty_matrix.size() == 0;
	result = result && !empty_matrix.empty() && empty_matrix.size() == 2;
	result = result && empty_matrix[0].empty() && empty_matrix[0].size() == 0;
	result = result && empty_matrix[1].empty() && empty_matrix[1].size() == 0;
	result = result && !matrix.empty() && matrix.size() == 2;
	result = result && !matrix[0].empty() && matrix[0].size() == 3;
	result = result && !matrix[1].empty() && matrix[1].size() == 3;
	result = result && !iter_matrix.empty() && iter_matrix.size() == 2;
	result = result && iter_matrix[0] == intVec;
	result = result && iter_matrix[1] == intVec;
	result = result && copy_matrix == matrix;

	return result;
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
	// x = x; // should not copy anything - TODO: does not compile on Mac
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
	std::cout << "conversion and comparison iterator to const_iterator"
			  << std::endl;
#endif
	ft::vector<int>::const_iterator c_it = nums.begin();
	result = result && c_it != nums.end();

#ifdef DEBUG
	std::cout << "conversion and comparison reverse_iterator to "
				 "reverse_const_iterator"
			  << std::endl;
#endif
	ft::vector<int>::const_reverse_iterator c_rit = nums.rbegin();
	result = result && c_rit != nums.rend();

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
	ft::vector<int>			numbers(3, 42);
	ft::vector<int>			otherNumbers(2, 21);

	// return values
	ft::vector<int>::iterator		  r_one;
	ft::vector<int>::iterator		  r_multiple;
	ft::vector<int>::iterator		  r_range;
	ft::vector<int>::iterator		  r_multiple_fail;
	ft::vector<int>::iterator		  r_range_fail;
	ft::vector<std::string>::iterator r_one_string;
	ft::vector<std::string>::iterator r_multiple_string;
	ft::vector<std::string>::iterator r_range_string;
	ft::vector<std::string>::iterator r_multiple_fail_string;
	ft::vector<std::string>::iterator r_range_fail_string;

	// makes sure the iterators in the next line stay valid, else it would be UB
	// numbers.reserve(numbers.capacity() + numbers.size());
	// numbers.insert(numbers.end(), numbers.begin(), numbers.end());

#ifdef DEBUG
	std::cout << "nums " << nums << std::endl;
	std::cout << "numbers " << numbers << std::endl;
	std::cout << "empty " << empty << std::endl;
#endif

	// ft::vector<int>::const_iterator cit = nums.begin();

	// insert one value at a time
	r_one = nums.insert(nums.begin(), -1);
	result = result && *r_one == -1 && nums.front() == -1;
	r_one = nums.insert(nums.begin() + 3, -2);
	result = result && *r_one == -2 && nums.at(3) == -2;
	r_one = nums.insert(nums.end(), -3);
	result = result && *r_one == -3 && nums.back() == -3;

	// insert multiple copies at once
	r_multiple = nums.insert(nums.begin(), 3, 0);
	result = result && *r_multiple == 0 && nums.front() == 0;
	r_multiple_string = empty.insert(empty.begin(), 2, "hi");
	result = result && *r_multiple_string == "hi" && empty.front() == "hi";

	// insert 0 copies -> pos getting returned
	r_multiple_fail = nums.insert(nums.begin(), 0, 7);
	result = result && r_multiple_fail == nums.begin() && nums.front() != 7;
	r_multiple_fail_string = empty.insert(empty.begin(), 0, "nothing");
	result = result && r_multiple_fail_string == empty.begin() &&
			 empty.front() != "nothing";

#ifdef DEBUG
	std::cout << "nums " << nums << std::endl;
	std::cout << "empty " << empty << std::endl;
#endif

	// insert range
	r_range = nums.insert(nums.end(), numbers.begin(), numbers.end());
	result = result && *r_range == numbers.front() &&
			 ft::equal(r_range, nums.end(), numbers.begin());
	r_range_string =
		empty.insert(empty.begin() + 1, fruits.begin(), fruits.end());
	result = result && *r_range_string == fruits.front();

	r_range_fail =
		nums.insert(nums.end(), otherNumbers.begin(), otherNumbers.begin());
	result = result && r_range_fail == nums.end() && nums.back() == 42;
	r_range_fail_string =
		empty.insert(empty.end(), fruits.begin(), fruits.begin());
	result =
		result && r_range_fail_string == empty.end() && empty.back() == "hi";

#ifdef DEBUG
	std::cout << "nums " << nums << std::endl;
	std::cout << "empty " << empty << std::endl;
#endif

	return result;
}

bool erase()
{
	bool result = true;

	const int		  ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	ft::vector<int>	  nums(ints, ints + 9);
	const std::string strings[] = {
		"orange",
		"apple",
		"raspberry",
		"bananna",
		"mango",
		"kiwi",
		"strawberry"};
	ft::vector<std::string> fruits(strings, strings + 7);

	// return values
	ft::vector<int>::iterator		  r_one;
	ft::vector<int>::iterator		  r_one_end;
	ft::vector<int>::iterator		  r_range;
	ft::vector<int>::iterator		  r_range_end;
	ft::vector<int>::iterator		  r_range_empty;
	ft::vector<std::string>::iterator r_string_one;
	ft::vector<std::string>::iterator r_string_one_end;
	ft::vector<std::string>::iterator r_string_range;
	ft::vector<std::string>::iterator r_string_range_end;
	ft::vector<std::string>::iterator r_string_range_empty;

#ifdef DEBUG
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << std::endl;
#endif

	// erase the first and last element
	r_one = nums.erase(nums.begin());
	result = result && r_one == nums.begin();
	r_one_end = nums.erase(nums.end() - 1);
	result = result && r_one_end == nums.end();

	r_string_one = fruits.erase(fruits.begin());
	result = result && r_string_one == fruits.begin();
	r_string_one_end = fruits.erase(fruits.end() - 1);
	result = result && r_string_one_end == fruits.end();

#ifdef DEBUG
	std::cout << "After erasing the first and last element:" << std::endl;
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << std::endl;
#endif

	// try erasing empty range -> last gets returned
	r_range_empty = nums.erase(nums.begin(), nums.begin());
	result = result && r_range_empty == nums.begin();
	r_string_range_empty = fruits.erase(fruits.begin() + 2, fruits.begin() + 2);
	result = result && r_string_range_empty == fruits.begin() + 2;

#ifdef DEBUG
	std::cout << "After erasing an empty range:" << std::endl;
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << std::endl;
#endif

	r_range_end = nums.erase(nums.end() - 3, nums.end());
	result = result && r_range_end == nums.end();
	r_string_range_end = fruits.erase(fruits.end() - 1, fruits.end());
	result = result && r_string_range_end == fruits.end();

#ifdef DEBUG
	std::cout << "After erasing an range till the end:" << std::endl;
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << std::endl;
#endif

	r_range = nums.erase(nums.begin() + 1, nums.end() - 1);
	result = result && r_range == nums.begin() + 1;
	r_string_range = fruits.erase(fruits.begin() + 1, fruits.end() - 1);
	result = result && r_string_range == fruits.begin() + 1;

#ifdef DEBUG
	std::cout << "After erasing an range in the middle:" << std::endl;
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << std::endl;
#endif

	nums.erase(nums.begin(), nums.end());
	result = result && nums.size() == 0;
	fruits.erase(fruits.begin(), fruits.end());
	result = result && fruits.size() == 0;

#ifdef DEBUG
	std::cout << "After erasing everything:" << std::endl;
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << std::endl;
#endif

	return result;
}

bool pop_back()
{
	bool result = true;

	const int		  ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	ft::vector<int>	  nums(ints, ints + 9);
	const std::string strings[] = {
		"orange",
		"apple",
		"raspberry",
		"bananna",
		"mango",
		"kiwi",
		"strawberry"};
	ft::vector<std::string> fruits(strings, strings + 7);

#ifdef DEBUG
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << std::endl;
#endif

	nums.pop_back();
	result = result && nums.size() == 8;
	fruits.pop_back();
	result = result && fruits.size() == 6;

#ifdef DEBUG
	std::cout << "After poping the last element:" << std::endl;
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << std::endl;
#endif

	return result;
}

bool resize()
{
	bool result = true;

	const int		  ints[] = {1, 2, 3, 4, 5};
	ft::vector<int>	  nums(ints, ints + 5);
	const std::string strings[] = {
		"orange",
		"apple",
		"raspberry",
		"bananna",
		"mango",
		"kiwi",
		"strawberry"};
	ft::vector<std::string>	 fruits(strings, strings + 7);
	ft::vector<std::string>* fruits_heap = new ft::vector<std::string>(fruits);
	ft::vector< ft::vector<int> > matrix(3);

#ifdef DEBUG
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << "fruits_heap " << *fruits_heap << std::endl;
	std::cout << "matrix " << matrix << std::endl;
	std::cout << std::endl;
#endif

	nums.resize(9);
	result = result && nums.size() == 9 && nums.back() == 0;
	fruits.resize(16);
	result = result && fruits.size() == 16 && fruits.back() == "";

#ifdef DEBUG
	std::cout << "After resizing to make it bigger:" << std::endl;
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << std::endl;
#endif

	nums.resize(3);
	result = result && nums.size() == 3;
	fruits.resize(3);
	result = result && fruits.size() == 3;
	fruits_heap->resize(3);
	result = result && fruits_heap->size() == 3;
	matrix.resize(2);
	result = result && matrix.size() == 2;

#ifdef DEBUG
	std::cout << "After resizing to make it smaller:" << std::endl;
	std::cout << "nums " << nums << std::endl;
	std::cout << "fruits " << fruits << std::endl;
	std::cout << "fruits_heap " << *fruits_heap << std::endl;
	std::cout << std::endl;
#endif
	delete fruits_heap;

	// resize(currentSize) should not do anything;
	ft::vector<int>::size_type numsSize = nums.size();
	nums.resize(numsSize);
	result = result && nums.size() == numsSize;

	// resize(0) should effectivly clear the vector;
	matrix.resize(0);
	result = result && matrix.empty();

	return result;
}

bool all()
{
	bool success = true;

	std::cout << "-- Test vector --" << std::endl;
	success = success &&
			  debug::run_test("vector construction", test_vector::construction);
	success = success && debug::run_test("vector copy", test_vector::copy);
	success = success && debug::run_test("vector assign", test_vector::assign);
	success =
		success && debug::run_test("vector capacity", test_vector::capacity);
	success = success && debug::run_test("vector data", test_vector::data);
	success = success &&
			  debug::run_test(
				  "vector reverse_iteration", test_vector::reverse_iteration);
	success = success && debug::run_test("vector clear", test_vector::clear);
	success = success && debug::run_test("vector insert", test_vector::insert);
	success = success && debug::run_test("vector erase", test_vector::erase);
	success =
		success && debug::run_test("vector pop_back", test_vector::pop_back);
	success = success && debug::run_test("vector resize", test_vector::resize);

	return success;
}
} // namespace test_vector
