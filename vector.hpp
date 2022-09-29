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
#ifdef DEBUG
		std::cout << "vector constructor (default)" << std::endl;
#endif
	}

	// fill constructor
	explicit vector(
		size_type			  n,
		const value_type&	  val = value_type(void),
		const allocator_type& alloc = allocator_type())
	{
#ifdef DEBUG
		std::cout << "vector constructor (fill)" << std::endl;
#endif
	}

	// range constructor
	template <class InputIterator>
	vector(
		InputIterator		  first,
		InputIterator		  last,
		const allocator_type& alloc = allocator())
	{
#ifdef DEBUG
		std::cout << "vector constructor (range)" << std::endl;
#endif
	}

	// copy constructor
	vector(const vector& src)
	{
#ifdef DEBUG
		std::cout << "vector constructor (copy)" << std::endl;
#endif
	}

	// Destructor
	~vector(void)
	{
#ifdef DEBUG
		std::cout << "vector destructor" << std::endl;
#endif
	}

private:
	allocator_type m_alloc;
}; // class vector

} // namespace ft

#endif // VECTOR_HPP
