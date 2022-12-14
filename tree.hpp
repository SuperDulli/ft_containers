#ifndef TREE_HPP
#define TREE_HPP

#include <algorithm> // swap
#include <iomanip>
#include <iostream>
#include <memory> // allocator
#include <string>

#include "algorithm.hpp" // equal, lexicographical_compare
#include "iterator.hpp"
#include "pair.hpp"
#include "utility.hpp"

namespace ft
{

enum RB_tree_color
{
	RED = false,
	BLACK = true
};

// node

template <typename Value>
struct RB_tree_node {
	RB_tree_color color;
	RB_tree_node* parent;
	RB_tree_node* left;
	RB_tree_node* right;
	Value		  value;

	static RB_tree_node* minimum(RB_tree_node* node)
	{
		while (node->left != NULL)
			node = node->left;
		return node;
	}

	static const RB_tree_node* minimum(const RB_tree_node* node)
	{
		while (node && node->left != NULL)
			node = node->left;
		return node;
	}

	static RB_tree_node* maximum(RB_tree_node* node)
	{
		while (node && node->right != NULL)
			node = node->right;
		return node;
	}

	static const RB_tree_node* maximum(const RB_tree_node* node)
	{
		while (node->right != NULL)
			node = node->right;
		return node;
	}

	static RB_tree_node* next(RB_tree_node* node)
	{
		if (node->right)
			return minimum(node->right);
		while (node->parent && node == node->parent->right)
			node = node->parent;
		return node->parent;
	}

	static const RB_tree_node* next(const RB_tree_node* node)
	{
		return next(const_cast<RB_tree_node*>(node));
	}

	static RB_tree_node* previous(RB_tree_node* node)
	{
		if (node->left)
			return maximum(node->left);
		while (node->parent && node == node->parent->left)
			node = node->parent;
		return node->parent;
	}

	static const RB_tree_node* previous(const RB_tree_node* node)
	{
		return previous(const_cast<RB_tree_node*>(node));
	}
};

// iterator

template <typename T>
struct RB_tree_iterator : ft::iterator<std::bidirectional_iterator_tag, T> {
	typedef typename RB_tree_iterator<T>::pointer	pointer;
	typedef typename RB_tree_iterator<T>::reference reference;

	typedef RB_tree_iterator<T> self;
	typedef RB_tree_node<T>*	node_type;

	node_type m_node;

	RB_tree_iterator() : m_node() {}

	explicit RB_tree_iterator(node_type node) : m_node(node) {}

	reference operator*() const
	{
		return m_node->value;
	}

	pointer operator->() const
	{
		return &m_node->value;
	}

	self& operator++()
	{
		m_node = RB_tree_node<T>::next(m_node);
		return *this;
	}

	self operator++(int)
	{
		self tmp = *this;
		m_node = RB_tree_node<T>::next(m_node);
		return tmp;
	}

	self& operator--()
	{
		m_node = RB_tree_node<T>::previous(m_node);
		return *this;
	}

	self operator--(int)
	{
		self tmp = *this;
		m_node = RB_tree_node<T>::previous(m_node);
		return tmp;
	}

	bool operator==(const self& other) const
	{
		return m_node == other.m_node;
	}

