#include <iomanip>
#include <iostream>
#include <string>

#include <vector> // for getting iterators

#include "../debug_utility.hpp"

#ifdef USE_STL // CREATE A REAL STL EXAMPLE
#include <set>
namespace ft = std;
#else
#include "../set.hpp"
#endif

namespace test_set
{
using ::operator<<; // use operators from the gloabal namespace

ft::set<int> generate_sorted_set(size_t count = 20)
{
	ft::set<int> sorted;
	debug::insert_sorted(sorted, count);

#ifdef DEBUG
	std::cout << sorted << std::endl;
#endif
	return sorted;
}

ft::set<int> generate_random_set(size_t count = 20)
{
	ft::set<int> random;
	debug::insert_random(random, count);

#ifdef DEBUG
	std::cout << random << std::endl;
#endif
	return random;
}

bool construction()
{
	bool result = true;

	// empty
	ft::set<int> empty;
#ifdef DEBUG
	std::cout << "empty " << empty << std::endl;
#endif
	result = result && empty.empty() && empty.size() == 0;

	// range
	const int		 count = 20;
	int				 ints[] = {53, 4,  28, 83, 76, 7, 26, 74, 97, 64,
							   22, 42, 83, 1,  64, 9, 64, 29, 58, 0};
	std::vector<int> numbers(ints, ints + count);
	ft::set<int>	 range(numbers.begin(), numbers.end());
#ifdef DEBUG
	std::cout << "range " << range << std::endl;
#endif
	// numbers could contain duplicates
	result = result && !range.empty() && range.size() <= count;

	// copy
	ft::set<int> copy(range);
#ifdef DEBUG
	std::cout << "copy " << copy << std::endl;
#endif
	result = result && copy == range && copy != empty;

	return result;
}

bool insert_simple()
{
	bool result = true;
#ifdef DEBUG
	std::cout << "insert one by one (total=6)" << std::endl;
#endif
	ft::set<int>							 set;
	ft::pair< ft::set<int>::iterator, bool > insert_result;

	insert_result = set.insert(1);
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;

#ifdef DEBUG
	std::cout << "insert the same key again" << std::endl;
#endif
	insert_result = set.insert(1);
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == false;

	insert_result = set.insert(2);
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;
	insert_result = set.insert(3);
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;
	insert_result = set.insert(4);
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;
	insert_result = set.insert(5);
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;
	insert_result = set.insert(6);
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;

#ifdef DEBUG
	std::cout << set << std::endl;
#endif
	result = result && set.size() == 6;
	return result;
}

bool insert_hint(ft::set<int>& set, ft::set<int>::iterator hint, int value)
{
	ft::set<int>::iterator	it;
	ft::set<int>::size_type set_size;

	set_size = set.size();
	it = set.insert(hint, value);
	return debug::insertion_status(it, set.size() != set_size);
}

bool insert_hint()
{
	bool result = true;
#ifdef DEBUG
	std::cout << "insert one by one with hint (total=6)" << std::endl;
#endif
	ft::set<int> set;

	result = result && insert_hint(set, set.end(), 1) == true;

#ifdef DEBUG
	std::cout << "insert the same key again" << std::endl;
#endif
	result = result && insert_hint(set, set.end(), 1) == false;

#ifdef DEBUG
	std::cout << "insert with wrong hint" << std::endl;
#endif
	result = result && insert_hint(set, set.begin(), 2) == true;
	result = result && insert_hint(set, set.end(), 3) == true;
	result = result && insert_hint(set, set.end(), 4) == true;
	result = result && insert_hint(set, set.end(), 5) == true;
	result = result && insert_hint(set, set.end(), 6) == true;

#ifdef DEBUG
	std::cout << set << std::endl;
#endif
	result = result && set.size() == 6;
	return result;
}

bool insert_random()
{
	ft::set<int> random;

	debug::insert_random(random, 20);

#ifdef DEBUG
	std::cout << random << std::endl;
#endif
	// could try to insert duplicates
	return (!random.empty() && random.size() <= 20);
}

bool insert_range()
{
	std::cout << "insert a range" << std::endl;
	int				 ints[] = {88, 64, 5, 89, 78, 17, 95, 8, 61, 0};
	std::vector<int> numbers(ints, ints + 10);
	ft::set<int>	 range;

	range.insert(numbers.begin(), numbers.end());

	std::cout << range << std::endl;
	return (range.size() == numbers.size());
}

bool insert()
{
	bool result = true;

	result = result && debug::run_test("insert simple", insert_simple);
	result = result && debug::run_test("insert hint", insert_hint);
	result = result && debug::run_test("insert range", insert_range);
	result = result && debug::run_test("insert random", insert_random);

	return result;
}

bool copy()
{
	bool result = true;

	ft::set<std::string> empty;
	const std::string	 strings[] = {"orange", "apple", "raspberry"};
	ft::set<std::string> fruits(strings, strings + 3);

#ifdef DEBUG
	std::cout << "copy with copy constructor" << std::endl;
#endif
	ft::set<std::string> empty_copy(empty);
	result = result && empty == empty_copy;

#ifdef DEBUG
	std::cout << "copy assignment" << std::endl;
#endif

	return result;
}

bool all()
{
	bool success = true;

	std::cout << "-- Test set --" << std::endl;
	success =
		success && debug::run_test("set construction", test_set::construction);
	success = success && debug::run_test("set insert", test_set::insert);
	// success = success && debug::run_test("set erase", test_set::erase);
	// success = success && debug::run_test("set access", test_set::access);

	// debug::run_test("relational operators", test_relational_operators);
	return success;
}
} // namespace test_set
