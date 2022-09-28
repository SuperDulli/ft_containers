#include "iterator.hpp"
#include <iostream>
#include <iterator>
#include <vector>
#include <typeinfo>

typedef std::vector<int>::iterator	iter_type;

bool	test_default_constructor()
{
	ft::reverse_iterator<iter_type> my_rev_iter;
	std::reverse_iterator<iter_type> std_rev_iter;

	typedef ft::iterator_traits<iter_type> my_traits;
	// typedef std::iterator_traits<iter_type> traits;

	// if (typeid(my_traits::iterator_category) == typeid(traits::iterator_category))
	if (typeid(my_traits::iterator_category) == typeid(std::random_access_iterator_tag))
		return true;
	else
		return false;
	return true;
}
