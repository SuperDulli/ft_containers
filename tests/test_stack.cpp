#include <iomanip>
#include <iostream>
#include <string>

#include "../debug_utility.hpp"
#include <deque>
#include <list>
#include <map>
#include <vector>

#ifdef USE_STL // CREATE A REAL STL EXAMPLE
#include <stack>
namespace ft = std;
#else
#include "../stack.hpp"
#endif

namespace test_stack
{
using ::operator<<; // use operators from the gloabal namespace

bool construction()
{
	bool result = true;

#ifdef DEBUG
	std::cout << "construct stack<int>:" << std::endl;
#endif
	ft::stack<int> intStack;
	result = result && intStack.empty() && intStack.size() == 0;

#ifdef DEBUG
	std::cout << "construct stack< int, std::list<int> >:" << std::endl;
#endif
	ft::stack< int, std::list<int> > intStack2;
	result = result && intStack2.empty() && intStack2.size() == 0;

#ifdef DEBUG
	std::cout << "construct stack< int, std::deque<int> >:" << std::endl;
#endif
	ft::stack< int, std::deque<int> > intStack3;
	result = result && intStack3.empty() && intStack3.size() == 0;

#ifdef DEBUG
	std::cout << "construct stack< int, std::vector<int> >:" << std::endl;
#endif
	ft::stack< int, std::vector<int> > intStack4;
	result = result && intStack4.empty() && intStack4.size() == 0;

#ifdef DEBUG
	std::cout << "construct stack<std::string>:" << std::endl;
#endif
	ft::stack<std::string> stringStack;

	result = result && stringStack.empty() && stringStack.size() == 0;

	const int		count = 20;
	int				ints[] = {53, 4,  28, 83, 76, 7, 26, 74, 97, 64,
							  22, 42, 83, 1,  64, 9, 64, 29, 58, 0};
	ft::vector<int> numbers(ints, ints + count);
#ifdef DEBUG
	std::cout << "construct stack< int, ft::vector> init with copy of vector:"
			  << std::endl;
#endif
	ft::stack< int, ft::vector<int> > init(numbers);
#ifdef DEBUG
	std::cout << init << std::endl;
#endif
	result = result && init.size() == count;

#ifdef DEBUG
	std::cout << "copy the stack<int>" << std::endl;
#endif
	ft::stack< int, ft::vector<int> > copy(init);
#ifdef DEBUG
	std::cout << copy << std::endl;
#endif
	result = result && copy == init;

	return true;
}

bool copy()
{
	bool result = true;

	ft::stack<std::string> empty;
	ft::stack<std::string> stack;

	stack.push("first");
	stack.push("second");
	stack.push("third");

#ifdef DEBUG
	std::cout << "empty: " << empty << std::endl;
	std::cout << "stack: " << stack << std::endl;

	std::cout << "empty = stack (copy assignment)" << std::endl;
#endif
	empty = stack;
#ifdef DEBUG
	std::cout << "empty2(stack) (copy construction)" << std::endl;
#endif
	ft::stack<std::string> empty2(stack);
#ifdef DEBUG
	std::cout << "empty: " << empty << std::endl;
	std::cout << "empty2: " << empty2 << std::endl;
	std::cout << "stack: " << stack << std::endl;
#endif
	result = result && empty == stack && empty2 == stack;

#ifdef DEBUG
	std::cout << "empty.push(\"fourth\");" << std::endl;
	std::cout << "empty2.pop(); " << std::endl;
#endif
	empty.push("fourth");
	empty2.pop();

#ifdef DEBUG
	std::cout << "empty: " << empty << std::endl;
	std::cout << "empty2: " << empty2 << std::endl;
	std::cout << "stack: " << stack << std::endl;
#endif
	result =
		result && empty.size() == 4 && empty2.size() == 2 && stack.size() == 3;

	return result;
}

bool all()
{
	bool success = true;

	std::cout << "-- Test stack --" << std::endl;
	success = success && debug::run_test("stack construction", construction);
	success = success && debug::run_test("stack copy", copy);

	return success;
}
} // namespace test_stack
