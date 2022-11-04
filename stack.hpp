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

	template <class T1, class C1>
	friend bool operator==(const stack<T1, C1>&, const stack<T1, C1>&);
	template <class T1, class C1>
	friend bool operator<(const stack<T1, C1>&, const stack<T1, C1>&);
};

} // namespace ft

#endif // STACK_HPP
