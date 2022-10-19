#ifndef TREE_HPP
#define TREE_HPP

#include <memory> // allocator

namespace ft
{

enum RB_tree_color {
	RED = false,
	BLACK = true
};

// node

// tree

template <
	class Key,
	class Value,
	class Compare,
	class Allocator = std::allocator<Value> >
class RB_tree
{};


} // namespace ft


#endif // TREE_HPP
