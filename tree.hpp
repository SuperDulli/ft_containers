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
	Value		  value;

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
	RB_tree() : m_alloc(), m_key_compare(), m_root(), m_node_count(0) {}
	RB_tree(
		const key_compare&	  comp,
		const allocator_type& alloc = allocator_type())
		: m_alloc(alloc), m_key_compare(comp), m_root(), m_node_count(0)
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

	ft::pair<iterator, bool> insert(const value_type& value)
	{
		node_type node = m_new_node(value);
		return m_insert(node);
	}

	// private:
public: // TODO: make tree mamber private
	node_allocator m_alloc;
	key_compare	   m_key_compare;
	node_type	   m_root;
	size_type	   m_node_count;

	static const_reference s_value(const_node_type node)
	{
		return node->value;
	}

	static const key_type& s_key(const_node_type node)
	{
		return KeyOfValue()(s_value(node));
	}

	node_type m_new_node(value_type value);
	void	  m_recolor(node_type node);

	ft::pair<iterator, bool> m_insert(node_type node);
	void					 m_erase(node_type node);

	void m_left_rotate(node_type node);
	void m_right_rotate(node_type node);
};

// implementation of Red-Black tree

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
	// TODO: moc into function
	allocator_type alloc = allocator_type(m_alloc);
	alloc.construct(&node->value, value);
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
void RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_erase(
	node_type node)
{
	// TODO: delete subtree
	(void) node;
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
RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::m_insert(node_type node)
{
	if (!m_root)
	{
		m_root = node;
		++m_node_count;
		node->color = BLACK;
		return ft::make_pair(iterator(node), true);
	}
	node_type tmp = m_root;
	node_type previous = m_root;
	while (tmp)
	{
		if (m_key_compare(s_key(node), s_key(tmp)))
		{
#ifdef DEBUG
			std::cout << "move left" << std::endl;
#endif
			previous = tmp;
			tmp = tmp->left;
		}
		else
		{
			previous = tmp;
			tmp = tmp->right;
		}
	}
	if (m_key_compare(s_key(node), s_key(previous)))
	{
		previous->left = node;
		node->parent = previous;
	}
	else if (m_key_compare(s_key(previous), s_key(node)))
	{
		previous->right = node;
		node->parent = previous;
	}
	else
	{
		std::cout << "not unique" << std::endl;
	}

	++m_node_count;

#ifdef DEBUG
	std::cout << *this << std::endl;
#endif

	// fix color of the nodes
	while (node != m_root && node->parent->color == RED)
	{
		if (node->parent->parent && node->parent == node->parent->parent->left)
		{
			// node->parent is left child
			node_type uncle = node->parent->parent->right;
			if (uncle && uncle->color == RED)
			{
				// case 1
				std::cout << "case 1 (left)" << std::endl;
				node_type grandparent = node->parent->parent;
				// while (grandparent && grandparent->color == RED)
				// {
				// 	m_recolor(grandparent);
				// 	if (!grandparent->parent)
				// 		break;
				// 	grandparent = grandparent->parent->parent;
				// }
				m_recolor(grandparent);
				node = grandparent;
			}
			else
			{
				if (node == node->parent->right)
				{
					// case 2
					std::cout << "case 2 (left)" << std::endl;
					node = node->parent;
					m_left_rotate(node);
				}
				// case 3
				std::cout << "case 3 (left)" << std::endl;
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
				std::cout << "case 1 (right)" << std::endl;
				node_type grandparent = node->parent->parent;
				m_recolor(grandparent);
				node = grandparent;
			}
			else
			{
				if (node == node->parent->left)
				{
					// case 2
					std::cout << "case 2 (right)" << std::endl;
					node = node->parent;
					m_right_rotate(node);
				}
				// case 3
				std::cout << "case 3 (right)" << std::endl;
				m_left_rotate(node->parent->parent);
				m_recolor(node->parent);
			}
		}
	}
	m_root->color = BLACK;

#ifdef DEBUG
	std::cout << *this << std::endl;
#endif

	// TODO: return right bool
	return ft::make_pair(iterator(node), true);
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
		m_root = y;
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
		m_root = y;
	else if (node == node->parent->right)
		node->parent->right = y;
	else
		node->parent->left = y;
	y->right = node;
	node->parent = y;
}

// https://www.baeldung.com/java-print-binary-tree-diagram

template <typename Value>
std::ostream& traverseNodes(
	std::ostream&		 os,
	RB_tree_node<Value>* node,
	const std::string&	 padding,
	const std::string&	 pointer,
	bool				 hasRightSibling)
{
	if (!node)
		return os;

	os << std::endl << padding << pointer;
	os << Color::Modifier(
		(node->color == RED) ? Color::FG_RED : Color::FG_BLACK);
	os << node->value << Color::Modifier();

	std::string paddingForBoth = padding;
	if (hasRightSibling)
		paddingForBoth += "│  ";
	else
		paddingForBoth += "   ";

	std::string pointerRight = "└──";
	std::string pointerLeft = (node->right) ? "├──" : "└──";

	traverseNodes(os, node->left, paddingForBoth, pointerLeft, node->right);
	traverseNodes(os, node->right, paddingForBoth, pointerRight, false);

	return os;
}

template <typename Value>
std::ostream& operator<<(std::ostream& os, RB_tree_node<Value>* node)
{
	if (!node)
		return os;

	os << Color::Modifier(
		(node->color == RED) ? Color::FG_RED : Color::FG_BLACK);
	os << node->value << Color::Modifier();

	std::string pointerRight = "└──";
	std::string pointerLeft = (node->right) ? "├──" : "└──";

	traverseNodes(os, node->left, "", pointerLeft, node->right);
	traverseNodes(os, node->right, "", pointerRight, false);

	return os;
}

template <
	class Key,
	class Value,
	class KeyOfValue,
	class Compare,
	class Allocator>
std::ostream& operator<<(
	std::ostream&											   os,
	const RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& tree)
{
	os << "Red-Black tree(node_count=" << tree.m_node_count << ")" << std::endl;
	os << tree.m_root;
	return os;
}

#endif // TREE_HPP
