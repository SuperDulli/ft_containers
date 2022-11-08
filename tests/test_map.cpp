#include <iomanip>
#include <iostream>
#include <string>

#include <vector> // for getting iterators

#include "../debug_utility.hpp"

#ifdef USE_STL // CREATE A REAL STL EXAMPLE
#include <map>
namespace ft = std;
#else
#include "../map.hpp"
#endif

namespace test_map
{
using ::operator<<; // use operators from the gloabal namespace

ft::map<int, int> generate_random_map(size_t count = 20)
{
	ft::map<int, int> random;
	debug::insert_random_pair(random, count);

#ifdef DEBUG
	std::cout << random << std::endl;
#endif
	return random;
}

ft::map<int, int> generate_sorted_map(size_t count = 20)
{
	ft::map<int, int> sorted;
	debug::insert_sorted_pair(sorted, count);

#ifdef DEBUG
	std::cout << sorted << std::endl;
#endif
	return sorted;
}

bool construction()
{
	bool result = true;

	// default
	ft::map<int, int> empty;
	result = result && empty.empty() && empty.size() == 0;

	// range
	const int count = 20;
	int		  ints[] = {99, 8, 28, 45, 33, 22, 99, 50, 97, 8,
						48, 7, 31, 48, 78, 87, 27, 31, 4,  79};
	ft::vector< ft::pair<int, int> > number_pairs;
	for (size_t i = 0; i < count; i++)
	{
		number_pairs.push_back(ft::make_pair(ints[i], i));
	}
	ft::map<int, int> range(number_pairs.begin(), number_pairs.end());
	result = result && !range.empty() && range.size() != 0;

	// TODO: empty with custom compare and/or allocator
	// TODO: complex objects

	ft::map<std::string, int> animal_weights;
result = result && animal_weights.empty();

	ft::map<int, int> empty_copy(empty);
	result = result && empty_copy == empty;

	ft::map<int, int> copy(range);
	result = result && copy == range;

	return result;
}

bool insert_simple()
{
	bool result = true;
#ifdef DEBUG
	std::cout << "insert one by one (total=6)" << std::endl;
#endif
	ft::map<int, int>							  map;
	ft::pair< ft::map<int, int>::iterator, bool > insert_result;

	insert_result = map.insert(ft::make_pair(1, 0));
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;

#ifdef DEBUG
	std::cout << "insert the same key again" << std::endl;
#endif
	insert_result = map.insert(ft::make_pair(1, 99999999));
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == false;

	insert_result = map.insert(ft::make_pair(2, 0));
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;
	insert_result = map.insert(ft::make_pair(3, 0));
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;
	insert_result = map.insert(ft::make_pair(4, 0));
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;
	insert_result = map.insert(ft::make_pair(5, 0));
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;
	insert_result = map.insert(ft::make_pair(6, 0));
	result = result && debug::insertion_status(
						   insert_result.first, insert_result.second) == true;

#ifdef DEBUG
	std::cout << map << std::endl;
#endif
	result = result && map.size() == 6;
	return result;
}

bool insert_hint(
	ft::map<int, int>&			map,
	ft::map<int, int>::iterator hint,
	const ft::pair<int, int>&	pair)
{
	ft::map<int, int>::iterator	 it;
	ft::map<int, int>::size_type map_size;

	map_size = map.size();
	it = map.insert(hint, pair);
	return debug::insertion_status(it, map.size() != map_size);
}

bool insert_hint()
{
	bool result = true;
#ifdef DEBUG
	std::cout << "insert one by one with hint (total=6)" << std::endl;
#endif
	ft::map<int, int> map;

	result = result && insert_hint(map, map.end(), ft::make_pair(1, 0)) == true;

#ifdef DEBUG
	std::cout << "insert the same key again" << std::endl;
#endif
	result =
		result && insert_hint(map, map.end(), ft::make_pair(1, 99999)) == false;

#ifdef DEBUG
	std::cout << "insert with wrong hint" << std::endl;
#endif
	result =
		result && insert_hint(map, map.begin(), ft::make_pair(2, -1)) == true;
	result = result && insert_hint(map, map.end(), ft::make_pair(3, 3)) == true;
	result = result && insert_hint(map, map.end(), ft::make_pair(4, 4)) == true;
	result = result && insert_hint(map, map.end(), ft::make_pair(5, 5)) == true;
	result = result && insert_hint(map, map.end(), ft::make_pair(6, 6)) == true;

#ifdef DEBUG
	std::cout << map << std::endl;
#endif
	result = result && map.size() == 6;
	return result;
}

bool insert_range()
{
	const int count = 10;
	int		  ints[] = {88, 64, 5, 89, 78, 17, 95, 8, 61, 0};
	ft::vector< ft::pair<int, int> > number_pairs;
	for (size_t i = 0; i < count; i++)
	{
		number_pairs.push_back(ft::make_pair(ints[i], i));
	}
	ft::map<int, int> range;

	range.insert(number_pairs.begin(), number_pairs.end());

#ifdef DEBUG
	std::cout << range << std::endl;
#endif
	// number_pairs could contain duplicates
	return (!range.empty() && range.size() <= number_pairs.size());
}

bool insert_random()
{
	ft::map<int, int> random;

	debug::insert_random_pair(random, 20);

#ifdef DEBUG
	std::cout << random << std::endl;
#endif
	// could try to insert duplicates
	return (!random.empty() && random.size() <= 20);
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

bool erase_pos()
{
	ft::map<int, int>			 map = generate_random_map(20);
	ft::map<int, int>::size_type map_size = map.size();

#ifdef DEBUG
	std::cout << "erase begin() by iterator:" << std::endl;
#endif
	map.erase(map.begin());

#ifdef DEBUG
	std::cout << map << std::endl;
#endif
	return map.size() + 1 == map_size;
}

bool erase_range(
	ft::map<int, int>&			map,
	ft::map<int, int>::iterator first,
	ft::map<int, int>::iterator last)
{
	ft::map<int, int>::size_type map_size = map.size();
	ft::map<int, int>::size_type removed_size = ft::distance(first, last);

#ifdef DEBUG
	std::cout << "erase range [";
	printIterName(map, first);
	std::cout << ", ";
	printIterName(map, last);
	std::cout << ") by iterator (" << removed_size
			  << " element(s)):" << std::endl;
#endif
	map.erase(first, last);
#ifdef DEBUG
	std::cout << map << std::endl;
#endif

	return map.size() == map_size - removed_size;
}

bool erase_range()
{
	bool result = true;

	ft::map<int, int>			map = generate_sorted_map(20);
	ft::map<int, int>::iterator first;
	ft::map<int, int>::iterator last;

	first = map.begin();
	last = map.begin();
	ft::advance(last, 5);
	result = result && erase_range(map, first, last);

	first = map.begin();
	last = map.end();
	ft::advance(first, 5);
	result = result && erase_range(map, first, last);

	first = map.begin();
	ft::advance(first, 2);
	last = first;
	ft::advance(last, 1);
	result = result && erase_range(map, first, last);

	result = result && erase_range(map, map.begin(), map.end());

	return result;
}

bool erase_key(ft::map<int, int>& map, int key)
{
	ft::map<int, int>::size_type map_size = map.size();
	ft::map<int, int>::size_type removed;

#ifdef DEBUG
	std::cout << "erase key=" << key << std::endl;
#endif
	removed = map.erase(key);
#ifdef DEBUG
	std::cout << map << std::endl;
#endif

	return map.size() == map_size - removed && map.count(key) == 0;
}

bool erase_key()
{
	bool result = true;

	ft::map<int, int> map = generate_sorted_map(20);

	result = result && erase_key(map, 5);
#ifdef DEBUG
	std::cout << "erase non existing key;" << std::endl;
#endif
	result = result && erase_key(map, -42);

	return result;
}

bool erase()
{
	bool result = true;

	result = result && debug::run_test("erase pos", erase_pos);
	result = result && debug::run_test("erase range", erase_range);
	result = result && debug::run_test("erase key", erase_key);

	return result;
}

bool access()
{
	bool result = true;

	ft::map<std::string, int> animal_weights;
	int						  wieght;

	wieght = animal_weights["Whale"];
#ifdef DEBUG
	std::cout << "Try to look up the weight of a Whale: " << wieght << std::endl;
#endif
	result = result && wieght == 0;

	animal_weights["Whale"] = 136000;
#ifdef DEBUG
	std::cout << "Set the weight of a Whale: " << animal_weights["Whale"]
			  << std::endl;
#endif
	result = result && animal_weights["Whale"] == 136000;

	animal_weights["Moose"] = 386;
#ifdef DEBUG
	std::cout << "Set the weight of a Moose: " << animal_weights["Moose"]
			  << std::endl;
#endif
	result = result && animal_weights["Moose"] == 386;

#ifdef DEBUG
	std::cout << animal_weights << std::endl;
#endif

	return result;
}

bool clear()
{
	ft::map<int, int> map = generate_random_map();

	map.clear();
#ifdef DEBUG
	std::cout << map << std::endl;
#endif
	return map.empty() && map.size() == 0;
}

bool all()
{
	bool success = true;

	std::cout << "-- Test map --" << std::endl;
	success =
		success && debug::run_test("map construction", test_map::construction);
	success = success && debug::run_test("map insert", test_map::insert);
	success = success && debug::run_test("map erase", test_map::erase);
	success = success && debug::run_test("map access", test_map::access);
	success = success && debug::run_test("map clear", test_map::clear);

	// debug::run_test("relational operators", test_relational_operators);
	return success;
}
} // namespace test_map
