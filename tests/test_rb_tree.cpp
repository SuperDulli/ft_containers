#include <iomanip>
#include <iostream>
#include <string>

#include <functional> // less
#include <utility>	  // pair

#include "../debug_utility.hpp"
#include "../utility.hpp" // selectFirst

#include "../tree.hpp"

namespace test_tree
{
typedef RB_tree<
	int,
	ft::pair<const int, int>,
	ft::SelectFirst< ft::pair<const int, int> >,
	std::less<int> >
	map_tree_type;

typedef RB_tree< int, int, ft::Identity<int>, std::less<int> > set_tree_type;

bool construction()
{
	bool result = true;

	RB_tree<
		int,
		std::pair<const int, int>,
		ft::SelectFirst< ft::pair<const int, int> >,
		std::less<int> >
		empty;

	return result;
}

bool insert_simple()
{
	std::cout << "insert one by one (total=6)" << std::endl;
	set_tree_type set_tree;

	set_tree.insert(50);
	set_tree.insert(5);
	set_tree.insert(25);
	set_tree.insert(100);
	set_tree.insert(75);
	set_tree.insert(90);

	std::cout << set_tree << std::endl;
	return (set_tree.verify() && set_tree.size() == 6);
}

bool insert_unique()
{
	std::cout << "insert the same key twice" << std::endl;
	set_tree_type unique;
	unique.insert(1);
	unique.insert(1);

	std::cout << unique << std::endl;
	return (unique.verify() && unique.size() == 1);
}

bool insert_unique_complex()
{
	std::cout << "insert the same key twice (on accident)" << std::endl;
	set_tree_type unique_complex;
	unique_complex.insert(83);
	unique_complex.insert(86);
	unique_complex.insert(77);
	unique_complex.insert(15);
	unique_complex.insert(93);
	unique_complex.insert(35);
	unique_complex.insert(86);
	unique_complex.insert(92);
	unique_complex.insert(49);
	unique_complex.insert(21);

	std::cout << unique_complex << std::endl;
	return (unique_complex.verify() && unique_complex.size() == 9);
}

bool insert_range()
{
	std::cout << "insert a range" << std::endl;
	int				ints[] = {88, 64, 5, 89, 78, 17, 95, 8, 61, 0};
	ft::vector<int> numbers(ints, ints + 10);
	set_tree_type	range;

	range.insert(numbers.begin(), numbers.end());

	std::cout << range << std::endl;
	return (range.verify() && range.size() == numbers.size());
}

bool insert_random()
{
	const int count = 50;
	std::cout << "insert " << count << " random numbers" << std::endl;
	set_tree_type random;
	insert_random(random, count);

	std::cout << random << std::endl;
	return random.verify();
}

bool insert_hint()
{
	std::cout << "insert with a hint" << std::endl;
	set_tree_type	hint_tree;
	int				ints[] = {88, 64, 5, 89, 78, 17, 95, 8, 61, 0};
	ft::vector<int> numbers(ints, ints + 10);

	hint_tree.insert(numbers.begin(), numbers.end());
	std::cout << hint_tree << std::endl;

	set_tree_type::iterator hint = hint_tree.find(17);
	hint = hint_tree.insert(hint, 16);
	std::cout << hint_tree << std::endl;

	hint = hint_tree.insert(hint, 15);
	std::cout << hint_tree << std::endl;

	std::cout << "wrong hint:" << std::endl;
	hint_tree.insert(hint, 5);
	std::cout << hint_tree << std::endl;

	std::cout << "wrong hint:" << std::endl;
	hint = hint_tree.find(17);
	hint_tree.insert(hint, 18);
	std::cout << hint_tree << std::endl;

	std::cout << "hint == begin:" << std::endl;
	hint = hint_tree.begin();
	hint_tree.insert(hint, -1);
	std::cout << hint_tree << std::endl;

	std::cout << "hint == end:" << std::endl;
	hint = hint_tree.end();
	hint_tree.insert(hint, 100);
	std::cout << hint_tree << std::endl;

	std::cout << "hint == begin (empty tree):" << std::endl;
	set_tree_type empty;
	hint = empty.begin();
	empty.insert(hint, 42);
	std::cout << empty << std::endl;

	std::cout << "hint == begin (empty tree):" << std::endl;
	set_tree_type empty2;
	hint = empty2.begin();
	empty2.insert(hint, 42);
	std::cout << empty2 << std::endl;

	return hint_tree.verify() && empty.verify() && empty2.verify();
}

bool insert()
{
	bool result = true;

	// map_tree_type empty;

	// empty.insert(ft::make_pair<const int, int>(120, 0));
	// empty.insert(ft::make_pair(7, 0));
	// empty.insert(ft::make_pair(3, 0));
	// empty.insert(ft::make_pair(15, 0));
	// empty.insert(ft::make_pair(16, 0));
	// empty.insert(ft::make_pair(14, 0));
	// empty.insert(ft::make_pair(200, 0));
	// empty.insert(ft::make_pair(150, 0));
	// empty.insert(ft::make_pair(250, 0));

	result = result && debug::run_test("insert simple", insert_simple);
	result = result && debug::run_test("insert unique", insert_unique);
	result = result &&
			 debug::run_test("insert unique_complex", insert_unique_complex);
	result = result && debug::run_test("insert range", insert_range);
	result = result && debug::run_test("insert random", insert_random);
	result = result && debug::run_test("insert hint", insert_hint);

	// // iteration
	// set_tree_type::iterator it;
	// it = set_tree.begin();
	// while (it != set_tree.end())
	// {
	// 	std::cout << *it << std::endl;
	// 	++it;
	// }

	// // reverse iteration
	// it = set_tree.end();
	// while (it != set_tree.begin())
	// {
	// 	--it;
	// 	std::cout << *it << std::endl;
	// }

	// // delete

	// set_tree.erase(set_tree.begin());

	// std::cout << set_tree << std::endl;

	// result = result && set_tree.verify();

	return result;
}

bool all()
{
	bool result = true;

	std::cout << "-- Test Red-Black tree --" << std::endl;
	result =
		result && debug::run_test("tree construction", test_tree::construction);
	result = result && debug::run_test("tree insert", test_tree::insert);

	// debug::run_test("relational operators", test_relational_operators);
	return result;
}
} // namespace test_tree

int main()
{
	bool result = true;

	srand(time(NULL));

	result = result && debug::run_test("tree", test_tree::all);

	if (result)
		std::cout << Color::Modifier(Color::FG_GREEN) << "All Test passed."
				  << Color::Modifier() << std::endl;
	else
		std::cout << Color::Modifier(Color::FG_RED)
				  << "At least one Test failed." << Color::Modifier()
				  << std::endl;
	return (result ? 0 : 1);
}

bool debug::run_test(const std::string& name, bool (*test_f)(void))
{
	std::cout << "running Test: " << name << std::endl;
	bool result = (test_f) ();
	test_result(name, result);

	return result;
}

void debug::test_result(const std::string& name, bool result)
{
	std::cout << "Test(" << name << "): ";
	if (result)
	{
		std::cout << Color::Modifier(Color::FG_GREEN) << "passed."
				  << Color::Modifier();
	}
	else
	{
		std::cout << Color::Modifier(Color::FG_RED) << "failed."
				  << Color::Modifier();
	}
	std::cout << std::endl;
}
