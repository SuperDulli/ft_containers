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
	// typedef implementation - defined				 iterator;
	// typedef implementation - defined				 const_iterator;
	typedef std::reverse_iterator<iterator>			 reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	 const_reverse_iterator;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::size_type		 size_type;

	// Constructors

	vector();
	explicit vector(const allocator_type& alloc);
	explicit vector(
		size_type		 count,
		const T&		 value = T(),
		const Allocator& alloc = Allocator());
	template <class InputIt>
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
	vector(const vector& other);

	// Destructor

	~vector();

	// opertarors

	vector& operator=(const vector& other);

	// member functions

	void assign(size_type count, count T& value);
	template <class InputIt>
	void assign(InputIt first, InputIt last);

	allocator_type get_allocator() const;

	// capacity

	bool	  empty() const;
	size_type size() const;
	size_type max_size() const;
	void	  reserve(size_type new_cap);
	size_type capacity() const;

	// Element access

	reference		at(size_type pos);
	const_reference at(size_type pos) const;
	reference		operator[](size_type pos);
	const_reference operator[](size_type pos) const;
	reference		front();
	const_reference front() const;
	reference		back();
	const_reference back() const;
	T*				data();
	const T*		data() const;

protected:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;

private:
	allocator_type m_alloc;
}; // class vector

} // namespace ft

// Constructors

template <class T, class Alloc>
ft::vector<T, Alloc>::vector()
	: m_alloc(), m_start(), m_finish(), m_endOfStorage()
{
#ifdef DEBUG
	std::cout << "vector constructor (default)" << std::endl;
#endif
}

template <class T, class Alloc>
ft::vector<T, Alloc>::vector(const allocator_type& alloc = allocator_type(void))
	: m_alloc(alloc), m_start(), m_finish(), m_endOfStorage()
{
#ifdef DEBUG
	std::cout << "vector constructor (empty)" << std::endl;
#endif
}

template <class T, class Alloc>
ft::vector<T, Alloc>::vector(
	size_type			  n,
	const value_type&	  val = value_type(void),
	const allocator_type& alloc = allocator_type())
	: m_alloc(alloc)
{
#ifdef DEBUG
	std::cout << "vector constructor (fill)" << std::endl;
#endif
	m_start = alloc.allocate(n);
	for (size_type i = 0; i < n; i++)
	{
		alloc.construct(m_start + i, val);
	}
	m_finish = m_start + n;
	m_endOfStorage = m_finish;
}

template <class T, class Alloc, class InputIterator>
ft::vector<T, Alloc>::vector(
	InputIterator		  first,
	InputIterator		  last,
	const allocator_type& alloc = allocator())
	: m_alloc(alloc)
{
#ifdef DEBUG
	std::cout << "vector constructor (range)" << std::endl;
#endif
	size_type i = 0;

	m_start = alloc.allocate(n);
	while (first != last)
	{
		alloc.construct(m_start + i, *first);
		++first;
		++i;
	}
	m_finish = m_start + i;
	m_endOfStorage = m_start + n;
}

template <class T, class Alloc>
ft::vector<T, Alloc>::vector(const vector& other) : m_alloc(alloc)
{
#ifdef DEBUG
	std::cout << "vector constructor (copy)" << std::endl;
#endif
	size_type i = 0;

	m_start = alloc.allocate(other.capacity());
	for (size_type i = 0; i < n; i++)
	{
		alloc.construct(m_start + i, other[i]);
	}
	m_finish = m_start + i;
	m_endOfStorage = m_start + other.capacity();
}

template <class T, class Alloc>
ft::vector<T, Alloc>::~vector(void)
{
#ifdef DEBUG
	std::cout << "vector destructor" << std::endl;
#endif
	m_alloc.deallocate(m_start, this->capacity());
}

#endif // VECTOR_HPP
