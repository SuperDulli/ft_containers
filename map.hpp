#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef>	  // size_t, ptrdiff_t
#include <functional> // less
#include <memory>	  // allocator

#include "pair.hpp"
#include "tree.hpp"

namespace ft
{

template <
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
public:
	typedef Key					   key_type;
	typedef T					   mapped_type;
	typedef ft::pair<const Key, T> value_type;

	typedef Compare	  key_compare;
	typedef Allocator allocator_type;

private:
	typedef
		typename Allocator::template rebind<value_type>::other pair_alloc_type;

	typedef RB_tree<
		key_type,
		value_type,
		ft::SelectFirst<value_type>,
		key_compare,
		pair_alloc_type>
		tree_type;

	tree_type m_tree;

public:
	typedef typename pair_alloc_type::pointer		   pointer;
	typedef typename pair_alloc_type::const_pointer	   const_pointer;
	typedef typename pair_alloc_type::reference		   reference;
	typedef typename pair_alloc_type::const_reference  const_reference;
	typedef typename tree_type::size_type			   size_type;
	typedef typename tree_type::difference_type		   difference_type;
	typedef typename tree_type::iterator			   iterator;
	typedef typename tree_type::const_iterator		   const_iterator;
	typedef typename tree_type::reverse_iterator	   reverse_iterator;
	typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

public:
	class value_compare
	{
		friend class map<Key, T, Compare, Allocator>;

	public:
		typedef bool	   result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;

	public:
		result_type operator()(
			const first_argument_type&	lhs,
			const second_argument_type& rhs) const
		{
			return m_compare(lhs.first, rhs.first);
		}

	protected:
		key_compare m_compare;

		value_compare(key_compare c) : m_compare(c){};
	};

	// constructor

