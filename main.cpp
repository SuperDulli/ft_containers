#include "debug_utility.hpp"

bool test_pair();

int main() {
	debug::run_test("pair", test_pair);
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
	std::cout << "Test(" << name << "):";
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
