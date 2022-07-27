#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <string>

namespace ft
{
template < class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef T										 value_type;
	typedef Allocator								 allocator_type;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::const_pointer	 const_pointer;
	typedef implementation - defined				 iterator;
	typedef implementation - defined				 const_iterator;
	typedef std::reverse_iterator<iterator>			 reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	 const_reverse_iterator;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::size_type		 size_type;

	// Constructors

	// default constructor - empty container
	explicit vector(const allocator_type& alloc = allocator_type(void))
	{
		std::cout << "Default vector constructor called." << std::endl;
	}

	// fill constructor
	explicit vector(
		size_type n, const value_type& val = value_type(void),
		const allocator_type& alloc = allocator_type())
	{
		std::cout << "vector fill constructor called." << std::endl;
	}

	// range constructor
	template <class InputIterator>
	vector(
		InputIterator first, InputIterator last,
		const allocator_type& alloc = allocator())
	{
		std::cout << "vector range constructor called." << std::endl;
	}

	// copy constructor
	vector(const vector& src)
	{
		std::cout << "vector copy constructor called." << std::endl;
	}

	// Destructor
	~vector(void)
	{
		std::cout << "vector destructor called." << std::endl;
	}

private:
	allocator_type m_alloc;
}; // class vector

} // namespace ft

#endif // VECTOR_HPP
