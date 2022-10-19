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
	typedef std::size_t			   size_type;
	typedef std::ptrdiff_t		   difference_type;
	typedef Compare				   key_compare;
	typedef Allocator			   allocator_type;
	typedef value_type&			   reference;
	typedef const value_type&	   const_reference;

private:
	typedef RB_tree<key_type, value_type, key_compare, allocator_type>
		tree_type;

	tree_type m_tree;

public:
	typedef typename Allocator::pointer				   pointer;
	typedef typename Allocator::const_pointer		   const_pointer;
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

	T&		 at(const key_type& key);
	const T& at(const key_type& key) const;
	T&		 operator[](const key_type& key);

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
	iterator  erase(iterator pos);
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
};

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
