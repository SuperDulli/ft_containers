#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#ifdef DEBUG
#include <iostream>
#endif

#include <iterator>
#include <cstddef>

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
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef std::random_access_iterator_tag iterator_category;
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

template <typename T>
class PtrIterator : public ft::iterator<std::random_access_iterator_tag, T>
{
public:
	typedef PtrIterator<T>							 iterator;
	typedef typename PtrIterator<T>::difference_type difference_type;
	typedef typename PtrIterator<T>::pointer		 pointer;
	typedef typename PtrIterator<T>::reference		 reference;

public:
	// Constructors

	PtrIterator() : m_pos(NULL) {}
	PtrIterator(T* x) : m_pos(x) {}
	PtrIterator(const PtrIterator& it) : m_pos(it.m_pos) {}
	// allows iterator to const iterator conversion
	template <typename X>
	PtrIterator(const PtrIterator<X>& it) : m_pos(it.base())
	{
#ifdef DEBUG
		std::cout << "PtrIterator conversion" << std::endl;
#endif
	}
	~PtrIterator() {}

	// operators

	iterator& operator=(const PtrIterator& other)
	{
		this->m_pos = other.m_pos;
		return *this;
	}

	iterator& operator++()
	{
		++m_pos;
		return *this;
	}

	iterator operator++(int)
	{
		PtrIterator tmp(*this);
					operator++();
		return tmp;
	}

	iterator& operator--()
	{
		--m_pos;
		return *this;
	}

	iterator operator--(int)
	{
		PtrIterator tmp(*this);
					operator--();
		return tmp;
	}

	reference operator*() const
	{
		return *m_pos;
	}

	pointer operator->() const
	{
		return m_pos;
	}

	iterator operator+(difference_type n) const
	{
		return (m_pos + n);
	}

	iterator& operator+=(difference_type n)
	{
		m_pos += n;
		return *this;
	}

	iterator operator-(difference_type n) const
	{
		return (m_pos - n);
	}

	iterator& operator-=(difference_type n)
	{
		m_pos -= n;
		return *this;
	}

	reference operator[](difference_type n) const
	{
		return m_pos[n];
	}

	difference_type operator-(PtrIterator it) const
	{
		return (this->m_pos - it.m_pos);
	}

	const pointer& base() const
	{
		return m_pos;
	}

private:
	T* m_pos;
};

// non-member function

// allow mixed iterator/const_iterator parameters
template <typename L, typename R>
typename PtrIterator<L>::difference_type
operator-(const PtrIterator<L>& lhs, const PtrIterator<R>& rhs)
{
	return (lhs.base() - rhs.base());
}

// allow n + iterator
template <typename T>
PtrIterator<T>
operator+(typename PtrIterator<T>::difference_type n, const PtrIterator<T>& it)
{
	return PtrIterator<T>(it.base() + n);
}

// relation operators (to allow comparison between const and non cost versions)

template <typename L, typename R>
bool operator==(const PtrIterator<L>& lhs, const PtrIterator<R>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <typename L, typename R>
bool operator!=(const PtrIterator<L>& lhs, const PtrIterator<R>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <typename L, typename R>
bool operator<(const PtrIterator<L>& lhs, const PtrIterator<R>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <typename L, typename R>
bool operator<=(const PtrIterator<L>& lhs, const PtrIterator<R>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <typename L, typename R>
bool operator>(const PtrIterator<L>& lhs, const PtrIterator<R>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <typename L, typename R>
bool operator>=(const PtrIterator<L>& lhs, const PtrIterator<R>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator iterator_type;
	typedef
		typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type	  value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer			pointer;
	typedef typename iterator_traits<Iterator>::reference		reference;

	// Constructors

	// // default constructor
	// reverse_iterator(void);
	// // initalization constructor
	// explicit reverse_iterator(iterator_type it);
	// // copy / type-cast constructor
	// template <class Iter>
	// reverse_iterator(const reverse_iterator<Iter>& rev_it);

	// // public member functions

	// // return base iterator
	// iterator_type base(void) const;

	// // operator overloads

	// // derefernce iterator
	// reference operator*(void) const;
	// // addtion operator
	// reverse_iterator operator+(difference_type n) const;
	// // increment iterator position (pre-increment)
	// reverse_iterator& operator++(void);
	// // increment iterator position (post-increment)
	// reverse_iterator operator++(int);
	// // advance iterator position.
	// reverse_iterator& operator+=(difference_type n);
	// // subtraction operator
	// reverse_iterator operator-(difference_type n) const;
	// // decrease iterator position (pre-increment)
	// reverse_iterator& operator--(void);
	// // decrease iterator position (post-increment)
	// reverse_iterator operator--(int);
	// // decrease iterator position
	// reverse_iterator& operator-=(difference_type n);
	// // derefernce iterator
	// pointer operator->(void) const;
	// // derefences with offset
	// reference operator[](difference_type n) const;

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
		iterator_type tmp = m_base_iterator;
		return *--tmp;
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

	reverse_iterator operator--(int)
	{
		reverse_iterator tmp = *this;
		++m_base_iterator;
		return (tmp);
	}

	reverse_iterator& operator-=(difference_type n)
	{
		m_base_iterator += n;
		return (*this);
	}

	pointer operator->(void) const
	{
		return &(operator*());
	}

	reference operator[](difference_type n) const
	{
		return base()[-n - 1];
	}

private:
	iterator_type m_base_iterator;
};

// non-member funtions for reverse_iterator

// relational operators for reverse_iterator

template <class IteratorL, class IteratorR>
bool operator==(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs);
template <class IteratorL, class IteratorR>
bool operator!=(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs);
template <class IteratorL, class IteratorR>
bool operator<(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs);
template <class IteratorL, class IteratorR>
bool operator<=(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs);
template <class IteratorL, class IteratorR>
bool operator>(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs);
template <class IteratorL, class IteratorR>
bool operator>=(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs);

// additon operator
template <class Iterator>
reverse_iterator<Iterator> operator+(
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>&					 rev_it);
// subtraction operator
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);

// implementation of relation operators

template <class IteratorL, class IteratorR>
bool operator==(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class IteratorL, class IteratorR>
bool operator!=(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class IteratorL, class IteratorR>
bool operator<(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class IteratorL, class IteratorR>
bool operator<=(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class IteratorL, class IteratorR>
bool operator>(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class IteratorL, class IteratorR>
bool operator>=(
	const reverse_iterator<IteratorL>& lhs,
	const reverse_iterator<IteratorR>& rhs)
{
	return (lhs.base() <= rhs.base());
}

// implementation of the addition operator

template <class Iterator>
reverse_iterator<Iterator> operator+(
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>&					 rev_it)
{
	return rev_it.operator+(n);
}

// implementation of the subtraction operator

// returns the distance between lhs and rhs;
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs)
{
	return (rhs.base() - lhs.base());
}

} // namespace ft

#endif // ITERATOR_HPP