	bool operator!=(const self& other) const
	{
		return m_node != other.m_node;
	}
};

template <typename T>
struct RB_tree_const_iterator
	: ft::iterator<std::bidirectional_iterator_tag, T> {
	typedef typename RB_tree_iterator<const T>::pointer	  pointer;
	typedef typename RB_tree_iterator<const T>::reference reference;

	typedef RB_tree_iterator<T> iterator;

	typedef RB_tree_const_iterator<T> self;
	typedef const RB_tree_node<T>*	  node_type;

	node_type m_node;

	RB_tree_const_iterator() : m_node() {}

	explicit RB_tree_const_iterator(node_type node) : m_node(node) {}

	// allow conversion from iterator to const iterator
	RB_tree_const_iterator(const iterator& it) : m_node(it.m_node)
	{
#ifdef DEBUG
	// std::cout << "RB tree iterator conversion" << std::endl;
#endif
	}

	reference operator*() const
	{
		return m_node->value;
	}

	pointer operator->() const
	{
		return &m_node->value;
	}

	self& operator++()
	{
		m_node = RB_tree_node<T>::next(m_node);
		return *this;
	}

	self operator++(int)
	{
		self tmp = *this;
		m_node = RB_tree_node<T>::next(m_node);
		return tmp;
	}

	self& operator--()
	{
		m_node = RB_tree_node<T>::previous(m_node);
		return *this;
	}

	self operator--(int)
	{
		self tmp = *this;
		m_node = RB_tree_node<T>::previous(m_node);
		return tmp;
	}

	bool operator==(const self& other) const
	{
		return m_node == other.m_node;
	}

	bool operator!=(const self& other) const
	{
		return m_node != other.m_node;
	}
};

// comparing iterators

template <typename T>
bool operator==(
	const RB_tree_iterator<T>&		 lhs,
	const RB_tree_const_iterator<T>& rhs)
{
	return lhs.m_node == rhs.m_node;
}

template <typename T>
bool operator!=(
	const RB_tree_iterator<T>&		 lhs,
	const RB_tree_const_iterator<T>& rhs)
{
	return lhs.m_node != rhs.m_node;
}

// tree

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator = std::allocator<Value> >
class RB_tree
{
private:
	typedef typename Allocator::template rebind<RB_tree_node<Value> >::other
		node_allocator;

public:
	typedef Key								key_type;
	typedef Value							value_type;
	typedef Compare							key_compare;
	typedef value_type*						pointer;
	typedef const value_type				const_pointer;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef RB_tree_node<value_type>*		node_type;
	typedef const RB_tree_node<value_type>* const_node_type;
	typedef size_t							size_type;
	typedef ptrdiff_t						difference_type;
	typedef Allocator						allocator_type;

	typedef RB_tree_iterator<value_type>	   iterator;
	typedef RB_tree_const_iterator<value_type> const_iterator;

	typedef ft::reverse_iterator<iterator>		 reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

public:
	RB_tree() : m_alloc(), m_key_compare(), m_header(), m_node_count(0)
	{
		m_initalize();
	}
	RB_tree(
		const key_compare&	  comp,
		const allocator_type& alloc = allocator_type())
		: m_alloc(alloc), m_key_compare(comp), m_header(), m_node_count(0)
	{
		m_initalize();
	}
	RB_tree(const RB_tree& other)
		: m_alloc(other.m_alloc), m_key_compare(other.m_key_compare), m_header()
	{
		m_initalize();
		*this = other;
	}

	~RB_tree()
	{
		clear();
		m_destroy_NIL(NIL);
	}

	RB_tree& operator=(const RB_tree& other);

	ft::pair<iterator, bool> insert(const value_type& value)
	{
		// node_type node = m_new_node(value);
		return m_insert(value);
	}

	iterator insert(iterator pos, const value_type& value)
	{
		iterator result;
		if (pos == end())
		{
			node_type right = RB_tree_node<Value>::maximum(m_header.left);
			if (size() > 0 && m_key_compare(s_key(right), KeyOfValue()(value)))
			{
				result = m_add_child(right, value);
				m_insert_fixup(result.m_node);
				return result;
			}
			else
				return m_insert(value).first;
		}
		else if (m_key_compare(KeyOfValue()(value), s_key(pos.m_node)))
		{
			// try insert before the hint
			iterator before = pos;
			if (pos == begin())
			{
				result = m_add_child(pos.m_node, value);
				m_insert_fixup(result.m_node);
				return result;
			}
			else if (m_key_compare(
						 s_key((--before).m_node), KeyOfValue()(value)))
			{
				if (!(before.m_node)->right)
				{
					result = m_add_child(before.m_node, value);
					m_insert_fixup(result.m_node);
					return result;
				}
				else if (!(pos.m_node)->left)
				{
					result = m_add_child(pos.m_node, value);
					m_insert_fixup(result.m_node);
					return result;
				}
			}
		}
		// ignore hint
#ifdef DEBUG
		std::cout << "hint ignored" << std::endl;
#endif
		return m_insert(value).first;
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			insert(*first);
			++first;
		}
	}

