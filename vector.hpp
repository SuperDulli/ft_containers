#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <string>

#include <stdexcept>

namespace ft
{
template < class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef T										 value_type;
	typedef Alloc									 allocator_type;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::const_pointer	 const_pointer;
	// typedef implementation - defined				 iterator;
	// typedef implementation - defined				 const_iterator;
	// typedef std::reverse_iterator<iterator>			 reverse_iterator;
	// typedef std::reverse_iterator<const_iterator>	 const_reverse_iterator;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::size_type		 size_type;

	// Constructors

	vector();
	explicit vector(const allocator_type& alloc);
	explicit vector(
		size_type			  count,
		const T&			  value = T(),
		const allocator_type& alloc = Alloc());
	// template <class InputIterator>
	// vector(
	// 	InputIterator		  first,
	// 	InputIterator		  last,
	// 	const allocator_type& alloc = Alloc());
	vector(const vector& other);

	// Destructor

	~vector();

	// opertarors

	vector& operator=(const vector& other);

	// member functions

	void assign(size_type count, const T& value);
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last);

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

	// iterators

	// TODO: iterator declaration

protected:
	void m_rangeCheck(size_type pos) const;

private:
	allocator_type m_alloc;
	pointer		   m_start;
	pointer		   m_finish;
	pointer		   m_endOfStorage;
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
ft::vector<T, Alloc>::vector(const allocator_type& alloc)
	: m_alloc(alloc), m_start(), m_finish(), m_endOfStorage()
{
#ifdef DEBUG
	std::cout << "vector constructor (empty)" << std::endl;
#endif
}

template <class T, class Alloc>
ft::vector<T, Alloc>::vector(
	size_type			  n,
	const value_type&	  val,
	const allocator_type& alloc)
	: m_alloc(alloc)
{
#ifdef DEBUG
	std::cout << "vector constructor (fill)" << std::endl;
#endif
	m_start = m_alloc.allocate(n);
	for (size_type i = 0; i < n; i++)
	{
		m_alloc.construct(m_start + i, val);
	}
	m_finish = m_start + n;
	m_endOfStorage = m_finish;
}

// template <class T, class Alloc> template <class InputIterator>
// ft::vector<T, Alloc>::vector(
// 	InputIterator		  first,
// 	InputIterator		  last,
// 	const allocator_type& alloc)
// 	: m_alloc(alloc)
// {
// #ifdef DEBUG
// 	std::cout << "vector constructor (range)" << std::endl;
// #endif
// 	size_type i = 0;

// 	m_start = m_alloc.allocate(static_cast<size_type>(first));
// 	while (first != last)
// 	{
// 		m_alloc.construct(m_start + i, *first);
// 		++first;
// 		++i;
// 	}
// 	m_finish = m_start + i;
// 	m_endOfStorage = m_start + static_cast<size_type>(first);
// }

template <class T, class Alloc>
ft::vector<T, Alloc>::vector(const vector& other) : m_alloc(other.m_alloc)
{
#ifdef DEBUG
	std::cout << "vector constructor (copy)" << std::endl;
#endif
	size_type i;

	m_start = m_alloc.allocate(other.capacity());
	for (i = 0; i < other.capacity(); i++)
	{
		m_alloc.construct(m_start + i, other[i]);
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

// operator

template <class T, class Alloc>
ft::vector<T, Alloc>& ft::vector<T, Alloc>::operator=(const vector& other)
{
#ifdef DEBUG
	std::cout << "vector operator= (copy assignment)" << std::endl;
#endif
	if (this != other)
	{
#ifdef DEBUG
		std::cout << "vectors are not identical (copying elemements)"
				  << std::endl;
#endif
		// TODO: copy
	}
	return *this;
}

// TODO: assign overloads

template <class T, class Alloc>
typename ft::vector<T, Alloc>::allocator_type
ft::vector<T, Alloc>::get_allocator() const
{
	return m_alloc;
}

// capacity

template <class T, class Alloc>
bool ft::vector<T, Alloc>::empty() const
{
	return (m_finish - m_start == 0);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::size() const
{
	return (m_finish - m_start);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::max_size() const
{
	return m_alloc.max_size();
}

template <class T, class Alloc>
void ft::vector<T, Alloc>::reserve(size_type new_cap)
{
	if (new_cap > this->max_size())
		throw std::length_error();
	if (capacity() < new_cap)
	{
		// TODO: realloc
		throw std::logic_error("not implemented");
	}
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::capacity() const
{
	return (m_endOfStorage - m_start);
}

// Element access

template <class T, class Alloc>
void ft::vector<T, Alloc>::m_rangeCheck(size_type pos) const
{
	if (pos >= size())
		throw std::out_of_range("pos out of vector's range.");
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::at(size_type pos)
{
	m_rangeCheck(pos);
	return (*this)[pos];
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference
ft::vector<T, Alloc>::at(size_type pos) const
{
	m_rangeCheck(pos);
	return (*this)[pos];
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference
ft::vector<T, Alloc>::operator[](size_type pos)
{
	return *(this->m_start + pos);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference
ft::vector<T, Alloc>::operator[](size_type pos) const
{
	return *(this->m_start + pos);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::front()
{
	return *begin();
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference
ft::vector<T, Alloc>::front() const
{
	return *begin();
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::back()
{
	return *(end() - 1);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference
ft::vector<T, Alloc>::back() const
{
	return *(end() - 1);
}

template <class T, class Alloc>
T* ft::vector<T, Alloc>::data()
{
	return this->m_start;
}

template <class T, class Alloc>
const T* ft::vector<T, Alloc>::data() const
{
	return this->m_start;
}

#endif // VECTOR_HPP
