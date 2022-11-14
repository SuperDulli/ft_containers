#include <iostream>
#include <string>
#include <iomanip>

#include <debug_utility.hpp>

#ifdef USE_STL	   // CREATE A REAL STL EXAMPLE
#include <utility> // std::pair
namespace ft = std;
#else
#include <pair.hpp>
#endif

bool test_pair_construction()
{
	ft::pair<std::string, double> product1; // default constructor
	ft::pair<std::string, double> product2("tomatoes", 2.30); // value init
	ft::pair<std::string, double> product3(product2); // copy constructor

	ft::pair<std::string, double> product4("Titanic", 4.5); // value init
	ft::pair<std::string, int>	  movie(product4); // templated copy constructor

	if (product1.first != "" || product1.second != 0)
		return false;
	if (product2.first != "tomatoes" || product2.second != 2.30)
		return false;
	if (product3.first != product2.first || product3.second != product2.second)
		return false;

	product1 =
		ft::make_pair(std::string("lightbulbs"), 0.99); // using make_pair

#ifdef DEBUG
	std::cout << "The price of " << product1.first << " is $" << product1.second
			  << std::endl;
	std::cout << "The price of " << product2.first << " is $" << product2.second
			  << std::endl;
	std::cout << "The price of " << product3.first << " is $" << product3.second
			  << std::endl;

	std::cout << "product4 " << product4 << std::endl;
	std::cout << "movie " << movie << std::endl;
#endif
	return true;
}

// bool test_swap() // swap is c++11
// {
// 	ft::pair<int, char> foo(10, 'a');
// 	ft::pair<int, char> bar(90, 'z');

// 	foo.swap(bar);

// 	if (foo.first != 90 || foo.second != 'z')
// 		return false;
// 	if (bar.first != 10 || bar.second != 'a')
// 		return false;

// #ifdef DEBUG
// 	std::cout << "foo " << foo << std::endl;
// 	std::cout << "bar " << bar << std::endl;
// #endif

// 	return true;
// }

