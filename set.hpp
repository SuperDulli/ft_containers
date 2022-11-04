#ifndef SET_HPP
#define SET_HPP

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

	// set comparison

	template <typename Key1, typename Compare1, typename A1>
	friend bool operator==(
		const set<Key1, Compare1, A1>&,
		const set<Key1, Compare1, A1>&);
	template <typename Key1, typename Compare1, typename A1>
	friend bool operator<(
		const set<Key1, Compare1, A1>&,
		const set<Key1, Compare1, A1>&);
};

} // namespace ft

#endif // SET_HPP