	map();
	explicit map(
		const key_compare&	  comp,
		const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	map(InputIterator first,
		InputIterator last,
		const key_compare& = key_compare(),
		const allocator_type& alloc = allocator_type());
	map(const map& other);

	~map();

	map&		   operator=(const map& other);
	allocator_type get_allocator() const;

	// element access

	mapped_type& operator[](const key_type& key);

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
	void	  swap(map& other);

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

	// map comparison

	template <typename Key1, typename T1, typename Compare1, typename A1>
	friend bool operator==(
		const map<Key1, T1, Compare1, A1>&,
		const map<Key1, T1, Compare1, A1>&);
	template <typename Key1, typename T1, typename Compare1, typename A1>
	friend bool operator<(
		const map<Key1, T1, Compare1, A1>&,
		const map<Key1, T1, Compare1, A1>&);
};

// constructor

template <class Key, class T, class Compare, class Allocator>
map<Key, T, Compare, Allocator>::map() : m_tree()
{
#ifdef DEBUG
	std::cout << "map default constructor" << std::endl;
#endif
}

template <class Key, class T, class Compare, class Allocator>
map<Key, T, Compare, Allocator>::map(
	const key_compare&	  comp,
	const allocator_type& alloc)
	: m_tree(comp, alloc)
{
#ifdef DEBUG
	std::cout << "map empty constructor" << std::endl;
#endif
}

template <class Key, class T, class Compare, class Allocator>
template <class InputIterator>
map<Key, T, Compare, Allocator>::map(
	InputIterator		  first,
	InputIterator		  last,
	const key_compare&	  key_compare,
	const allocator_type& alloc)
	: m_tree(key_compare, alloc)
{
#ifdef DEBUG
	std::cout << "map range constructor" << std::endl;
#endif
	m_tree.insert(first, last);
}

template <class Key, class T, class Compare, class Allocator>
map<Key, T, Compare, Allocator>::map(const map& other) : m_tree(other.m_tree)
{
#ifdef DEBUG
	std::cout << "map copy constructor" << std::endl;
#endif
}

template <class Key, class T, class Compare, class Allocator>
map<Key, T, Compare, Allocator>::~map()
{
#ifdef DEBUG
	std::cout << "map destructor" << std::endl;
#endif
	// clear();
}

template <class Key, class T, class Compare, class Allocator>
map<Key, T, Compare, Allocator>&
map<Key, T, Compare, Allocator>::operator=(const map& other)
{
#ifdef DEBUG
	std::cout << "map operator= (copy assignment)" << std::endl;
#endif
	if (this != &other)
	{
#ifdef DEBUG
		std::cout << "maps are not identical (copying elemements)" << std::endl;
#endif
		map tmp(other);
		swap(tmp);
		return *this;
	}
	return *this;
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::allocator_type
map<Key, T, Compare, Allocator>::get_allocator() const
{
	return m_tree.get_allocator();
}

// element access

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::mapped_type&
map<Key, T, Compare, Allocator>::operator[](const key_type& key)
{
	iterator it = lower_bound(key);
	if (it == end() || key_comp()(key, (*it).first))
		it = insert(it, value_type(key, mapped_type()));
	return (*it).second;
}

// iterators

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::iterator
map<Key, T, Compare, Allocator>::begin()
{
	return m_tree.begin();
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::const_iterator
map<Key, T, Compare, Allocator>::begin() const
{
	return m_tree.begin();
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::iterator
map<Key, T, Compare, Allocator>::end()
{
	return m_tree.end();
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::const_iterator
map<Key, T, Compare, Allocator>::end() const
{
	return m_tree.end();
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::reverse_iterator
map<Key, T, Compare, Allocator>::rbegin()
{
	return m_tree.rbegin();
}
template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::const_reverse_iterator
map<Key, T, Compare, Allocator>::rbegin() const
{
	return m_tree.rbegin();
}
template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::reverse_iterator
map<Key, T, Compare, Allocator>::rend()
{
	return m_tree.rend();
}
template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::const_reverse_iterator
map<Key, T, Compare, Allocator>::rend() const
{
	return m_tree.rend();
}

// capacity

template <class Key, class T, class Compare, class Allocator>
bool map<Key, T, Compare, Allocator>::empty() const
{
	return m_tree.empty();
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::size_type
map<Key, T, Compare, Allocator>::size() const
{
	return m_tree.size();
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::size_type
map<Key, T, Compare, Allocator>::max_size() const
{
	return m_tree.max_size();
}

// modifiers

template <class Key, class T, class Compare, class Allocator>
void map<Key, T, Compare, Allocator>::clear()
{
	// TODO: clear map
}

template <class Key, class T, class Compare, class Allocator>
ft::pair<typename map<Key, T, Compare, Allocator>::iterator, bool>
map<Key, T, Compare, Allocator>::insert(const value_type& value)
{
	return m_tree.insert(value);
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::iterator
map<Key, T, Compare, Allocator>::insert(iterator pos, const value_type& value)
{
	return m_tree.insert(pos, value);
}

template <class Key, class T, class Compare, class Allocator>
template <class InputIterator>
void map<Key, T, Compare, Allocator>::insert(
	InputIterator first,
	InputIterator last)
{
	return m_tree.insert(first, last);
}

template <class Key, class T, class Compare, class Allocator>
void map<Key, T, Compare, Allocator>::erase(iterator pos)
{
	m_tree.erase(pos);
}

template <class Key, class T, class Compare, class Allocator>
void map<Key, T, Compare, Allocator>::erase(iterator first, iterator last)
{
	m_tree.erase(first, last);
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::size_type
map<Key, T, Compare, Allocator>::erase(const key_type& key)
{
	return m_tree.erase(key);
}

template <class Key, class T, class Compare, class Allocator>
void map<Key, T, Compare, Allocator>::swap(map& other)
{
	m_tree.swap(other.m_tree);
}

// look up

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::size_type
map<Key, T, Compare, Allocator>::count(const key_type& key) const
{
	return m_tree.count(key);
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::iterator
map<Key, T, Compare, Allocator>::find(const key_type& key)
{
	return m_tree.find(key);
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::const_iterator
map<Key, T, Compare, Allocator>::find(const key_type& key) const
{
	return m_tree.find(key);
}

template <class Key, class T, class Compare, class Allocator>
ft::pair<
	typename map<Key, T, Compare, Allocator>::iterator,
	typename map<Key, T, Compare, Allocator>::iterator>
map<Key, T, Compare, Allocator>::equal_range(const key_type& key)
{
	return m_tree.equal_range(key);
}

template <class Key, class T, class Compare, class Allocator>
ft::pair<
	typename map<Key, T, Compare, Allocator>::const_iterator,
	typename map<Key, T, Compare, Allocator>::const_iterator>
map<Key, T, Compare, Allocator>::equal_range(const key_type& key) const
{
	return m_tree.equal_range(key);
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::iterator
map<Key, T, Compare, Allocator>::lower_bound(const key_type& key)
{
	return m_tree.lower_bound(key);
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::const_iterator
map<Key, T, Compare, Allocator>::lower_bound(const key_type& key) const
{
	return m_tree.lower_bound(key);
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::iterator
map<Key, T, Compare, Allocator>::upper_bound(const key_type& key)
{
	return m_tree.upper_bound(key);
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::const_iterator
map<Key, T, Compare, Allocator>::upper_bound(const key_type& key) const
{
	return m_tree.upper_bound(key);
}

// observer

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::key_compare
map<Key, T, Compare, Allocator>::key_comp() const
{
	return m_tree.key_comp();
}

template <class Key, class T, class Compare, class Allocator>
typename map<Key, T, Compare, Allocator>::value_compare
map<Key, T, Compare, Allocator>::value_comp() const
{
	return value_compare(m_tree.key_comp());
}

// relational operators

template <class Key, class T, class Compare, class Allocator>
bool operator==(
	const ft::map<Key, T, Compare, Allocator>& lhs,
	const ft::map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.m_tree == rhs.m_tree;
}

template <class Key, class T, class Compare, class Allocator>
bool operator!=(
	const ft::map<Key, T, Compare, Allocator>& lhs,
	const ft::map<Key, T, Compare, Allocator>& rhs)
{
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Allocator>
bool operator<(
	const ft::map<Key, T, Compare, Allocator>& lhs,
	const ft::map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.m_tree < rhs.m_tree;
}

template <class Key, class T, class Compare, class Allocator>
bool operator<=(
	const ft::map<Key, T, Compare, Allocator>& lhs,
	const ft::map<Key, T, Compare, Allocator>& rhs)
{
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Allocator>
bool operator>(
	const ft::map<Key, T, Compare, Allocator>& lhs,
	const ft::map<Key, T, Compare, Allocator>& rhs)
{
	return rhs < lhs;
}

template <class Key, class T, class Compare, class Allocator>
bool operator>=(
	const ft::map<Key, T, Compare, Allocator>& lhs,
	const ft::map<Key, T, Compare, Allocator>& rhs)
{
	return !(lhs < rhs);
}

// specialization for ft::swap(map)

template <class Key, class T, class Compare, class Allocator>
void swap(
	ft::map<Key, T, Compare, Allocator>& lhs,
	ft::map<Key, T, Compare, Allocator>& rhs)
{
	lhs.swap(rhs);
}

} // namespace ft

#endif // MAP_HPP