	void erase(iterator pos)
	{
		node_type node = pos.m_node;
		m_remove(node);
		m_destroy_node(node);
	}

	void erase(iterator first, iterator last)
	{
		if (first == begin() && last == end())
		{
			clear();
			return;
		}
		while (first != last)
		{
			erase(first++);
			// important to use postfix increment because iterator becomes
			// invalid after erase
			// ++first; // segfault
		}
	}

	size_type erase(const key_type& key)
	{
		iterator pos = find(key);
		if (pos == end())
			return 0;
		erase(pos);
		return 1;
	}

	void clear()
	{
		m_erase(m_root());
		m_root() = NULL;
		m_node_count = 0;
	}

	void swap(RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& other)
	{
		if (!m_root())
		{
			if (other.m_root())
			{
				this->m_set_root(other.m_root());
				other.m_root() = NULL;
			}
		}
		else if (!other.m_root())
		{
			other.m_set_root(m_root());
			m_root() = NULL;
		}
		else
		{
			std::swap(m_root(), other.m_root());
			this->m_set_root(m_root());
			other.m_set_root(other.m_root());
		}
		std::swap(m_node_count, other.m_node_count);
		std::swap(m_key_compare, other.m_key_compare);
		std::swap(NIL, other.NIL);
		std::swap(m_alloc, other.m_alloc);
	}

	allocator_type get_allocator() const
	{
		return allocator_type(m_alloc);
	}

	// capacity

	bool empty() const
	{
		return begin() == end();
	}

	size_type size() const
	{
		return m_node_count;
	}

	size_type max_size() const
	{
		return get_allocator().max_size();
	}

	// lookup

	iterator find(const key_type& key)
	{
		iterator it = lower_bound(key);
		if (it == end() || m_key_compare(key, s_key(it.m_node)))
			return end();
		return it;
	}

	const_iterator find(const key_type& key) const
	{
		const_iterator it = lower_bound(key);
		if (it == end() || m_key_compare(key, s_key(it.m_node)))
			return end();
		return it;
	}

	size_type count(const key_type& key) const
	{
		ft::pair<const_iterator, const_iterator> pair = equal_range(key);
		const size_type n = std::distance(pair.first, pair.second);
		return n;
	}

	iterator lower_bound(const key_type& key)
	{
		return m_lower_bound(m_root(), end().m_node, key);
	}

	const_iterator lower_bound(const key_type& key) const
	{
		return m_lower_bound(m_root(), end().m_node, key);
	}

	iterator upper_bound(const key_type& key)
	{
		return m_upper_bound(m_root(), end().m_node, key);
	}

	const_iterator upper_bound(const key_type& key) const
	{
		return m_upper_bound(m_root(), end().m_node, key);
	}

	ft::pair<iterator, iterator> equal_range(const key_type& key);
	ft::pair<const_iterator, const_iterator>
	equal_range(const key_type& key) const;

	// iterator

	iterator begin()
	{
		if (!m_header.left)
			return end();
		return iterator(RB_tree_node<Value>::minimum(m_header.left));
	}

	const_iterator begin() const
	{
		if (!m_header.left)
			return end();
		return const_iterator(RB_tree_node<Value>::minimum(m_header.left));
	}

	iterator end()
	{
		return iterator(&m_header);
	}

