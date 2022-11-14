#include <debug_utility.hpp>

bool test_pair();
bool test_utility();
namespace test_vector
{
bool all();
}
namespace test_tree
{
bool all();
}
namespace test_map
{
bool all();
}
namespace test_stack
{
bool all();
}
namespace test_set
{
bool all();
}

int main()
{
	bool		  result = true;
	const clock_t begin = std::clock();

	result = result && debug::run_test("pair", test_pair);
	result = result && debug::run_test("utility", test_utility);
	result = result && debug::run_test("vector", test_vector::all);
	// result = result && debug::run_test("tree", test_tree::all);
	result = result && debug::run_test("map", test_map::all);
	result = result && debug::run_test("stack", test_stack::all);
	result = result && debug::run_test("set", test_set::all);

	// TODO: add test for typedefs?

	if (result)
		std::cout << Color::Modifier(Color::FG_GREEN) << "All Test passed."
				  << Color::Modifier() << std::endl;
	else
		std::cout << Color::Modifier(Color::FG_RED)
				  << "At least one Test failed." << Color::Modifier()
				  << std::endl;
	std::cout << 1000.0 * (std::clock() - begin) / CLOCKS_PER_SEC << "ms"
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
