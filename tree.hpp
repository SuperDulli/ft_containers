#ifndef TREE_HPP
#define TREE_HPP

#include "iterator.hpp"
#include "pair.hpp"
#include <memory> // allocator

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
	Value value;

	static RB_tree_node* minimum(RB_tree_node* node)
	{
		while (node->left != NULL)
			node = node->left;
		return node;
	}

	static const RB_tree_node* minimum(const RB_tree_node* node)
	{
		while (node->left != NULL)
			node = node->left;
		return node;
	}

	static RB_tree_node* maximum(RB_tree_node* node)
	{
		while (node->right != NULL)
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

	static RB_tree_node* previous(const RB_tree_node* node)
	{
		if (node->left)
			return maximum(node->left);
		while (node->parent && node == node->parent->left)
			node = node->parent;
		return node->parent;
	}
};

// iterator

template <typename T>
struct RB_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
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
	: ft::iterator<ft::bidirectional_iterator_tag, T> {
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
		std::cout << "RB tree iterator conversion" << std::endl;
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

// tree

template <
	class Key,
	class Value,
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
	RB_tree() : m_root(), m_node_count() {}
	RB_tree(
		const key_compare&	  comp,
		const allocator_type& alloc = allocator_type())
		: m_alloc(alloc), m_key_compare(comp), m_root(), m_node_count()
	{}
	RB_tree(const RB_tree& other)
		: m_alloc(other.m_alloc), m_key_compare(other.m_key_compare)
	{
		*this = other;
	}

	~RB_tree()
	{
		m_erase(m_root);
	}

	RB_tree& operator=(const RB_tree& other)
	{
		m_erase(m_root);
		m_alloc = other.m_alloc;
		m_key_compare = other.m_key_compare;
		m_root = other.m_root;
		m_node_count = other.m_node_count;
	}

	void insert(value_type value)
	{
		node_type node = m_new_node(value);
		m_insert(node);
	}

private:
	node_allocator m_alloc;
	key_compare	   m_key_compare;
	node_type	   m_root;
	size_type	   m_node_count;

	node_type m_new_node(value_type value);

	void m_insert(node_type node);
	void m_erase(node_type node);
};

// implementation of Red-Black tree

template <class Key, class Value, class Compare, class Allocator>
typename RB_tree<Key, Value, Compare, Allocator>::node_type
RB_tree<Key, Value, Compare, Allocator>::m_new_node(value_type value)
{
	node_type node = m_alloc.allocate(1);
	node->color = RED;
	node->value = value;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
}

template <class Key, class Value, class Compare, class Allocator>
void RB_tree<Key, Value, Compare, Allocator>::m_erase(node_type node)
{
	// TODO: delete subtree
	(void) node;
}

template <class Key, class Value, class Compare, class Allocator>
void RB_tree<Key, Value, Compare, Allocator>::m_insert(node_type node)
{
	if (!m_root)
	{
		m_root = node;
	}
}

#endif // TREE_HPP