	const_iterator end() const
	{
		return const_iterator(&m_header);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	// observers

	key_compare key_comp() const
	{
		return m_key_compare;
	}

private:
	node_allocator		m_alloc;
	key_compare			m_key_compare;
	RB_tree_node<Value> m_header; // special node for iterator purposes
	node_type			NIL;
	size_type			m_node_count;

	static const_reference s_value(const_node_type node)
	{
		return node->value;
	}

	static const key_type& s_key(const_node_type node)
	{
		return KeyOfValue()(s_value(node));
	}

	void m_initalize()
	{
		m_header.color = RED;
		m_header.parent = NULL;
		m_header.left = NULL;
		m_header.right = NULL;

		NIL = m_alloc.allocate(1);
		// NIL->color = BLACK;
		// NIL->parent = NULL;
		// NIL->left = NULL;
		// NIL->right = NULL;
		m_set_NIL(NIL);
	}

	void m_set_NIL(node_type& node)
	{
		NIL->color = BLACK;
		NIL->parent = NULL;
		NIL->left = NULL;
		NIL->right = NULL;
		node = NIL;
	}

	node_type& m_root()
	{
		return m_header.left;
	}

	const_node_type m_root() const
	{
		return m_header.left;
	}

	void m_set_root(node_type node)
	{
		m_root() = node;
		node->parent = &m_header;
	}

	node_type m_new_node(value_type value);
	void	  m_destroy_node(node_type node);
	void	  m_destroy_NIL(node_type node);
	node_type m_clone_node(const_node_type value);
	node_type m_copy(const_node_type node, node_type parent);
	void	  m_recolor(node_type node);

	ft::pair<iterator, bool> m_insert(value_type value);
	void					 m_insert_fixup(node_type node);
	iterator				 m_add_child(node_type parent, value_type value);

	void m_left_rotate(node_type node);
	void m_right_rotate(node_type node);

	void m_transplant(node_type u, node_type v);
	void m_remove(node_type node);
	void m_remove_fixup(node_type node);

	void m_erase(node_type node);

	iterator
	m_lower_bound(node_type left, node_type right, const key_type& key);
	const_iterator m_lower_bound(
		const_node_type left,
		const_node_type right,
		const key_type& key) const;

	iterator
	m_upper_bound(node_type left, node_type right, const key_type& key);
	const_iterator m_upper_bound(
		const_node_type left,
		const_node_type right,
		const key_type& key) const;

public:
	// debug

	bool	   verify() const;
	node_type& get_root()
	{
		return m_root();
	}
	const_node_type get_root() const
	{
		return m_root();
	}

private:
	ft::pair<bool, int> m_check_subtree(const_node_type node) const;
};

// implementation of Red-Black tree

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>&
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::operator=(
	const RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& other)
{
	if (this == &other)
		return *this;
	if (this->m_root())
		clear();
	m_alloc = other.m_alloc;
	m_key_compare = other.m_key_compare;
	m_node_count = other.m_node_count;
	if (other.m_root())
		this->m_set_root(m_copy(other.m_root(), &m_header));
	return *this;
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::node_type
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_new_node(
	value_type value)
{
	node_type node = m_alloc.allocate(1);
	get_allocator().construct(&node->value, value);
	node->color = RED;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_destroy_node(
	node_type node)
{
	get_allocator().destroy(&node->value);
	m_alloc.deallocate(node, 1);
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_destroy_NIL(
	node_type node)
{
	m_alloc.deallocate(node, 1);
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::node_type
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_clone_node(
	const_node_type node)
{
	node_type clone = m_new_node(node->value);
	clone->color = node->color;
	return clone;
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::node_type
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_copy(
	const_node_type node,
	node_type		parent)
{
	node_type copy = m_clone_node(node);
	copy->parent = parent;
	if (node->right)
	{
		copy->right = m_copy(node->right, copy);
	}
	parent = copy;
	node = node->left;
	while (node)
	{
		node_type y = m_clone_node(node);
		parent->left = y;
		y->parent = parent;
		if (node->right)
			y->right = m_copy(node->right, y);
		parent = y;
		node = node->left;
	}

	return copy;
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_recolor(
	node_type node)
{
	node->color = (node->color == RED) ? BLACK : RED;
	node->left->color = (node->color == BLACK) ? RED : BLACK;
	node->right->color = (node->color == BLACK) ? RED : BLACK;
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
ft::pair<
	typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator,
	bool>
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_insert(value_type value)
{
	iterator it;
	if (!m_root())
	{
		node_type node = m_new_node(value);
		m_set_root(node);
		++m_node_count;
		node->color = BLACK;
		return ft::make_pair(iterator(node), true);
	}
	node_type tmp = m_root();
	node_type previous = m_root();
	while (tmp)
	{
		if (m_key_compare(KeyOfValue()(value), s_key(tmp)))
		{
			previous = tmp;
			tmp = tmp->left;
		}
		else if (m_key_compare(s_key(tmp), KeyOfValue()(value)))
		{
			previous = tmp;
			tmp = tmp->right;
		}
		else
		{
			return ft::make_pair(iterator(tmp), false);
		}
	}
	it = m_add_child(previous, value);
	m_insert_fixup(it.m_node);

	return ft::make_pair(it, true);
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_add_child(
	node_type  parent,
	value_type value)
{
	node_type node = m_new_node(value);
	if (m_key_compare(KeyOfValue()(value), s_key(parent)))
	{
		parent->left = node;
		node->parent = parent;
	}
	else
	{
		parent->right = node;
		node->parent = parent;
	}
	++m_node_count;
	return (iterator(node));
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_insert_fixup(
	node_type node)
{
	// fix color of the nodes TODO: move to function
	while (node != m_root() && node->parent->color == RED)
	{
		if (node->parent->parent && node->parent == node->parent->parent->left)
		{
			// node->parent is left child
			node_type uncle = node->parent->parent->right;
			if (uncle && uncle->color == RED)
			{
				// case 1
				// std::cout << "case 1 (left)" << std::endl;
				node_type grandparent = node->parent->parent;
				m_recolor(grandparent);
				node = grandparent;
			}
			else
			{
				if (node == node->parent->right)
				{
					// case 2
					// std::cout << "case 2 (left)" << std::endl;
					node = node->parent;
					m_left_rotate(node);
				}
				// case 3
				// std::cout << "case 3 (left)" << std::endl;
				m_right_rotate(node->parent->parent);
				m_recolor(node->parent);
			}
		}
		else
		{
			node_type uncle = node->parent->parent->left;
			if (uncle && uncle->color == RED)
			{
				// case 1
				// std::cout << "case 1 (right)" << std::endl;
				node_type grandparent = node->parent->parent;
				m_recolor(grandparent);
				node = grandparent;
			}
			else
			{
				if (node == node->parent->left)
				{
					// case 2
					// std::cout << "case 2 (right)" << std::endl;
					node = node->parent;
					m_right_rotate(node);
				}
				// case 3
				// std::cout << "case 3 (right)" << std::endl;
				m_left_rotate(node->parent->parent);
				m_recolor(node->parent);
			}
		}
	}
	m_root()->color = BLACK;
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_left_rotate(
	node_type node)
{
	node_type y = node->right;
	node->right = y->left;
	if (y->left)
		y->left->parent = node;
	y->parent = node->parent;
	if (!node->parent)
		m_set_root(y);
	else if (node == node->parent->left)
		node->parent->left = y;
	else
		node->parent->right = y;
	y->left = node;
	node->parent = y;
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_right_rotate(
	node_type node)
{
	node_type y = node->left;
	node->left = y->right;
	if (y->right)
		y->right->parent = node;
	y->parent = node->parent;
	if (!node->parent)
		m_set_root(y);
	else if (node == node->parent->right)
		node->parent->right = y;
	else
		node->parent->left = y;
	y->right = node;
	node->parent = y;
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_transplant(
	node_type u,
	node_type v)
{
	if (!u->parent)
		m_set_root(v);
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v)
		v->parent = u->parent;
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_remove(
	node_type node)
{
	node_type	  y = node;
	node_type	  x;
	RB_tree_color y_original_color = y->color;
	if (!node->left) // only right child
	{
		x = node->right;
		if (!x)
		{
			m_set_NIL(x);
		}
		m_transplant(node, x);
	}
	else if (!node->right) // only left child
	{
		x = node->left;
		m_transplant(node, node->left);
	}
	else // both childern
	{
		y = RB_tree_node<Value>::minimum(node->right);
		y_original_color = y->color;
		x = y->right;
		if (!x)
		{
			m_set_NIL(x);
		}
		if (y->parent == node) // y is direct child of node
		{
			x->parent = y;
		}
		else
		{
			m_transplant(y, x);
			y->right = node->right;
			y->right->parent = y;
		}
		m_transplant(node, y);
		y->left = node->left;
		y->left->parent = y;
		y->color = node->color;
	}
	if (y_original_color == BLACK && x)
	{
		m_remove_fixup(x);
	}
	if (x == NIL)
	{
		if (x == x->parent->left)
			x->parent->left = NULL;
		else
			x->parent->right = NULL;
	}
	--m_node_count;
}

/**
 * @brief restores the properties of the red black tree.
 *
 * w is sibling of node.
 * 4 cases:
 * 1. w is red.
 * 2. w is black and its both children are black.
 * 3. w is black and its right child is black and left child is red.
 * 4. w is black and its right child is red.
 *
 * @tparam Key
 * @tparam Value
 * @tparam KeyOfValue
 * @tparam Compare
 * @tparam Allocator
 * @param node
 */
template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_remove_fixup(
	node_type node)
{
	node_type w; // sibling of node
	while (node != m_root() && node->color == BLACK)
	{
		if (node == node->parent->left)
		{
			w = node->parent->right;
			if (w->color == RED) // case 1
			{
				w->color = BLACK;
				node->parent->color = RED;
				m_left_rotate(node->parent);
				w = node->parent->right;
			}
			if ((!w->left || w->left->color == BLACK) &&
				(!w->right || w->right->color == BLACK)) // case 2
			{
				w->color = RED;
				node = node->parent;
			}
			else // case 3 and 4
			{
				if (!w->right ||
					(w->right && w->right->color == BLACK)) // case 3
				{
					w->left->color = BLACK;
					w->color = RED;
					m_right_rotate(w);
					w = node->parent->right;
				}
				// case 4
				w->color = node->parent->color;
				node->parent->color = BLACK;
				if (w->right)
					w->right->color = BLACK;
				m_left_rotate(node->parent);
				node = m_root();
			}
		}
		else
		{
			w = node->parent->left;
			if (w->color == RED) // case 1
			{
				w->color = BLACK;
				node->parent->color = RED;
				m_right_rotate(node->parent);
				w = node->parent->left;
			}
			if ((!w->right || w->right->color == BLACK) &&
				(!w->left || w->left->color == BLACK)) // case 2
			{
				w->color = RED;
				node = node->parent;
			}
			else // case 3 and 4
			{
				if ((!w->left ||
					 (w->left && w->left->color == BLACK))) // case 3
				{
					w->right->color = BLACK;
					w->color = RED;
					m_left_rotate(w);
					w = node->parent->left;
				}
				// case 4
				w->color = node->parent->color;
				node->parent->color = BLACK;
				if (w->left)
					w->left->color = BLACK;
				m_right_rotate(node->parent);
				node = m_root();
			}
		}
	}

	node->color = BLACK;
}

/**
 * @brief remove subtree without rebalance
 *
 * @param node root of the subtree
 */
template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_erase(
	node_type node)
{
	while (node)
	{
		m_erase(node->right);
		node_type y = node->left;
		m_destroy_node(node);
		node = y;
	}
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_lower_bound(
	node_type		left,
	node_type		right,
	const key_type& key)
{
	while (left)
	{
		if (!m_key_compare(s_key(left), key))
		{
			right = left;
			left = right->left;
		}
		else
		{
			left = left->right;
		}
	}
	return iterator(right);
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_lower_bound(
	const_node_type left,
	const_node_type right,
	const key_type& key) const
{
	while (left)
	{
		if (!m_key_compare(s_key(left), key))
		{
			right = left;
			left = right->left;
		}
		else
		{
			left = left->right;
		}
	}
	return const_iterator(right);
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_upper_bound(
	node_type		left,
	node_type		right,
	const key_type& key)
{
	while (left)
	{
		if (m_key_compare(key, s_key(left)))
		{
			right = left;
			left = right->left;
		}
		else
		{
			left = left->right;
		}
	}
	return iterator(right);
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_upper_bound(
	const_node_type left,
	const_node_type right,
	const key_type& key) const
{
	while (left)
	{
		if (m_key_compare(key, s_key(left)))
		{
			right = left;
			left = right->left;
		}
		else
		{
			left = left->right;
		}
	}
	return const_iterator(right);
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
ft::pair<
	typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator,
	typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator>
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::equal_range(
	const key_type& key)
{
	node_type left = m_root();
	node_type right = end().m_node;
	while (left)
	{
		if (m_key_compare(s_key(left), key))
			left = left->right;
		else if (m_key_compare(key, s_key(left)))
		{
			right = left;
			left = left->left;
		}
		else
		{
			node_type left_up(left);
			node_type right_up(right);
			right = left;
			left = left->left;
			left_up = left_up->right;
			return ft::make_pair(
				m_lower_bound(left, right, key),
				m_upper_bound(left_up, right_up, key));
		}
	}
	return ft::make_pair(iterator(right), iterator(right));
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
ft::pair<
	typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		const_iterator,
	typename RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		const_iterator>
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::equal_range(
	const key_type& key) const
{
	const_node_type left = m_root();
	const_node_type right = end().m_node;
	while (left)
	{
		if (m_key_compare(s_key(left), key))
			left = left->right;
		else if (m_key_compare(key, s_key(left)))
		{
			right = left;
			left = left->left;
		}
		else
		{
			const_node_type left_up(left);
			const_node_type right_up(right);
			right = left;
			left = left->left;
			left_up = left_up->right;
			return ft::make_pair(
				m_lower_bound(left, right, key),
				m_upper_bound(left_up, right_up, key));
		}
	}
	return ft::make_pair(const_iterator(right), const_iterator(right));
}

/**
 * @brief checks wheter the tree is a valid red black tree.
 *
 * Properties:
 * 1. Every node is either red or black.
 * 2. All leaf nodes are black.
 * 3. A red node does not have a red child.
 * 4. Every path from a node to any of its descentant leaf nodes goes
 * through the same number of black nodes.
 */
template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
bool RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::verify() const
{
	return m_check_subtree(m_root()).first;
}

/**
 * @brief check if the sub tree is a valid red black tree and count the number
 * of black nodes.
 *
 * @return ft::pair<bool, int> valid tree & number of black nodes
 */
template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
ft::pair<bool, int>
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_check_subtree(
	const_node_type node) const
{
	int blackCount;

	if (!node) // leaf
		return ft::make_pair(true, 1);
	if (node->parent && !node->parent->parent && node->color != BLACK) // root
		return ft::make_pair(false, 0);
	if (node->color == RED) // check #3
	{
		blackCount = 0;
		if ((node->left && node->left->color == RED) ||
			(node->right && node->right->color == RED))
		{
			return ft::make_pair(false, 0);
		}
	}
	else
		blackCount = 1;

	ft::pair<bool, int> left = m_check_subtree(node->left);
	ft::pair<bool, int> right = m_check_subtree(node->right);

	if (left.first && right.first && left.second == right.second)
		return ft::make_pair(true, blackCount + left.second);
	return ft::make_pair(false, blackCount + left.second);
}

// non member functions

// relational operators

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
bool operator==(
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
	return (
		lhs.size() == rhs.size() &&
		ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
bool operator!=(
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
	return (!(lhs == rhs));
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
bool operator<(
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
	return ft::lexicographical_compare(
		lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
bool operator<=(
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
	return (!(rhs < lhs));
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
bool operator>(
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
	return (rhs < lhs);
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
bool operator>=(
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
	return (!(lhs < rhs));
}

} // namespace ft

#endif // TREE_HPP
