#ifndef SET_HPP
#define SET_HPP

#ifdef DEBUG
#include <iostream>
#endif

#include "tree.hpp"

#include <functional> // less
#include <memory>	  // allocator

namespace ft
{

template <
	class Key,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<Key> >
class set
{
public:
	typedef Key										 key_type;
	typedef Key										 value_type;
	typedef Compare									 key_compare;
	typedef Compare									 value_compare;
	typedef Allocator								 allocator_type;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::const_pointer	 const_pointer;

private:
	typedef typename Allocator::template rebind<value_type>::other alloc_type;

	typedef RB_tree<
		key_type,
		value_type,
		ft::Identity<value_type>,
		key_compare,
		alloc_type>
		tree_type;

	tree_type m_tree;

public:
	typedef typename tree_type::iterator			   iterator;
	typedef typename tree_type::const_iterator		   const_iterator;
	typedef typename tree_type::reverse_iterator	   reverse_iterator;
	typedef typename tree_type::const_reverse_iterator const_reverse_iterator;
	typedef typename tree_type::size_type			   size_type;
	typedef typename tree_type::difference_type		   difference_type;

	// constructor

	set();
	explicit set(
		const key_compare&	  comp,
		const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	set(InputIterator first,
		InputIterator last,
		const key_compare& = key_compare(),
		const allocator_type& alloc = allocator_type());
	set(const set& other);

	~set();

	set&		   operator=(const set& other);
	allocator_type get_allocator() const;

	// iterators

	iterator			   begin();
	const_iterator		   begin() const;
	iterator			   end();
	const_iterator		   end() const;
	reverse_iterator	   rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator	   rend();
	const_reverse_iterator rend() const;

	// capacity

	bool	  empty() const;
	size_type size() const;
	size_type max_size() const;

	// modifiers

	void					 clear();
	ft::pair<iterator, bool> insert(const value_type& value);
	iterator				 insert(iterator pos, const value_type& value);
	template <class InputIterator>
	void	  insert(InputIterator first, InputIterator last);
	void	  erase(iterator pos);
	void	  erase(iterator first, iterator last);
	size_type erase(const key_type& key);
	void	  swap(set& other);

	// lookup

	size_type					 count(const key_type& key) const;
	iterator					 find(const key_type& key);
	const_iterator				 find(const key_type& key) const;
	ft::pair<iterator, iterator> equal_range(const key_type& key);
	ft::pair<const_iterator, const_iterator>
				   equal_range(const key_type& key) const;
	iterator	   lower_bound(const key_type& key);
	const_iterator lower_bound(const key_type& key) const;
	iterator	   upper_bound(const key_type& key);
	const_iterator upper_bound(const key_type& key) const;

	// observer

	key_compare	  key_comp() const;
	value_compare value_comp() const;

	// set comparison

	template <typename Key1, typename Compare1, typename A1>
	friend bool
	operator==(const set<Key1, Compare1, A1>&, const set<Key1, Compare1, A1>&);
	template <typename Key1, typename Compare1, typename A1>
	friend bool
	operator<(const set<Key1, Compare1, A1>&, const set<Key1, Compare1, A1>&);
};

// constructor

template <class Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set() : m_tree()
{
#ifdef DEBUG
	std::cout << "set default constructor" << std::endl;
#endif
}

template <class Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set(
	const key_compare&	  comp,
	const allocator_type& alloc)
	: m_tree(comp, alloc)
{
#ifdef DEBUG
	std::cout << "set empty constructor" << std::endl;
#endif
}

template <class Key, class Compare, class Allocator>
template <class InputIterator>
set<Key, Compare, Allocator>::set(
	InputIterator		  first,
	InputIterator		  last,
	const key_compare&	  key_compare,
	const allocator_type& alloc)
	: m_tree(key_compare, alloc)
{
#ifdef DEBUG
	std::cout << "set range constructor" << std::endl;
#endif
	m_tree.insert(first, last);
}

template <class Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set(const set& other) : m_tree(other.m_tree)
{
#ifdef DEBUG
	std::cout << "set copy constructor" << std::endl;
#endif
}

template <class Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::~set()
{
#ifdef DEBUG
	std::cout << "set destructor" << std::endl;
#endif
	clear();
}

template <class Key, class Compare, class Allocator>
set<Key, Compare, Allocator>&
set<Key, Compare, Allocator>::operator=(const set& other)
{
#ifdef DEBUG
	std::cout << "set operator= (copy assignment)" << std::endl;
#endif
	if (this != &other)
	{
#ifdef DEBUG
		std::cout << "sets are not identical (copying elemements)" << std::endl;
#endif
		set tmp(other);
		swap(tmp);
		return *this;
	}
	return *this;
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::allocator_type
set<Key, Compare, Allocator>::get_allocator() const
{
	return m_tree.get_allocator();
}

// iterators

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator
set<Key, Compare, Allocator>::begin()
{
	return m_tree.begin();
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_iterator
set<Key, Compare, Allocator>::begin() const
{
	return m_tree.begin();
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator
set<Key, Compare, Allocator>::end()
{
	return m_tree.end();
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_iterator
set<Key, Compare, Allocator>::end() const
{
	return m_tree.end();
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::reverse_iterator
set<Key, Compare, Allocator>::rbegin()
{
	return m_tree.rbegin();
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_reverse_iterator
set<Key, Compare, Allocator>::rbegin() const
{
	return m_tree.rbegin();
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::reverse_iterator
set<Key, Compare, Allocator>::rend()
{
	return m_tree.rend();
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_reverse_iterator
set<Key, Compare, Allocator>::rend() const
{
	return m_tree.rend();
}

// capacity

template <class Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::empty() const
{
	return m_tree.empty();
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::size_type
set<Key, Compare, Allocator>::size() const
{
	return m_tree.size();
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::size_type
set<Key, Compare, Allocator>::max_size() const
{
	return m_tree.max_size();
}

// modifiers

template <class Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::clear()
{
	m_tree.clear();
}

template <class Key, class Compare, class Allocator>
pair<typename set<Key, Compare, Allocator>::iterator, bool>
set<Key, Compare, Allocator>::insert(const value_type& value)
{
	return m_tree.insert(value);
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator
set<Key, Compare, Allocator>::insert(iterator pos, const value_type& value)
{
	return m_tree.insert(pos, value);
}

template <class Key, class Compare, class Allocator>
template <class InputIterator>
void set<Key, Compare, Allocator>::insert(
	InputIterator first,
	InputIterator last)
{
	m_tree.insert(first, last);
}

template <class Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::erase(iterator pos)
{
	m_tree.erase(pos);
}

template <class Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::erase(iterator first, iterator last)
{
	m_tree.erase(first, last);
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::size_type
set<Key, Compare, Allocator>::erase(const key_type& key)
{
	return m_tree.erase(key);
}

template <class Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::swap(set& other)
{
	m_tree.swap(other.m_tree);
}

// lookup

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::size_type
set<Key, Compare, Allocator>::count(const key_type& key) const
{
	return m_tree.count(key);
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator
set<Key, Compare, Allocator>::find(const key_type& key)
{
	return m_tree.find(key);
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_iterator
set<Key, Compare, Allocator>::find(const key_type& key) const
{
	return m_tree.find(key);
}

template <class Key, class Compare, class Allocator>
pair<
	typename set<Key, Compare, Allocator>::iterator,
	typename set<Key, Compare, Allocator>::iterator >
set<Key, Compare, Allocator>::equal_range(const key_type& key)
{
	return m_tree.equal_range(key);
}

template <class Key, class Compare, class Allocator>
pair<
	typename set<Key, Compare, Allocator>::const_iterator,
	typename set<Key, Compare, Allocator>::const_iterator >
set<Key, Compare, Allocator>::equal_range(const key_type& key) const
{
	return m_tree.equal_range(key);
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator
set<Key, Compare, Allocator>::lower_bound(const key_type& key)
{
	return m_tree.lower_bound(key);
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_iterator
set<Key, Compare, Allocator>::lower_bound(const key_type& key) const
{
	return m_tree.lower_bound(key);
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator
set<Key, Compare, Allocator>::upper_bound(const key_type& key)
{
	return m_tree.upper_bound(key);
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_iterator
set<Key, Compare, Allocator>::upper_bound(const key_type& key) const
{
	return m_tree.upper_bound(key);
}

// observer

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::key_compare
set<Key, Compare, Allocator>::key_comp() const
{
	return m_tree.key_comp();
}

template <class Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::value_compare
set<Key, Compare, Allocator>::value_comp() const
{
	return value_compare(m_tree.key_comp());
}

// relational operators

template <class Key, class Compare, class Allocator>
bool operator==(
	const set<Key, Compare, Allocator>& lhs,
	const set<Key, Compare, Allocator>& rhs)
{
	return lhs.m_tree == rhs.m_tree;
}

template <class Key, class Compare, class Allocator>
bool operator!=(
	const set<Key, Compare, Allocator>& lhs,
	const set<Key, Compare, Allocator>& rhs)
{
	return !(lhs == rhs);
}

template <class Key, class Compare, class Allocator>
bool operator<(
	const set<Key, Compare, Allocator>& lhs,
	const set<Key, Compare, Allocator>& rhs)
{
	return lhs.m_tree < rhs.m_tree;
}

template <class Key, class Compare, class Allocator>
bool operator<=(
	const set<Key, Compare, Allocator>& lhs,
	const set<Key, Compare, Allocator>& rhs)
{
	return !(rhs < lhs);
}

template <class Key, class Compare, class Allocator>
bool operator>(
	const set<Key, Compare, Allocator>& lhs,
	const set<Key, Compare, Allocator>& rhs)
{
	return rhs < lhs;
}

template <class Key, class Compare, class Allocator>
bool operator>=(
	const set<Key, Compare, Allocator>& lhs,
	const set<Key, Compare, Allocator>& rhs)
{
	return !(lhs < rhs);
}

// specialization for ft::swap(set)

template <class Key, class T, class Compare, class Allocator>
void swap(set<Key, Compare, Allocator>& lhs, set<Key, Compare, Allocator>& rhs)
{
	lhs.swap(rhs);
}

} // namespace ft

#endif // SET_HPP
