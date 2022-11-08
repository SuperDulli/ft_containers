#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <string>

#include "iterator.hpp"
#include "utility.hpp"
#include "pair.hpp"

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
	typedef ft::PtrIterator<T>						 iterator;
	typedef ft::PtrIterator<const T>				 const_iterator;
	typedef ft::reverse_iterator<iterator>			 reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	 const_reverse_iterator;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::size_type		 size_type;

	// Constructors

	vector();
	explicit vector(const allocator_type& alloc);
	explicit vector(
		size_type			  count,
		const T&			  value = T(),
		const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	vector(
		InputIterator first,
		typename ft::enable_if<
			!ft::is_integral<InputIterator>::value,
			InputIterator>::type last,
		const allocator_type&	 alloc = allocator_type());
	vector(const vector& other);

	// Destructor

	~vector();

	// opertarors

	vector& operator=(const vector& other);

	// member functions

	void assign(size_type count, const T& value);
	template <class InputIterator>
	void assign(
		InputIterator first,
		typename ft::enable_if<
			!ft::is_integral<InputIterator>::value,
			InputIterator>::type last);

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

	iterator			   begin();
	const_iterator		   begin() const;
	iterator			   end();
	const_iterator		   end() const;
	reverse_iterator	   rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator	   rend();
	const_reverse_iterator rend() const;

	// modifiers

	void	 clear();
	iterator insert(const_iterator pos, const T& value);
	iterator insert(const_iterator pos, size_type count, const T& value);
	template <class InputIterator>
	iterator insert(
		const_iterator pos,
		InputIterator  first,
		typename ft::enable_if<
			!ft::is_integral<InputIterator>::value,
			InputIterator>::type last);
	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);
	void	 push_back(const T& value);
	void	 pop_back();
	void	 resize(size_type count, T value = T());
	void	 swap(vector& other);

protected:
	void m_rangeCheck(size_type pos) const;

private:
	allocator_type m_alloc;
	pointer		   m_start;
	pointer		   m_finish;
	pointer		   m_endOfStorage;

	void m_moveElementsRight(iterator pos, size_type count);
	void m_moveElementsLeft(iterator pos, size_type count);
	void m_destroy(pointer, size_type count);
}; // class vector

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

template <class T, class Alloc>
template <class InputIterator>
ft::vector<T, Alloc>::vector(
	InputIterator first,
	typename ft::enable_if<
		!ft::is_integral< InputIterator>::value,
		InputIterator>::type last,
	const allocator_type&	 alloc)
	: m_alloc(alloc)
{
#ifdef DEBUG
	std::cout << "vector constructor (range)" << std::endl;
#endif
	InputIterator tmp(first);
	size_type	  size = ft::distance(tmp, last);

	m_start = m_alloc.allocate(size);
	size_type i = 0;
	while (first != last)
	{
		m_alloc.construct(m_start + i, *first);
		++first;
		++i;
	}
	m_finish = m_start + i;
	m_endOfStorage = m_start + size;
}

template <class T, class Alloc>
ft::vector<T, Alloc>::vector(const vector& other) : m_alloc(other.m_alloc)
{
#ifdef DEBUG
	std::cout << "vector constructor (copy)" << std::endl;
#endif
	size_type i;

	m_start = m_alloc.allocate(other.capacity());
	for (i = 0; i < other.size(); i++)
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
	m_destroy(m_start, this->size());
	m_alloc.deallocate(m_start, this->capacity());
}

// operator

template <class T, class Alloc>
ft::vector<T, Alloc>& ft::vector<T, Alloc>::operator=(const vector& other)
{
#ifdef DEBUG
	std::cout << "vector operator= (copy assignment)" << std::endl;
#endif
	if (this != &other)
	{
#ifdef DEBUG
		std::cout << "vectors are not identical (copying elemements)"
				  << std::endl;
#endif
		vector tmp(other);
		swap(tmp);
		return *this;
	}
	return *this;
}

// assign overloads

template <class T, class Alloc>
void ft::vector<T, Alloc>::assign(size_type count, const T& value)
{
	clear();

	if (count > capacity())
	{
		m_alloc.deallocate(m_start, capacity());
		m_start = m_alloc.allocate(count);
		m_endOfStorage = m_start + count;
	}

	for (size_type i = 0; i < count; i++)
	{
		m_alloc.construct(m_start + i, value);
	}
	m_finish = m_start + count;
}

