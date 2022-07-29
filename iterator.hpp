#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stddef.h>

namespace ft
{
template <class Iterator>
struct iterator_traits {
	typedef typename Iterator::difference_type	 difference_type;
	typedef typename Iterator::value_type		 value_type;
	typedef typename Iterator::pointer			 pointer;
	typedef typename Iterator::reference		 reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
	typedef ptrdiff_t				   difference_type;
	typedef T						   value_type;
	typedef T*						   pointer;
	typedef T&						   reference;
	typedef random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
	typedef ptrdiff_t				   difference_type;
	typedef T						   value_type;
	typedef const T*				   pointer;
	typedef const T&				   reference;
	typedef random_access_iterator_tag iterator_category;
};

template <
	class Category,
	class T,
	class Distance = ptrdiff_t,
	class Pointer = T*,
	class Reference = T&>
struct iterator {
	typedef T		  value_type;
	typedef Distance  difference_type;
	typedef Pointer	  pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
};

// Empty classes to identify the category of an iterator
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator									 iterator_type;
	typedef iterator_traits<Iterator>::iterator_category iterator_category;
	typedef iterator_traits<Iterator>::value_type		 value_type;
	typedef iterator_traits<Iterator>::difference_type	 difference_type;
	typedef iterator_traits<Iterator>::pointer			 pointer;
	typedef iterator_traits<Iterator>::reference		 reference;

	// Constructors

	// default
	reverse_iterator(void);
	// initalization
	explicit reverse_iterator(iterator_type it);
	// copy / type-cast
	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it);

	// public member functions

	// return base iterator
	iterator_type base(void) const;

	// operator overloads

	// derefernce iterator
	reference operator*(void) const;
	// addtion operator
	reverse_iterator operator+(difference_type n) const;
	// increment iterator position (pre-increment)
	reverse_iterator& operator++(void);
	// increment iterator position (post-increment)
	reverse_iterator operator++(int);
	// advance iterator position.
	reverse_iterator& operator+=(difference_type n);
	// subtraction operator
	reverse_iterator operator-(difference_type n) const;
	// decrease iterator position (pre-increment)
	reverse_iterator& operator--(void);
	// decrease iterator position (post-increment)
	reverse_iterator operator--(int);
	// decrease iterator position
	reverse_iterator& operator-=(difference_type n);
	// derefernce iterator
	pointer operator->(void) const;
	// derefences with offset
	reference operator[](difference_type n) const;

	// "implementation" of reverse_iterator

	// constructor implementations

	reverse_iterator(void) : m_base_iterator() {}
	explicit reverse_iterator(iterator_type it) : m_base_iterator(it) {}
	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it)
		: m_base_iterator(rev_it.base())
	{}

	// public member function implementations

	iterator_type base(void) const
	{
		return m_base_iterator;
	}

	reference operator*(void) const
	{
		return m_base_iterator.reference;
	}

	reverse_iterator operator+(difference_type n) const
	{
		return (reverse_iterator(m_base_iterator - n));
	}

	reverse_iterator& operator++(void)
	{
		--m_base_iterator;
		return (*this);
	}

	reverse_iterator operator++(int)
	{
		reverse_iterator tmp = *this;
		--m_base_iterator;
		return (tmp);
	}

	reverse_iterator operator+=(difference_type n)
	{
		m_base_iterator -= n;
		return (*this);
	}

	reverse_iterator operator-(difference_type n) const
	{
		return (reverse_iterator(m_base_iterator + n));
	}

	reverse_iterator operator--(void)
	{
		++m_base_iterator;
		return (*this);
	}

private:
	iterator_type m_base_iterator;
};

// non-member funtions for reverse_iterator

// relational operators for reverse_iterator

template <class Iterator>
bool operator==(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);
template <class Iterator>
bool operator!=(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);
template <class Iterator>
bool operator<(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);
template <class Iterator>
bool operator<=(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);
template <class Iterator>
bool operator>(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);
template <class Iterator>
bool operator>=(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);

// additon operator
template <class Iterator>
reverse_iterator<Iterator> operator+(
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>&					 rev_it);
// subtraction operator
template <class Iterator>
reverse_iterator<Iterator> operator+(
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>&					 rev_it);

} // namespace ft

#endif // ITERATOR_HPP
