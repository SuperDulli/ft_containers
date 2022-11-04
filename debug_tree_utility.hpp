#ifndef DEBUG_TREE_UTILITY_HPP
#define DEBUG_TREE_UTILITY_HPP

#include "debug_utility.hpp"
#include "tree.hpp"
#include "Color.hpp"
#include <iostream>
#include <string>

// https://www.baeldung.com/java-print-binary-tree-diagram

template <typename Value>
std::ostream& traverseNodes(
	std::ostream&			 os,
	ft::RB_tree_node<Value>* node,
	const std::string&		 padding,
	const std::string&		 pointer,
	bool					 hasRightSibling)
{
	if (!node)
		return os;

	os << std::endl << padding << pointer;
	os << Color::Modifier(
		(node->color == ft::RED) ? Color::FG_RED : Color::FG_BLACK);
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
std::ostream& operator<<(std::ostream& os, const ft::RB_tree_node<Value>* node)
{
	if (!node)
		return os;

	os << Color::Modifier(
		(node->color == ft::RED) ? Color::FG_RED : Color::FG_BLACK);
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
	std::ostream&												   os,
	const ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>& tree)
{
	os << std::boolalpha;
	os << "Red-Black tree(size=" << tree.size()
	   << ", max_size=" << tree.max_size() << ", valid=" << tree.verify() << ")"
	   << std::endl;
	if (tree.size() == 0)
		return os;
	os << tree.get_root() << std::endl;
	for (typename ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::
			 const_iterator it = tree.begin();
		 it != tree.end();
		 ++it)
	{
		os << *it << ", ";
	}
	return os;
}

#endif // DEBUG_TREE_UTILITY_HPP
