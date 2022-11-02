#ifndef DEBUG_UTILITY_HPP
#define DEBUG_UTILITY_HPP

#ifdef USE_STL // CREATE A REAL STL EXAMPLE
#include <utility>
#include <vector>
namespace ft = std;
#else
#include "pair.hpp"
#include "tree.hpp"
#include "vector.hpp"
#endif

#include <stdlib.h> // rand
#include <time.h>

#include "Color.hpp"
#include <iostream>
#include <string>

namespace debug
{

bool run_test(const std::string& name, bool (*test_f)(void));
void test_result(const std::string& name, bool result);
template <class C>
void insert_random(C& container, size_t count);

} // namespace debug

template <typename U, typename V>
std::ostream& operator<<(std::ostream& os, const ft::pair<const U, V>& pair)
{
	os << "pair(" << pair.first << ", " << pair.second << ")";
	return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ft::vector<T>& vec)
{
	os << "vector(capacity=" << vec.capacity() << ", size="
	   << vec.size()
	   //    << ", front=" << vec.front()
	   << ", max_size=" << vec.max_size() << ")" << std::endl;

	if (vec.size())
	{
		typename ft::vector<T>::const_iterator it;
		// typename ft::vector<T>::iterator it; // TODO: why not this?
		for (it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << ", ";
		}
	}
	return os;
}

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
	os << tree.m_root() << std::endl;
	for (typename ft::RB_tree<Key, Value, KeyOfValue, Compare, Allocator>::
			 const_iterator it = tree.begin();
		 it != tree.end();
		 ++it)
	{
		os << *it << ", ";
	}
	return os;
}

template <typename InputIterator>
void printIterValues(InputIterator first, InputIterator last)
{
	while (first != last)
	{
		std::cout << *first << ", ";
		++first;
	}
	std::cout << std::endl;
}

template <class C>
void debug::insert_random(C& container, size_t count)
{
	ft::vector<int> ints;
	for (size_t i = 0; i < count; i++)
	{
		int rand_number = rand() % 100;
		container.insert(rand_number);
		ints.push_back(rand_number);
	}

	std::cout << "inserted: " << ints << std::endl;
}

#endif // DEBUG_UTILITY_HPP
