#ifndef STACK_HPP
#define STACK_HPP

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include "vector.hpp"

namespace ft
{

template <class T, class Container = ft::vector<T> >
class stack
{
public:
	typedef Container					   container_type;
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type  size_type;

	// c++11 on https://cplusplus.com/reference/stack/stack/,
	// but not on https://en.cppreference.com/w/cpp/container/stack
	 typedef typename Container::reference	   reference;
	 typedef typename Container::const_reference const_reference;

	// constructor

	explicit stack(const container_type& cont = container_type());
	stack(const stack& other);

	~stack();

	stack& operator=(const container_type& other);

	// element access

	value_type&		  top();
	const value_type& top() const;

	// capacity

	bool	  empty() const;
	size_type size() const;

	// modifiers

	void push(const value_type& value);
	void pop();

protected:
	container_type c;

private:
	template <class T1, class C1>
	friend bool operator==(const stack<T1, C1>&, const stack<T1, C1>&);
	template <class T1, class C1>
	friend bool operator<(const stack<T1, C1>&, const stack<T1, C1>&);
};

// constructor

template <class T, class Container>
stack<T, Container>::stack(const container_type& cont) : c(cont)
{
#ifdef DEBUG
	std::cout << "stack default constructor" << std::endl;
#endif
}

template <class T, class Container>
stack<T, Container>::stack(const stack<T, Container>& other)
	: c(other.c)
{
#ifdef DEBUG
	std::cout << "stack copy constructor" << std::endl;
#endif
}

template <class T, class Container>
stack<T, Container>::~stack()
{
#ifdef DEBUG
	std::cout << "stack destructor" << std::endl;
#endif
}

template <class T, class Container>
stack<T, Container>& stack<T, Container>::operator=(const container_type& other)
{
#ifdef DEBUG
	std::cout << "stack copy assignment operator" << std::endl;
#endif
	c = other.c;
	return *this;
}

// element access

template <class T, class Container>
typename stack<T, Container>::value_type& stack<T, Container>::top()
{
	return c.back();
}

template <class T, class Container>
const typename stack<T, Container>::value_type& stack<T, Container>::top() const
{
	return c.back();
}

// capacity

template <class T, class Container>
bool stack<T, Container>::empty() const
{
	return c.empty();
}

template <class T, class Container>
typename stack<T, Container>::size_type stack<T, Container>::size() const
{
	return c.size();
}

// modifiers

template <class T, class Container>
void stack<T, Container>::push(const value_type& value)
{
	c.push_back(value);
}

template <class T, class Container>
void stack<T, Container>::pop()
{
	c.pop_back();
}

// relational operators - non member functions

template <class T, class Container>
bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
	return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
	return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
	return !(rhs < lhs);
}

template <class T, class Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
	return rhs < lhs;
}

template <class T, class Container>
bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
	return !(lhs < rhs);
}

} // namespace ft

#endif // STACK_HPP
