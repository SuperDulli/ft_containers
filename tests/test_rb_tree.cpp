#include <iomanip>
#include <iostream>
#include <string>

#include <functional> // less
#include <utility>	  // pair

#include "../debug_utility.hpp"
#include "../debug_tree_utility.hpp"
#include "../utility.hpp" // selectFirst

#include "../tree.hpp"

namespace test_tree
{

using ::operator<<; // use operators from the gloabal namespace

typedef ft::RB_tree<
	int,
	ft::pair<const int, float>,
	ft::SelectFirst< ft::pair<const int, float> >,
	std::less<int> >
	map_tree_type;

typedef ft::RB_tree< int, int, ft::Identity<int>, std::less<int> >
	set_tree_type;

// TODO: move to seperate file(s)
struct Point {
	double x, y;
	Point() : x(), y() {}
	Point(double _x, double _y) : x(_x), y(_y) {}
};

std::ostream& operator<<(std::ostream& os, const Point& point)
{
	os << "Point(x=" << point.x << ", y=" << point.y << ")";
	return os;
}

struct PointCmp {
	bool operator()(const Point& lhs, const Point& rhs) const
	{
		return lhs.x < rhs.x; // NB. intentionally ignores y
	}
};
typedef ft::RB_tree< Point, Point, ft::Identity<Point>, PointCmp >
	point_tree_type;

typedef ft::RB_tree<
	Point,
	ft::pair<const Point, double>,
	ft::SelectFirst< ft::pair<const Point, double> >,
	PointCmp >
	point_map_tree_type;

bool construction()
{
	bool result = true;

	set_tree_type empty;
	set_tree_type empty_copy(empty);

	result = result && empty.size() == 0 && empty_copy.size() == 0 &&
			 empty == empty_copy && empty.empty() && empty_copy.empty();

	empty.insert(5);

	set_tree_type copy(empty);

	result = result && empty.size() == 1 && empty_copy.size() == 0 &&
			 copy.size() == 1 && empty != empty_copy && !copy.empty();

	// TODO: test other constructors
	map_tree_type map_tree;

	map_tree.insert(ft::make_pair(1, 1.f));
	map_tree.insert(ft::make_pair(2, 4.f));
	map_tree.insert(ft::make_pair(3, 9.f));
	std::cout << "map tree:\n" << map_tree << std::endl;
	result = result && !map_tree.empty();

	point_tree_type point_tree;
	point_tree.insert(Point(5, -12));
	point_tree.insert(Point(3, -42));
	point_tree.insert(Point(1, 1));
	point_tree.insert(Point(42, 0));
	std::cout << "point tree:\n" << point_tree << std::endl;
	result = result && !point_tree.empty();

	point_map_tree_type point_map_tree;
	point_map_tree.insert(ft::make_pair(Point(5, -12), 13));
	point_map_tree.insert(ft::make_pair(Point(3, -42), 44));
	point_map_tree.insert(ft::make_pair(Point(1, 1), 1));
	point_map_tree.insert(ft::make_pair(Point(42, 0), 42));
	std::cout << "point map tree:\n" << point_map_tree << std::endl;
	result = result && !point_map_tree.empty();

	return result;
}

bool insert_simple()
{
	std::cout << "insert one by one (total=6)" << std::endl;
	set_tree_type set_tree;

	set_tree.insert(50);
	set_tree.insert(5);
	set_tree.insert(25);
	set_tree.insert(100);
	set_tree.insert(75);
	set_tree.insert(90);

	std::cout << set_tree << std::endl;
	return (set_tree.verify() && set_tree.size() == 6);
}

bool insert_unique()
{
	std::cout << "insert the same key twice" << std::endl;
	set_tree_type unique;
	unique.insert(1);
	unique.insert(1);

	std::cout << unique << std::endl;
	return (unique.verify() && unique.size() == 1);
}

bool insert_unique_complex()
{
	std::cout << "insert the same key twice (on accident)" << std::endl;
	set_tree_type unique_complex;
	unique_complex.insert(83);
	unique_complex.insert(86);
	unique_complex.insert(77);
	unique_complex.insert(15);
	unique_complex.insert(93);
	unique_complex.insert(35);
	unique_complex.insert(86);
	unique_complex.insert(92);
	unique_complex.insert(49);
	unique_complex.insert(21);

	std::cout << unique_complex << std::endl;
	return (unique_complex.verify() && unique_complex.size() == 9);
}

bool insert_range()
{
	std::cout << "insert a range" << std::endl;
	int				ints[] = {88, 64, 5, 89, 78, 17, 95, 8, 61, 0};
	ft::vector<int> numbers(ints, ints + 10);
	set_tree_type	range;

	range.insert(numbers.begin(), numbers.end());

	std::cout << range << std::endl;
	return (range.verify() && range.size() == numbers.size());
}

bool insert_random()
{
	const int count = 50;
	std::cout << "insert " << count << " random numbers" << std::endl;
	set_tree_type random;
	debug::insert_random(random, count);

	std::cout << random << std::endl;
	return random.verify();
}

bool insert_hint()
{
	std::cout << "insert with a hint" << std::endl;
	set_tree_type	hint_tree;
	int				ints[] = {88, 64, 5, 89, 78, 17, 95, 8, 61, 0};
	ft::vector<int> numbers(ints, ints + 10);

	hint_tree.insert(numbers.begin(), numbers.end());
	std::cout << hint_tree << std::endl;

	set_tree_type::iterator hint = hint_tree.find(17);
	hint = hint_tree.insert(hint, 16);
	std::cout << hint_tree << std::endl;

	hint = hint_tree.insert(hint, 15);
	std::cout << hint_tree << std::endl;

	std::cout << "wrong hint:" << std::endl;
	hint_tree.insert(hint, 5);
	std::cout << hint_tree << std::endl;

	std::cout << "wrong hint:" << std::endl;
	hint = hint_tree.find(17);
	hint_tree.insert(hint, 18);
	std::cout << hint_tree << std::endl;

	std::cout << "hint == begin:" << std::endl;
	hint = hint_tree.begin();
	hint_tree.insert(hint, -1);
	std::cout << hint_tree << std::endl;

	std::cout << "hint == end:" << std::endl;
	hint = hint_tree.end();
	hint_tree.insert(hint, 100);
	std::cout << hint_tree << std::endl;

	std::cout << "hint == begin (empty tree):" << std::endl;
	set_tree_type empty;
	hint = empty.begin();
	empty.insert(hint, 42);
	std::cout << empty << std::endl;

	std::cout << "hint == begin (empty tree):" << std::endl;
	set_tree_type empty2;
	hint = empty2.begin();
	empty2.insert(hint, 42);
	std::cout << empty2 << std::endl;

	return hint_tree.verify() && empty.verify() && empty2.verify();
}

bool insert()
{
	bool result = true;

	// map_tree_type empty;

	// empty.insert(ft::make_pair<const int, int>(120, 0));
	// empty.insert(ft::make_pair(7, 0));
	// empty.insert(ft::make_pair(3, 0));
	// empty.insert(ft::make_pair(15, 0));
	// empty.insert(ft::make_pair(16, 0));
	// empty.insert(ft::make_pair(14, 0));
	// empty.insert(ft::make_pair(200, 0));
	// empty.insert(ft::make_pair(150, 0));
	// empty.insert(ft::make_pair(250, 0));

	result = result && debug::run_test("insert simple", insert_simple);
	result = result && debug::run_test("insert unique", insert_unique);
	result = result &&
			 debug::run_test("insert unique_complex", insert_unique_complex);
	result = result && debug::run_test("insert range", insert_range);
	result = result && debug::run_test("insert random", insert_random);
	result = result && debug::run_test("insert hint", insert_hint);

	// // iteration
	// set_tree_type::iterator it;
	// it = set_tree.begin();
	// while (it != set_tree.end())
	// {
	// 	std::cout << *it << std::endl;
	// 	++it;
	// }

	// // reverse iteration
	// it = set_tree.end();
	// while (it != set_tree.begin())
	// {
	// 	--it;
	// 	std::cout << *it << std::endl;
	// }

	// // delete

	// set_tree.erase(set_tree.begin());

	// std::cout << set_tree << std::endl;

	// result = result && set_tree.verify();

	return result;
}

set_tree_type create_random_test_tree(int count)
{
	set_tree_type random;
	debug::insert_random(random, count);

	std::cout << random << std::endl;

	return random;
}

set_tree_type create_random_test_tree()
{
	const int	  count = 20;
	set_tree_type random = create_random_test_tree(count);

	return random;
}

set_tree_type create_test_tree(const ft::vector<int>& numbers)
{
	set_tree_type tree;
	tree.insert(numbers.begin(), numbers.end());

	std::cout << tree << std::endl;

	return tree;
}

bool erase_pos(set_tree_type& tree, set_tree_type::iterator pos)
{
	bool					 result;
	set_tree_type::size_type tree_prev_size = tree.size();
	int						 removed_value = pos.m_node->value;

	std::cout << "erase value@pos=" << removed_value << std::endl;
	tree.erase(pos);
	std::cout << tree << std::endl;
	result = tree.verify() && tree.size() == tree_prev_size - 1 &&
			 tree.count(removed_value) == 0;

	return result;
}

bool erase_pos()
{
	bool result = true;
	// erasing sth on empty tree does not work - iterators not valid (end is not
	// dereferencable)
	const int count = 20;
	// int		  ints[] = {99, 8, 28, 45, 33, 22, 99, 50, 97, 8,
	// 					48, 7, 31, 48, 78, 87, 27, 31, 4,  79};
	int ints[] = {53, 4,  28, 83, 76, 7, 26, 74, 97, 64,
				  22, 42, 83, 1,  64, 9, 64, 29, 58, 0};
	// const int count = 50;
	// int		  ints[] = {77, 21, 32, 81, 43, 23, 0,	95, 33, 35, 97, 44, 78,
	// 					8,	42, 38, 78, 22, 27, 59, 3,	15, 24, 64, 43, 10,
	// 					55, 33, 57, 72, 78, 34, 93, 10, 68, 88, 85, 68, 35,
	// 					70, 56, 33, 67, 86, 93, 9,	24, 71, 84, 3};
	ft::vector<int> numbers(ints, ints + count);
	set_tree_type	tree = create_random_test_tree();
	// set_tree_type tree = create_test_tree(numbers);

	std::cout << "erase root=" << tree.m_root()->value << std::endl;
	result = result && erase_pos(tree, set_tree_type::iterator(tree.m_root()));

	std::cout << "erase begin" << std::endl;
	result = result && erase_pos(tree, tree.begin());

	std::cout << "erase last" << std::endl;
	result =
		result && erase_pos(tree, --tree.end()); // end is not valid to erase

	std::cout << "erase last2" << std::endl;
	result =
		result && erase_pos(tree, --tree.end()); // end is not valid to erase

	std::cout << "erase last3" << std::endl;
	result =
		result && erase_pos(tree, --tree.end()); // end is not valid to erase

	for (int i = 0; i < 10; i++)
	{
		set_tree_type::iterator	 pos = tree.begin();
		set_tree_type::size_type offset = rand() % tree.size();
		for (set_tree_type::size_type j = 0; j < offset; j++)
			++pos;

		std::cout << "erase sth" << std::endl;
		result = result && erase_pos(tree, pos);
	}

	// TODO: test more cases

	return result;
}

bool erase_range(
	set_tree_type&			tree,
	set_tree_type::iterator first,
	set_tree_type::iterator last)
{
	bool result = true;

	set_tree_type::size_type tree_prev_size = tree.size();
	int						 removed_count = ft::distance(first, last);
	ft::vector<int>			 removed_values(first, last);

	std::cout << "erase " << removed_count << " values ("
			  << *removed_values.begin() << " -> " << *(--removed_values.end())
			  << ")" << std::endl;
	tree.erase(first, last);
	std::cout << tree << std::endl;
	result = tree.verify() && tree.size() == tree_prev_size - removed_count;

	// check that all values got removed
	for (ft::vector<int>::iterator it = removed_values.begin();
		 it != removed_values.end();
		 ++it)
	{
		result = result && tree.count(*it) == 0;
	}

	return result;
}

bool erase_range()
{
	bool	  result = true;
	const int count = 50;
	int		  ints[] = {77, 21, 32, 81, 43, 23, 0,	95, 33, 35, 97, 44, 78,
						8,	42, 38, 78, 22, 27, 59, 3,	15, 24, 64, 43, 10,
						55, 33, 57, 72, 78, 34, 93, 10, 68, 88, 85, 68, 35,
						70, 56, 33, 67, 86, 93, 9,	24, 71, 84, 3};
	ft::vector<int> numbers(ints, ints + count);
	set_tree_type	tree = create_random_test_tree();
	// set_tree_type tree = create_test_tree(numbers);
	set_tree_type::iterator first;
	set_tree_type::iterator last;

	std::cout << "erase [begin, begin+3) " << std::endl;
	first = tree.begin();
	last = tree.begin();
	for (size_t i = 0; i < 3; i++)
		++last;
	result = result && erase_range(tree, first, last);

	std::cout << "erase [begin+3, begin+7) " << std::endl;
	first = tree.begin();
	last = tree.begin();
	for (size_t i = 0; i < 3; i++)
	{
		++first;
		++last;
		++last;
	}
	++last;
	result = result && erase_range(tree, first, last);

	std::cout << "erase [end-4, end) " << std::endl;
	first = tree.end();
	last = tree.end();
	for (size_t i = 0; i < 4; i++)
	{
		--first;
	}
	result = result && erase_range(tree, first, last);

	std::cout << "erase [begin, end) " << std::endl;
	first = tree.begin();
	last = tree.end();
	result = result && erase_range(tree, first, last);

	return result;
}

bool erase_key(set_tree_type& tree, int key, set_tree_type::size_type expected)
{
	bool					 result;
	set_tree_type::size_type tree_prev_size = tree.size();
	set_tree_type::size_type element_removed;

	std::cout << "erase key=" << key << std::endl;
	element_removed = tree.erase(key);
	std::cout << tree << std::endl;
	result = element_removed == expected;
	result = result && tree.verify() &&
			 tree.size() == tree_prev_size - element_removed &&
			 tree.count(key) == 0;

	return result;
}

bool erase_key()
{
	bool	  result = true;
	const int count = 50;
	int		  ints[] = {77, 21, 32, 81, 43, 23, 0,	95, 33, 35, 97, 44, 78,
						8,	42, 38, 78, 22, 27, 59, 3,	15, 24, 64, 43, 10,
						55, 33, 57, 72, 78, 34, 93, 10, 68, 88, 85, 68, 35,
						70, 56, 33, 67, 86, 93, 9,	24, 71, 84, 3};
	ft::vector<int> numbers(ints, ints + count);
	set_tree_type	tree = create_random_test_tree();
	// set_tree_type tree = create_test_tree(numbers);

	int key;

	key = -1;
	std::cout << "erasing a key that does not exist:" << std::endl;
	result = result && erase_key(tree, key, 0);

	key = *tree.begin();
	std::cout << "erasing a key that exist:" << std::endl;
	result = result && erase_key(tree, key, 1);

	return result;
}

bool erase()
{
	bool result = true;

	result = result && debug::run_test("erase pos", erase_pos);
	result = result && debug::run_test("erase range", erase_range);
	result = result && debug::run_test("erase key", erase_key);

	return result;
}

bool clear()
{
	bool		  result;
	set_tree_type tree = create_random_test_tree();

	tree.clear();
	std::cout << tree << std::endl;
	result = tree.size() == 0 && tree.verify() && tree.begin() == tree.end();

	return result;
}

bool swap(const set_tree_type& left_tree, const set_tree_type& right_tree)
{
	bool result;

	set_tree_type left(left_tree);
	set_tree_type right(right_tree);

	// set_tree_type::const_iterator it_left = left.begin();
	// set_tree_type::const_iterator end_left = left.end();
	// set_tree_type::const_iterator it_right = right.begin();
	// set_tree_type::const_iterator end_right = right.end();

	left.swap(right);
	// TODO: figure out how to use this correctly
	// std::cout << "iterate using the begin-iterator from before swap (left):"
	// << std::left; printIterValues(it_left, right_tree.end());
	std::cout << "left tree after swap:\n" << left << std::endl;
	result = left == right_tree && right == left_tree;

	return result;
}

bool swap()
{
	bool result = true;
	std::cout << "left tree " << std::endl;
	;
	set_tree_type tree_left = create_random_test_tree(5);
	std::cout << "right tree " << std::endl;
	;
	set_tree_type tree_right = create_random_test_tree(10);
	set_tree_type empty;

	std::cout << "swap left and right tree" << std::endl;
	result = result && test_tree::swap(tree_left, tree_right);

	// TODO: test with empty tree
	std::cout << "swap empty and right tree" << std::endl;
	result = result && test_tree::swap(empty, tree_right);

	std::cout << "swap left and empty tree" << std::endl;
	result = result && test_tree::swap(tree_left, empty);

	return result;
}

bool lower_bound(set_tree_type& tree, int bound)
{
	const set_tree_type c_tree(tree);

	set_tree_type::iterator		  it_low;
	set_tree_type::const_iterator c_it_low;

	std::cout << "find first key that is not before " << bound << ":"
			  << std::endl;
	it_low = tree.lower_bound(bound);
	c_it_low = c_tree.lower_bound(bound);

	if (it_low == tree.end() && c_it_low == c_tree.end())
	{
		std::cout << "all keys are before " << bound << std::endl;
		return true;
	}
	std::cout << "it_low: " << *it_low << std::endl;
	std::cout << "c_it_low: " << *c_it_low << std::endl;
	return (*it_low >= bound && *c_it_low >= bound);
}

bool lower_bound()
{
	bool result = true;

	set_tree_type empty;
	set_tree_type tree = create_random_test_tree(10);
	int			  bound;

	bound = 0;
	result = result && lower_bound(tree, bound);

	bound = 50;
	result = result && lower_bound(tree, bound);

	bound = 500;
	result = result && lower_bound(tree, bound);

	std::cout << "test with empty tree:" << std::endl;
	bound = 500;
	result = result && lower_bound(empty, bound);

	return result;
}

bool upper_bound(set_tree_type& tree, int bound)
{
	const set_tree_type c_tree(tree);

	set_tree_type::iterator		  it_high;
	set_tree_type::const_iterator c_it_high;

	std::cout << "find first key that is after " << bound << ":" << std::endl;
	it_high = tree.upper_bound(bound);
	c_it_high = c_tree.upper_bound(bound);

	if (it_high == tree.end() && c_it_high == c_tree.end())
	{
		std::cout << "no keys after " << bound << std::endl;
		return true;
	}
	std::cout << "it_low: " << *it_high << std::endl;
	std::cout << "c_it_low: " << *c_it_high << std::endl;
	return (bound < *it_high && bound < *c_it_high);
}

bool upper_bound()
{
	bool result = true;

	set_tree_type empty;
	set_tree_type tree = create_random_test_tree(10);
	int			  bound;

	bound = 0;
	result = result && upper_bound(tree, bound);

	bound = 50;
	result = result && upper_bound(tree, bound);

	bound = 500;
	result = result && upper_bound(tree, bound);

	std::cout << "test with empty tree:" << std::endl;
	bound = 50;
	result = result && upper_bound(empty, bound);

	return result;
}

void printIterName(const set_tree_type& tree, set_tree_type::const_iterator it)
{
	if (it == tree.end())
		std::cout << "end()";
	else if (it == tree.begin())
		std::cout << "begin()";
	else
		std::cout << *it;
}

bool equal_range(set_tree_type& tree, int key)
{
	bool				result = true;
	const set_tree_type c_tree(tree);

	ft::pair<set_tree_type::iterator, set_tree_type::iterator> pair;
	ft::pair<set_tree_type::const_iterator, set_tree_type::const_iterator>
		c_pair;

	std::cout << "find range containg all elements equal to " << key
			  << ". (first not less, last greater than):" << std::endl;
	pair = tree.equal_range(key);
	c_pair = c_tree.equal_range(key);

	std::cout << "[";
	printIterName(tree, pair.first);
	std::cout << ", ";
	printIterName(tree, pair.second);
	std::cout << ")" << std::endl;
	std::cout << "[";
	printIterName(c_tree, c_pair.first);
	std::cout << ", ";
	printIterName(c_tree, c_pair.second);
	std::cout << ")" << std::endl;

	if (pair.first != tree.end())
		result = result && *pair.first >= key;

	if (pair.second != tree.end())
		result = result && *pair.second > key;

	if (c_pair.first != c_tree.end())
		result = result && *c_pair.first >= key;

	if (c_pair.second != c_tree.end())
		result = result && *c_pair.second > key;

	// the range should either include zero or one element
	set_tree_type::iterator::difference_type distance =
		ft::distance(pair.first, pair.second);
	set_tree_type::const_iterator::difference_type c_distance =
		ft::distance(c_pair.first, c_pair.second);

	result = result && (distance == 0 || distance == 1);
	result = result && (c_distance == 0 || c_distance == 1);

	return result;
}

bool equal_range()
{
	bool		  result = true;
	set_tree_type empty;
	set_tree_type tree = create_random_test_tree(10);
	int			  key;

	key = 0;
	result = result && equal_range(tree, key);

	key = 50;
	result = result && equal_range(tree, key);

	key = 500;
	result = result && equal_range(tree, key);

	std::cout << "test with empty tree:" << std::endl;
	key = 50;
	result = result && equal_range(empty, key);

	return result;
}

bool all()
{
	bool result = true;

	std::cout << "-- Test Red-Black tree --" << std::endl;
	result =
		result && debug::run_test("tree construction", test_tree::construction);
	result = result && debug::run_test("tree insert", test_tree::insert);
	result = result && debug::run_test("tree erase", test_tree::erase);
	result = result && debug::run_test("tree clear", test_tree::clear);
	result = result && debug::run_test("tree swap", test_tree::swap);
	result =
		result && debug::run_test("tree lower_bound", test_tree::lower_bound);
	result =
		result && debug::run_test("tree upper_bound", test_tree::upper_bound);
	result =
		result && debug::run_test("tree equal_range", test_tree::equal_range);

	// debug::run_test("relational operators", test_relational_operators);
	return result;
}
} // namespace test_tree

int main()
{
	bool result = true;

	srand(time(NULL));

	result = result && debug::run_test("tree", test_tree::all);

	if (result)
		std::cout << Color::Modifier(Color::FG_GREEN) << "All Test passed."
				  << Color::Modifier() << std::endl;
	else
		std::cout << Color::Modifier(Color::FG_RED)
				  << "At least one Test failed." << Color::Modifier()
				  << std::endl;
	return (result ? 0 : 1);
}

bool debug::run_test(const std::string& name, bool (*test_f)(void))
{
	std::cout << "running Test: " << name << std::endl;
	bool result = (test_f) ();
	test_result(name, result);

	return result;
}

void debug::test_result(const std::string& name, bool result)
{
	std::cout << "Test(" << name << "): ";
	if (result)
	{
		std::cout << Color::Modifier(Color::FG_GREEN) << "passed."
				  << Color::Modifier();
	}
	else
	{
		std::cout << Color::Modifier(Color::FG_RED) << "failed."
				  << Color::Modifier();
	}
	std::cout << std::endl;
}