bool test_relational_operators()
{
	ft::pair<int, char> empty;
	ft::pair<int, char> a(10, 'a');
	ft::pair<int, char> a2(a);
	ft::pair<int, char> b(90, 'z');
	ft::pair<int, char> c(90, 'a');
	ft::pair<int, char> d(10, 'z');

#ifdef DEBUG
	// std::cout << "empty " << empty << std::endl;
	std::cout << "a " << a << std::endl;
	std::cout << "a2 " << a2 << std::endl;
	std::cout << "b " << b << std::endl;
	std::cout << "c " << c << std::endl;
	std::cout << "d " << d << std::endl;

	// std::cout << std::boolalpha;
	// std::cout << std::setw(12) << std::setfill(' ');

	std::cout << "==" << "a|" << "e|" << "b|" << "c|d" << std::endl;
	std::cout << "a|" << (a == a) << "|" << (a == a2) << "|" << (a == b) << "|" << (a == c) << "|" << (a == d) << std::endl;
	std::cout << "b|" << (b == a) << "|" << (b == a2) << "|" << (b == b) << "|" << (b == c) << "|" << (b == d) << std::endl;
	std::cout << "c|" << (c == a) << "|" << (c == a2) << "|" << (c == b) << "|" << (c == c) << "|" << (c == d) << std::endl;
	std::cout << "d|" << (d == a) << "|" << (d == a2) << "|" << (d == b) << "|" << (d == c) << "|" << (d == d) << std::endl;
	std::cout << std::endl;
	std::cout << "!=" << "a|" << "e|" << "b|" << "c|d" << std::endl;
	std::cout << "a|" << (a != a) << "|" << (a != a2) << "|" << (a != b) << "|" << (a != c) << "|" << (a != d) << std::endl;
	std::cout << "b|" << (b != a) << "|" << (b != a2) << "|" << (b != b) << "|" << (b != c) << "|" << (b != d) << std::endl;
	std::cout << "c|" << (c != a) << "|" << (c != a2) << "|" << (c != b) << "|" << (c != c) << "|" << (c != d) << std::endl;
	std::cout << "d|" << (d != a) << "|" << (d != a2) << "|" << (d != b) << "|" << (d != c) << "|" << (d != d) << std::endl;
	std::cout << std::endl;
	std::cout << "< " << "a|" << "e|" << "b|" << "c|d" << std::endl;
	std::cout << "a|" << (a < a) << "|" << (a < a2) << "|" << (a < b) << "|" << (a < c) << "|" << (a < d) << std::endl;
	std::cout << "b|" << (b < a) << "|" << (b < a2) << "|" << (b < b) << "|" << (b < c) << "|" << (b < d) << std::endl;
	std::cout << "c|" << (c < a) << "|" << (c < a2) << "|" << (c < b) << "|" << (c < c) << "|" << (c < d) << std::endl;
	std::cout << "d|" << (d < a) << "|" << (d < a2) << "|" << (d < b) << "|" << (d < c) << "|" << (d < d) << std::endl;
	std::cout << std::endl;
	std::cout << "<=" << "a|" << "e|" << "b|" << "c|d" << std::endl;
	std::cout << "a|" << (a <= a) << "|" << (a <= a2) << "|" << (a <= b) << "|" << (a <= c) << "|" << (a <= d) << std::endl;
	std::cout << "b|" << (b <= a) << "|" << (b <= a2) << "|" << (b <= b) << "|" << (b <= c) << "|" << (b <= d) << std::endl;
	std::cout << "c|" << (c <= a) << "|" << (c <= a2) << "|" << (c <= b) << "|" << (c <= c) << "|" << (c <= d) << std::endl;
	std::cout << "d|" << (d <= a) << "|" << (d <= a2) << "|" << (d <= b) << "|" << (d <= c) << "|" << (d <= d) << std::endl;
	std::cout << std::endl;
	std::cout << "> " << "a|" << "e|" << "b|" << "c|d" << std::endl;
	std::cout << "a|" << (a > a) << "|" << (a > a2) << "|" << (a > b) << "|" << (a > c) << "|" << (a > d) << std::endl;
	std::cout << "b|" << (b > a) << "|" << (b > a2) << "|" << (b > b) << "|" << (b > c) << "|" << (b > d) << std::endl;
	std::cout << "c|" << (c > a) << "|" << (c > a2) << "|" << (c > b) << "|" << (c > c) << "|" << (c > d) << std::endl;
	std::cout << "d|" << (d > a) << "|" << (d > a2) << "|" << (d > b) << "|" << (d > c) << "|" << (d > d) << std::endl;
	std::cout << std::endl;
	std::cout << ">=" << "a|" << "e|" << "b|" << "c|d" << std::endl;
	std::cout << "a|" << (a >= a) << "|" << (a >= a2) << "|" << (a >= b) << "|" << (a >= c) << "|" << (a >= d) << std::endl;
	std::cout << "b|" << (b >= a) << "|" << (b >= a2) << "|" << (b >= b) << "|" << (b >= c) << "|" << (b >= d) << std::endl;
	std::cout << "c|" << (c >= a) << "|" << (c >= a2) << "|" << (c >= b) << "|" << (c >= c) << "|" << (c >= d) << std::endl;
	std::cout << "d|" << (d >= a) << "|" << (d >= a2) << "|" << (d >= b) << "|" << (d >= c) << "|" << (d >= d) << std::endl;
#endif

	if (empty != empty)
		return false;
	if (empty == a)
		return false;
	if (a != a2)
		return false;
	if (a == b || a == c || a == d)
		return false;
	if (!(a != b) || !(a != c) || !(a != d))
		return false;
	if (!(a < b) || !(a < c) || !(a < d))
		return false;
	if (!(a <= b) || !(a <= c) || !(a <= d))
		return false;
	if (a > a2 || a > b || a > c || a > d)
		return false;
	if (!(a >= a2) || a >= b || a >= c || a >= d)
		return false;
	return true;
}

bool test_pair()
{
	bool success = true;

	std::cout << "-- Test pair --" << std::endl;
	debug::run_test("pair construction", test_pair_construction);
	// debug::run_test("pair swap", test_swap);
	debug::run_test("relational operators", test_relational_operators);
	return success;
}
