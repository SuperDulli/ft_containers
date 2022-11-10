#include <iomanip>
#include <iostream>
#include <string>

#include <debug_utility.hpp>

#ifdef USE_STL		   // CREATE A REAL STL EXAMPLE
#include <type_traits> // std::is_integral
namespace ft = std;
#else
#include <type_traits.hpp>
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
	std::cout << "unsigned long: " << ft::is_integral<unsigned long>::value
			  << "\n";
	std::cout << "bool: " << ft::is_integral<bool>::value << "\n";
	std::cout << std::endl;
#endif

	success = success && (ft::is_integral<float>::value == false);
	success = success && (ft::is_integral<int>::value == true);
	success = success && (ft::is_integral<const int>::value == true);
	success = success && (ft::is_integral<wchar_t>::value == true);
	success = success && (ft::is_integral<unsigned long>::value == true);
	success = success && (ft::is_integral<bool>::value == true);

	return success;
}

// helper functions for testing equal
bool is_palindrome(const std::string& s)
{
	return ft::equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
}

bool test_palindrome(const std::string& s)
{
	bool result = is_palindrome(s);
#ifdef DEBUG
	std::cout << "\"" << s << "\" " << (result ? "is" : "is not")
			  << " a palindrome" << std::endl;
#endif
	return result;
}

bool predicate_same_case(const char a, const char b)
{
	if (!std::isalpha(a) || !std::isalpha(b))
		return false;
	return (
		(std::isupper(a) && std::isupper(b)) ||
		(std::islower(a) && std::islower(b)));
}

bool compare_string_case(const std::string& s1, const std::string& s2)
{
	return ft::equal(s1.begin(), s1.end(), s2.begin(), predicate_same_case);
}

bool test_string_case(const std::string& s1, const std::string& s2)
{
	bool result = compare_string_case(s1, s2);

#ifdef DEBUG
	std::cout << "\"" << s1 << "\" and \"" << s2 << "\" "
			  << (result ? "have" : "dont't have")
			  << " the same case in all characters (length of first)."
			  << std::endl;
#endif
	return result;
}

bool test_equal()
{
	bool result = true;

	result = result && (test_palindrome("radar") == true);
	result = result && (test_palindrome("lagerregal") == true);
	result = result && (test_palindrome("hello") == false);

	result = result && (test_string_case("hello", "radar") == true);
	result = result && (test_string_case("Hello", "Radar") == true);
	result = result && (test_string_case("HeLlO", "RaDaR") == true);
	result = result && (test_string_case("Hell", "Radar") == true);
	result = result && (test_string_case("sweet", "1nice") == false);
	result = result && (test_string_case("sweet", "Sweet") == false);
	result = result && (test_string_case("swEeT", "Sweet") == false);

	return result;
}

bool compare_lexicographic(const std::string& s1, const std::string& s2)
{
	bool result =
		ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());

#if DEBUG
	std::cout << std::boolalpha;
	std::cout << "Comparing \"" << s1 << "\" and \"" << s2
			  << "\" lexicographical (less): " << result << std::endl;
#endif
	return result;
}

// a case-insensitive comparison function:
bool case_insensitive_compare(const char a, const char b)
{
	return std::tolower(a) < std::tolower(b);
}

bool compare_lexicographic_case_insensitive(
	const std::string& s1,
	const std::string& s2)
{
	bool result = ft::lexicographical_compare(
		s1.begin(), s1.end(), s2.begin(), s2.end(), case_insensitive_compare);

#if DEBUG
	std::cout << std::boolalpha;
	std::cout << "Comparing \"" << s1 << "\" and \"" << s2
			  << "\" lexicographical (less, case insensitve): " << result
			  << std::endl;
#endif
	return result;
}

bool test_lexicographical_compare()
{
	bool result = true;

	result = result && (compare_lexicographic("Apple", "apartment") == true);
	result = result && (compare_lexicographic("hello", "radar") == true);
	result = result && (compare_lexicographic("abc", "def") == true);
	result = result && (compare_lexicographic("Abc", "Aef") == true);
	result = result && (compare_lexicographic("short", "shorter") == true);
	result = result && (compare_lexicographic("same", "same") == false);
	result = result && (compare_lexicographic("Bcd", "Aef") == false);
	result = result && (compare_lexicographic("shorter", "short") == false);

	result = result && (compare_lexicographic_case_insensitive(
							"Apple", "apartment") == false);

	return result;
}

bool test_utility()
{
	bool success = true;

	std::cout << "-- Test utility --" << std::endl;
	debug::run_test("is_integral", test_is_integral);
	debug::run_test("equal", test_equal);
	debug::run_test("lexicographical_compare", test_lexicographical_compare);

	return success;
}
