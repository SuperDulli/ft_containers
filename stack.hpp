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
	typedef Container			  container_type;
	typedef Container::value_type value_type;
	typedef Container::size_type  size_type;

	// c++11
	//  typedef Container::reference	   reference;
	//  typedef Container::const_reference const_reference;

	// constructor

	explicit stack(const container_type& cont = container_type());
	stack(const container_type& other);

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
	container_type m_cont;

private:
	template <class T1, class C1>
	friend bool operator==(const stack<T1, C1>&, const stack<T1, C1>&);
	template <class T1, class C1>
	friend bool operator<(const stack<T1, C1>&, const stack<T1, C1>&);
};

// constructor

template <class T, class Container>
stack<T, Container>::stack(const container_type& cont) : m_cont(cont)
{
#ifdef DEBUG
	std::cout << "stack default constructor" << std::endl;
#endif
}

template <class T, class Container>
stack<T, Container>::stack(const container_type& other) : m_cont(other)
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
	m_cont = other.m_cont;
	return *this:
}

// element access

template <class T, class Container>
stack<T, Container>::value_type& stack<T, Container>::top()
{
	return m_cont.back();
}

template <class T, class Container>
const stack<T, Container>::value_type& stack<T, Container>::top() const
{
	return m_cont.back();
}

// capacity

template <class T, class Container>
bool stack<T, Container>::empty() const
{
	return m_cont.empty();
}

template <class T, class Container>
stack<T, Container>::size_type stack<T, Container>::size() const
{
	return m_cont.size();
}

// modifiers

template <class T, class Container>
void stack<T, Container>::push(const value_type& value)
{
	m_cont.push_back(value);
}

template <class T, class Container>
void stack<T, Container>::pop()
{
	m_cont.pop_back(value);
}

// relational operators - non member functions

template <class T, class Container>
bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
	return lhs.m_cont == rhs.m_cont;
}

template <class T, class Container>
bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
	return lhs.m_cont < rhs.m_cont;
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
