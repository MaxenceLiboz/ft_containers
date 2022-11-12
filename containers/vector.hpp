#ifndef VECTOR_HPP

#define VECTOR_HPP

#include <iterator>
#include <memory>
#include <iostream>
#include "../iterators/random_access_iterator.hpp"
#include "../iterators/reverse_iterator_vector.hpp"
#include "../includes/enable_if.hpp"
#include "../includes/equal.hpp"
#include "../includes/is_integral.hpp"
#include "../includes/lexicographical_compare.hpp"
#include <vector>

namespace ft{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			// Member types
			typedef 			T 												value_type;
			typedef 			Allocator 										allocator_type;
			typedef typename 	allocator_type::size_type 						size_type;
			typedef typename 	allocator_type::reference 						reference;
			typedef typename	allocator_type::const_reference					const_reference;
			typedef typename 	allocator_type::pointer 						pointer;
			typedef typename 	allocator_type::const_pointer 					const_pointer;
			typedef typename 	ft::random_access_iterator<value_type> 			iterator;
			typedef typename 	ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename 	ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename	ft::reverse_iterator<const_iterator> 			const_reverse_iterator;
			typedef typename 	ft::iterator_traits<iterator>::difference_type	difference_type; 
				
			//Need to implement iterator
			/*
			*/

		private:
			//Member variables
			pointer 		_start;
			pointer 		_end;
			pointer 		_capacity;
			allocator_type 	_allocator;

		public:

		/* ************************************************************************** */
		/* ----------------------- Constructors && Destructors ---------------------- */
		/* ************************************************************************** */
			//Default constructor
			explicit vector(const allocator_type& alloc = allocator_type())
			: _start(0), _end(0), _capacity(0), _allocator(alloc) {}

			//Fill constructor
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _start(0), _end(0), _capacity(0), _allocator(alloc)
			{
				assign(n, val);
			}

//			Range constructor
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			: _start(0), _end(0), _capacity(0), _allocator(alloc)
			{
				assign(first, last);
			}

			//Copy constructor
			 vector(const vector& x) : _start(0), _end(0), _capacity(0), _allocator(x._allocator) {*this = x;}

			//Destructor
			~vector()
			{
				if (capacity() > 0)
				{
					clear();
					_allocator.deallocate(_start, capacity());
				}
				_start = 0;
				_end = _start;
				_capacity = _start;
			}
		/* ************************************************************************** */
		/* ------------------------------- Operator '=' ----------------------------- */
		/* ************************************************************************** */
			vector& operator= (const vector& x)
			{
				if (x.capacity() > 0)
				{
					reserve(x.capacity());
					assign(x.begin(), x.end());
				}
				return *this;
			}

