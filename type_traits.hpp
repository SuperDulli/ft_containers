#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{

// enable if

template <bool B, class T = void>
struct enable_if;

template <class T>
struct enable_if<true, T> {
	typedef T type;
};

// needed as base class for is integral
template <class T, T v>
struct integral_constant {
	static const T value = v;

	typedef T						value_type;
	typedef integral_constant<T, v> type;

	operator value_type() const
	{
		return value;
	}
};

// specialization of integral_constant are C++11


struct true_type : integral_constant<bool, true> {};
struct false_type : integral_constant<bool, false> {};

// is integral

template <typename T>
struct is_integral : false_type {};

template <>
struct is_integral<bool> : true_type {};
template <>
struct is_integral<char> : true_type {};
template <>
struct is_integral<signed char> : true_type {};
template <>
struct is_integral<unsigned char> : true_type {};
template <>
struct is_integral<wchar_t> : true_type {};
template <>
struct is_integral<short> : true_type {};
template <>
struct is_integral<unsigned short> : true_type {};
template <>
struct is_integral<int> : true_type {};
template <>
struct is_integral<unsigned int> : true_type {};
template <>
struct is_integral<long> : true_type {};
template <>
struct is_integral<unsigned long> : true_type {};
// long long is not c++ 98

// volatile variants
template <>
struct is_integral<volatile bool> : true_type {};
template <>
struct is_integral<volatile char> : true_type {};
template <>
struct is_integral<volatile signed char> : true_type {};
template <>
struct is_integral<volatile unsigned char> : true_type {};
template <>
struct is_integral<volatile wchar_t> : true_type {};
template <>
struct is_integral<volatile short> : true_type {};
template <>
struct is_integral<volatile unsigned short> : true_type {};
template <>
struct is_integral<volatile int> : true_type {};
template <>
struct is_integral<volatile unsigned int> : true_type {};
template <>
struct is_integral<volatile long> : true_type {};
template <>
struct is_integral<volatile unsigned long> : true_type {};

// const variants
template <>
struct is_integral<const bool> : true_type {};
template <>
struct is_integral<const char> : true_type {};
template <>
struct is_integral<const signed char> : true_type {};
template <>
struct is_integral<const unsigned char> : true_type {};
template <>
struct is_integral<const wchar_t> : true_type {};
template <>
struct is_integral<const short> : true_type {};
template <>
struct is_integral<const unsigned short> : true_type {};
template <>
struct is_integral<const int> : true_type {};
template <>
struct is_integral<const unsigned int> : true_type {};
template <>
struct is_integral<const long> : true_type {};
template <>
struct is_integral<const unsigned long> : true_type {};

// volatile & const variants
template <>
struct is_integral<volatile const bool> : true_type {};
template <>
struct is_integral<volatile const char> : true_type {};
template <>
struct is_integral<volatile const signed char> : true_type {};
template <>
struct is_integral<volatile const unsigned char> : true_type {};
template <>
struct is_integral<volatile const wchar_t> : true_type {};
template <>
struct is_integral<volatile const short> : true_type {};
template <>
struct is_integral<volatile const unsigned short> : true_type {};
template <>
struct is_integral<volatile const int> : true_type {};
template <>
struct is_integral<volatile const unsigned int> : true_type {};
template <>
struct is_integral<volatile const long> : true_type {};
template <>
struct is_integral<volatile const unsigned long> : true_type {};

} // namespace ft

#endif // TYPE_TRAITS_HPP