template <class T, class Alloc>
template <class InputIterator>
void ft::vector<T, Alloc>::assign(
	InputIterator first,
	typename ft::enable_if<
		!ft::is_integral<InputIterator>::value,
		InputIterator>::type last)
{
	clear();

	InputIterator tmp(first);
	size_type	  count = ft::distance(tmp, last);
	if (count > capacity())
	{
		m_alloc.deallocate(m_start, capacity());
		m_start = m_alloc.allocate(count);
		m_endOfStorage = m_start + count;
	}

	size_type i = 0;
	while (first != last)
	{
		m_alloc.construct(m_start + i, *first);
		++first;
		++i;
	}
	m_finish = m_start + i;
}

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
		throw std::length_error(
			"vector::reserve (specified capacity would exceed maximum size)");
	if (capacity() < new_cap)
	{
		size_type i;
		pointer	  newArray = m_alloc.allocate(new_cap);
		for (i = 0; i < this->size(); i++)
		{
			m_alloc.construct(newArray + i, m_start[i]);
		}
		m_destroy(m_start, this->size());
		m_alloc.deallocate(m_start, this->capacity());
		m_start = newArray;
		m_finish = m_start + i;
		m_endOfStorage = m_start + new_cap;
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

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::begin()
{
	return iterator(m_start);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator
ft::vector<T, Alloc>::begin() const
{
	return const_iterator(m_start);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::end()
{
	return iterator(m_finish);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator ft::vector<T, Alloc>::end() const
{
	return const_iterator(m_finish);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator ft::vector<T, Alloc>::rbegin()
{
	return reverse_iterator(end());
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator
ft::vector<T, Alloc>::rbegin() const
{
	return const_reverse_iterator(end());
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator ft::vector<T, Alloc>::rend()
{
	return reverse_iterator(begin());
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator
ft::vector<T, Alloc>::rend() const
{
	return const_reverse_iterator(begin());
}

// modifiers

template <class T, class Alloc>
void ft::vector<T, Alloc>::clear()
{
	#ifdef DEBUG
	std::cout << "vector clear" << std::endl;
	#endif
	// for (pointer it = m_start; it != m_finish; ++it)
	// {
	// 	// it->~T();
	// 	m_alloc.destroy(it);
	// }
	m_destroy(m_start, this->size());
	m_finish = m_start;
}

/**
 * @brief Inserts one element at the specified location in the container.
 *
 * @param pos iterator before which the content will be inserted. pos may be the
 * end() iterator
 * @param value element value to insert
 * @return iterator pointing to the inserted value.
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::insert(const_iterator pos, const T& value)
{
	// pos would become in valid in case of realloc
	difference_type offset = pos.base() - m_start;

	insert(pos, 1, value);
	return m_start + offset;
}

/**
 * @brief Inserts elements at the specified location in the container.
 *
 * @param pos iterator before which the content will be inserted. pos may be the
 * end() iterator
 * @param value element value to insert
 * @param count number of elements to insert
 * @return iterator pointing to the inserted value.
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::insert(
	const_iterator pos,
	size_type	   count,
	const T&	   value)
{
	// pos would become in valid in case of realloc
	difference_type offset = pos.base() - m_start;
	if (count == 0)
		return iterator(m_start + offset);

	if (size() + count > capacity())
		reserve(capacity() == 0 ? count : (capacity()) * 2);
	iterator newPosition(m_start + offset);

	if (newPosition != end())
		m_moveElementsRight(newPosition, count);
	for (size_type i = 0; i < count; i++)
	{
		m_alloc.construct(&(*newPosition), value);
		++newPosition;
	}
	m_finish += count;

	return m_start + offset;
}

/**
 * @brief Inserts elements at the specified location in the container.
 *
 * @param pos iterator before which the content will be inserted. pos may be the
 * end() iterator
 * @param first start of the range of elements to insert, can't be a iterator
 * into container for which insert is called
 * @param last end of the range of elements to insert, can't be a iterator
 * into container for which insert is called
 * @return iterator pointing to the inserted value.
 */
template <class T, class Alloc>
template <class InputIterator>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::insert(
	const_iterator pos,
	InputIterator  first,
	typename ft::enable_if<
		!ft::is_integral<InputIterator>::value,
		InputIterator>::type last)
{
	// pos would become in valid in case of realloc
	difference_type offset = pos.base() - m_start;
	if (first == last)
		return iterator(m_start + offset);

	size_type count = ft::distance(first, last);
	reserve(size() + count);
	iterator newPosition(m_start + offset);

	if (newPosition != end())
		m_moveElementsRight(newPosition, count);
	for (size_type i = 0; i < count; i++)
	{
		m_alloc.construct(&(*newPosition), *first);
		++newPosition;
		++first;
	}
	m_finish += count;

	return m_start + offset;
}

/**
 * @brief Removes the element at pos.
 *
 * @param pos iterator to the element to remove
 * @return Iterator following the last removed element.
 * If pos refers to the last element, then the end() iterator is returned.
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::erase(iterator pos)
{
	return erase(pos, pos + 1);
}

/**
 * @brief Removes the elements in the range [first, last).
 *
 * @return Iterator following the last removed element.
 * If last == end() prior to removal, then the updated end() iterator is
 * returned.
 * If [first, last) is an empty range, then last is returned.
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::erase(iterator first, iterator last)
{
	if (first == end() || first == last)
		return last;

	size_type count = static_cast<size_type>(last - first);

	if (last < end())
	{
		m_moveElementsLeft(first, count);
		m_finish -= count;
	}
	else
	{
		while (first != last)
		{
			pop_back();
			--last;
		}
	}
	return first;
}

template <class T, class Alloc>
void ft::vector<T, Alloc>::push_back(const T& value)
{
	size_type currentCapacity = capacity();
	if (size() + 1 > currentCapacity)
	{
		size_type newCapacity =
			(currentCapacity == 0) ? 1 : currentCapacity * 2;
		if (newCapacity > max_size())
		{
			newCapacity = max_size();
			if (newCapacity <= currentCapacity)
				throw std::length_error("could not extend vector because it "
										"already at maximum size");
		}
		reserve(newCapacity);
	}
	m_alloc.construct(m_finish++, value);
}

/**
 * @brief removes the last element.
 *
 */
template <class T, class Alloc>
void ft::vector<T, Alloc>::pop_back()
{
	m_alloc.destroy(m_finish);
	m_finish--;
}

/**
 * @brief Resizes the vector to contain count elements.
 *
 * @param count new size of the vector.
 * If the current size is greater than count, the container is reduced to its
 * first count elements.
 * If the current size is less than count, additional copies of value are
 * appended.
 * @param value the value to initialize the new elements with
 */
template <class T, class Alloc>
void ft::vector<T, Alloc>::resize(size_type count, T value)
{
	if (size() > count)
	{
		// reduce size to count
		m_destroy(m_start + count, size() - count);
		m_finish = m_start + count;
	}
	else if (size() < count)
	{
		// append value to fill the new spots
		size_type i = count - size();
		while (i > 0)
		{
			push_back(value);
			i--;
		}
	}
}

template <class T, class Alloc>
void ft::vector<T, Alloc>::swap(vector& other)
{
	ft::swap(this->m_start, other.m_start);
	ft::swap(this->m_finish, other.m_finish);
	ft::swap(this->m_endOfStorage, other.m_endOfStorage);
	ft::swap(this->m_alloc, other.m_alloc);
}

// helper functions

/**
 * @brief moves elements starting at pos to the right
 *
 * @param pos start position
 * @param steps number of places the elements move
 */
template <class T, class Alloc>
void ft::vector<T, Alloc>::m_moveElementsRight(iterator pos, size_type steps)
{
	ft::pair<iterator, iterator> oldEnd(end() - 1, end());
	while (oldEnd.second != pos)
	{
		m_alloc.construct(&(*(oldEnd.first + steps)), *oldEnd.first);
		m_alloc.destroy(&(*oldEnd.first));
		--oldEnd.first;
		--oldEnd.second;
	}
}

/**
 * @brief moves elements starting at (pos + steps) to the left
 *
 * @param pos start position
 * @param steps number of places the elements move
 */
template <class T, class Alloc>
void ft::vector<T, Alloc>::m_moveElementsLeft(iterator pos, size_type steps)
{
	while (pos != end())
	{
		m_alloc.destroy(&(*pos));
		if (pos + steps < end())
			m_alloc.construct(&(*pos), *(pos + steps));
		++pos;
	}
}

template <class T, class Alloc>
void ft::vector<T, Alloc>::m_destroy(pointer start, size_type count)
{
	for (size_type i = 0; i < count; i++)
	{
		m_alloc.destroy(start + i);
	}
}

// relational operators

template <class T, class Alloc>
bool operator==(
	const ft::vector<T, Alloc>& lhs,
	const ft::vector<T, Alloc>& rhs)
{
	#ifdef DEBUG
	std::cout << "vector equality test" << std::endl;
#endif
	return (
		lhs.size() == rhs.size() &&
		ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!=(
	const ft::vector<T, Alloc>& lhs,
	const ft::vector<T, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(
		lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<=(
	const ft::vector<T, Alloc>& lhs,
	const ft::vector<T, Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(
	const ft::vector<T, Alloc>& lhs,
	const ft::vector<T, Alloc>& rhs)
{
	return (!(lhs < rhs));
}

} // namespace ft

#endif // VECTOR_HPP