		/* ************************************************************************** */
		/* -------------------------------- Iterators ------------------------------- */
		/* ************************************************************************** */
			iterator begin() {return iterator(_start);}
			const_iterator begin() const {return const_iterator(_start);}
			iterator end() {return iterator(_end);}
			const_iterator end() const {return const_iterator(_end);}
			reverse_iterator rbegin() {return reverse_iterator(_end);}
			const_reverse_iterator rbegin() const {return const_reverse_iterator(_end);}
			reverse_iterator rend() {return reverse_iterator(_start);}
			const_reverse_iterator rend() const {return const_reverse_iterator(_start);}
		/* ************************************************************************** */
		/* -------------------------------- Capacity -------------------------------- */
		/* ************************************************************************** */
			size_type size() const {return _end - _start;}
			size_type max_size() const {
				return std::min(_allocator.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max()));
			}
			void resize(size_type n, value_type val = value_type()){
				
				size_type	size_tmp = size();

				if (n == size_tmp)
					return;
				else if (n < size_tmp)
				{
					while (size_tmp > n)
					{
						_end--;
						_allocator.destroy(_end);
						size_tmp--;
					}
				}
				else
				{
					if (n <= capacity())
					{
						for (size_type i = size_tmp; i < n; i++)
                        {
                            _allocator.construct(_end, val);
                            _end++;
                        }
					}
					else
					{
						reserve(capacity() * 2 >= n ? capacity() * 2 : n);
						for (size_type i = size_tmp; i < n; i++)
						{
							_allocator.construct(_end, val);
							_end++;
						}
					}
				}
			}
			size_type capacity() const {return _capacity - _start;}
			bool empty() const {return (size() == 0 ? true : false);}
			void reserve(size_type n){

				if (n >= max_size())
					throw(std::length_error("vector"));
				else if (n <= capacity())
					return;

				pointer		tmp_start;
				pointer		tmp_end;

				tmp_start	= _allocator.allocate(n);
				tmp_end		= tmp_start;
				for (size_type i = 0; i < size(); i++)
				{
					_allocator.construct(tmp_end, _start[i]);
					_allocator.destroy(_start + i);
					tmp_end++;
				}
				if (capacity() > 0)
					_allocator.deallocate(_start, capacity());
				_start = tmp_start;
				_end = tmp_end;
				_capacity = _start + n;

			}
		/* ************************************************************************** */
		/* -------------------------------- Modifiers ------------------------------- */
		/* ************************************************************************** */
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				typename ft::iterator_traits<InputIterator>::iterator_category	category;
				this->_assign_range(first, last, category);
			}
			void assign(size_type n, const value_type& val)
			{
				if (n > 0)
				{
					if (n > capacity())
						reserve(n);
					clear();
					for (size_type i = 0; i < n; i++)
					{
						_allocator.construct(_end, val);
						_end++;
					}
				}
			}
			void clear(){
				pointer	tmp = _start;
				for (; tmp != _end; tmp++)
					_allocator.destroy(tmp);
				_end = _start;
			}

			iterator insert(iterator position, const value_type& val)
			{
				size_type	pos_len = position - begin();

				insert(position, 1, val);
				return _start + pos_len;
			}

			void insert(iterator position, size_type n, const value_type& val){
				size_type	loc = position - begin();
				vector		tmp(*this);

				if (size() + n > capacity())
					reserve(capacity() * 2 >= size() + n ? capacity() * 2 : size() + n);
				_end += n;
				for (size_type i = 0; i < n; i++)
				{
					if (loc + i >= tmp.size())
						_allocator.construct(_start + loc + i, val);
					else
						*(_start + loc + i) = val;
				}
				for (size_type it = loc; it < tmp.size(); it++)
				{
					if (it + n >= tmp.size())
						_allocator.construct(_start + it + n, tmp[it]);
					else
						*(_start + it + n) = tmp[it];
				}
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				size_type	loc = position - begin();
				vector		tmp(*this);

				_end = _start + loc;
				for (; first != last; first++)
				{
					if (size() < tmp.size())
					{
						*_end = *first;
						_end++;
					}
					else
						push_back(*first);
				}
				for (size_type it = loc; it < tmp.size(); it++)
				{
					if (size() < tmp.size())
					{
						*_end = tmp[it];
						_end++;
					}
					else
						push_back(tmp[it]);
				}
				
			}

			iterator erase(iterator position){
				iterator		it = position;

				for (;it != this->end() - 1; it++)
				{
					_allocator.destroy(it.base());
					_allocator.construct(it.base(), *(it + 1));
				}
				_allocator.destroy(it.base());
				_end--;
				return position;
			}

			iterator erase(iterator first, iterator last){
				iterator		it = first;
				size_type		range_size = last - first;

				for (;it != end(); it++)
				{
					if (it + range_size < end())
						*it = *(it + range_size);
					else
						_allocator.destroy(it.base());
				}
				_end = it.base() - range_size;
				return first;
			}
			
			void push_back(const value_type& val) {
				if (_end == _capacity)
					reserve(capacity() * 2 == 0 ? 1 : capacity() * 2);
				_allocator.construct(_end, val);
				_end++;
			}
			void pop_back() {
				if (size() != 0)
				{
					_allocator.destroy(_end - 1);
					_end--;
				}
			}
			void swap(vector& x){
				std::swap(_start, x._start);
				std::swap(_end, x._end);
				std::swap(_capacity, x._capacity);
			}
		/* ************************************************************************** */
		/* ----------------------------- Elements Access ---------------------------- */
		/* ************************************************************************** */
			reference operator[] (size_type n) {return *(_start + n);}
			const_reference operator[] (size_type n) const {return *(_start + n);}
			reference at(size_type n) {
				if (n >= size())
					throw(std::out_of_range("vector"));
				return _start[n];
			}
			const_reference at(size_type n) const {
				if (n >= size())
					throw(std::out_of_range("vector"));
				return _start[n];
			}
			reference front() { return *_start;}
			const_reference front() const { return *_start;}
			reference back() { return *(_end - 1);}
			const_reference back() const { return *(_end - 1);}
			T* data() {return _start;}
			const T* data() const {return _start;}
		/* ************************************************************************** */
		/* -------------------------- Allocator ------------------------------------- */
		/* ************************************************************************** */
			allocator_type get_allocator() const{return _allocator;}
		/* ************************************************************************** */
		/* -------------------------- Relationnal Operators ------------------------- */
		/* ************************************************************************** */
			friend bool operator== (const ft::vector<T, allocator_type>& lhs, const ft::vector<T, allocator_type>& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				return ft::equal(lhs._start, lhs._end, rhs._start);

			}
			friend bool operator!=(const ft::vector<T, allocator_type>& lhs, const ft::vector<T, allocator_type>& rhs){return !(lhs == rhs);}
			friend bool operator<(const ft::vector<T, allocator_type>& lhs, const ft::vector<T, allocator_type>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}
			friend bool operator>=(const ft::vector<T, allocator_type>& lhs, const ft::vector<T, allocator_type>& rhs){return !(lhs < rhs);}
			friend bool operator>(const ft::vector<T, allocator_type>& lhs, const ft::vector<T, allocator_type>& rhs)
			{
				if (!(lhs < rhs) && lhs != rhs)
					return true;
				else
					return false;

			}
			friend bool operator<=(const ft::vector<T, allocator_type>& lhs, const ft::vector<T, allocator_type>& rhs)
			{
				if (lhs < rhs || lhs == rhs)
					return true;
				else
					return false;
			}
		private:

			template <class InputIterator>
			void _assign_range(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				clear();
				for (; first != last; ++first)
					push_back(*first);
			}

			template <class InputIterator>
			void _assign_range(InputIterator first, InputIterator last, ft::input_iterator_tag)
			{
				clear();
				for (; first != last; ++first)
					push_back(*first);
			}

			template <class InputIterator>
			void _assign_range(InputIterator first, InputIterator last, std::forward_iterator_tag)
			{
				size_type n = ft::distance(first, last);

				clear();
				reserve(n);
				for (; first != last; ++first)
				{
					_allocator.construct(_end, *first);
					_end++;
				}
			}

			template <class InputIterator>
			void _assign_range(InputIterator first, InputIterator last, ft::forward_iterator_tag)
			{
				size_type n = ft::distance(first, last);

				clear();
				reserve(n);
				for (; first != last; ++first)
				{
					_allocator.construct(_end, *first);
					_end++;
				}
			}


	};
	template< class T, class Allocator >
	void swap( ft::vector<T,Allocator>& lhs, ft::vector<T,Allocator>& rhs ){
		lhs.swap(rhs);
	}
};

#endif
