#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
		public:
			//Member types
			typedef T 			value_type;
			typedef Container 	container_type;
			typedef size_t 		size_type;
			typedef T& 			reference;
			typedef const T& 	const_reference;

		protected:
			container_type _container;

		public:
			//Constructors && Destructor
			explicit stack(const Container& ctnr = Container()) : _container(ctnr) {}
			~stack() {}

			//Operator =
			stack	&operator=(const stack& other) { _container = other._container; return *this; }

			//Member functions
			reference top() { return _container.back(); }
			const_reference top() const { return _container.back(); }
			bool empty() const { return _container.empty(); }
			size_type size() const { return _container.size(); }
			void push(const value_type& value) { _container.push_back(value); }
			void pop() { _container.pop_back(); }

			//Operators
			friend bool operator==(const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs){
				return lhs._container == rhs._container;
			}
			friend bool operator!=(const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs){
				return lhs._container != rhs._container;
			}
			friend bool operator<(const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs){
				return lhs._container < rhs._container;
			}
			friend bool operator<=(const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs){
				return lhs._container <= rhs._container;
			}
			friend bool operator>(const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs){
				return lhs._container > rhs._container;
			}
			friend bool operator>=(const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs){
				return lhs._container >= rhs._container
			}
	};
}

#endif
