#include <iostream>
#include <string>
#include <iomanip>

#include "../debug_utility.hpp"

#ifdef USE_STL	   // CREATE A REAL STL EXAMPLE
#include <type_traits> // std::is_integral
namespace ft = std;
#else
#include "../utility.hpp"
#endif

bool test_is_integral()
{
	bool success = true;

#ifdef DEBUG
    std::cout << std::boolalpha;

    std::cout << "float: " << ft::is_integral<float>::value << "\n";
    std::cout << "int: " << ft::is_integral<int>::value << "\n";
    std::cout << "const int: " << ft::is_integral<const int>::value << "\n";
    std::cout << "wchar_t: " << ft::is_integral<wchar_t>::value << "\n";
    std::cout << "unsigned long: " << ft::is_integral<unsigned long>::value << "\n";
    std::cout << "bool: " << ft::is_integral<bool>::value << "\n";
	std::cout << std::endl;
#endif

	success = success & (ft::is_integral<float>::value == false);
	success = success & (ft::is_integral<int>::value == true);
	success = success & (ft::is_integral<const int>::value == true);
	success = success & (ft::is_integral<wchar_t>::value == true);
	success = success & (ft::is_integral<unsigned long>::value == true);
	success = success & (ft::is_integral<bool>::value == true);

	return success;
}

bool test_utility()
{
	bool success = true;

	std::cout << "-- Test utility --" << std::endl;
	debug::run_test("is_integral", test_is_integral);

	return success;
}
