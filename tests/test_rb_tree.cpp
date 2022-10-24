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
	tree_type;

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

bool insert()
{
	bool result = true;

	tree_type empty;

	empty.insert(ft::make_pair<const int, int>(120, 0));
	empty.insert(ft::make_pair(7, 0));
	empty.insert(ft::make_pair(3, 0));
	empty.insert(ft::make_pair(15, 0));
	empty.insert(ft::make_pair(16, 0));
	empty.insert(ft::make_pair(14, 0));
	empty.insert(ft::make_pair(200, 0));
	empty.insert(ft::make_pair(150, 0));
	empty.insert(ft::make_pair(250, 0));

	// iteration
	tree_type::iterator it;
	it = empty.begin();
	while (it != empty.end())
	{
		std::cout << *it << std::endl;
		++it;
	}

	// reverse iteration
	it = empty.end();
	while (it != empty.begin())
	{
		--it;
		std::cout << *it << std::endl;
	}

	// delete

	empty.erase(empty.begin());

	std::cout << empty << std::endl;

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
} // namespace test_tree

int main()
{
	bool result = true;

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
