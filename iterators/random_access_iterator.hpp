#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"
#include <iostream>
#include <iterator>

namespace ft{
	template <class T>
	class random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
		
		private:
			pointer	_pointer;

		public:
			pointer	base() const {return _pointer;}
		/* ************************************************************************** */
		/* ----------------------- Constructors && Destructors ---------------------- */
		/* ************************************************************************** */

			random_access_iterator(pointer begin) : _pointer(begin) {}
			random_access_iterator() {_pointer = 0;}
			random_access_iterator(const random_access_iterator &it){_pointer = it._pointer;}
			template<class TU>
			random_access_iterator(const random_access_iterator<TU> &it){_pointer = it.base();}

		/* ************************************************************************** */
		/* ------------------------------- Operator '=' ----------------------------- */
		/* ************************************************************************** */
			random_access_iterator	&operator=(const random_access_iterator &rhs)
			{
				if (this != &rhs)
					this->_pointer = rhs._pointer;
				return *this;
			}

		/* ************************************************************************** */
		/* ------------------------------ Input Iterator ---------------------------- */
		/* ************************************************************************** */
			reference	operator*() const {return *base();}
			pointer		operator->() const {return base();}
			random_access_iterator	operator++(int) {random_access_iterator tmp(*this); ++(*this); return tmp;}
			random_access_iterator	&operator++() {++_pointer; return *this;}
			friend bool		operator==(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {return lhs.base() == rhs.base();}
			template<class T2>
			friend bool		operator==(const random_access_iterator<T> &lhs, const random_access_iterator<T2> &rhs) {return lhs.base() == rhs.base();}
			friend bool		operator!=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {return lhs.base() != rhs.base();}
			template<class T2>
			friend bool		operator!=(const random_access_iterator<T> &lhs, const random_access_iterator<T2> &rhs) {return lhs.base() != rhs.base();}
			random_access_iterator &operator+=(difference_type n){
				// difference_type m = n;
				// if (m >= 0) while (m--) ++(this->_pointer);
				// else while (m++) --(this->_pointer);
				// return *base(); 
				_pointer += n;
				return *this;
			}

		/* ************************************************************************** */
		/* -------------------------- Bidirectionnal Iterator ----------------------- */
		/* ************************************************************************** */
			random_access_iterator	&operator--() {--this->_pointer; return *this;}
			random_access_iterator	operator--(int) {random_access_iterator tmp = *this; --this->_pointer; return tmp.base();}

		/* ************************************************************************** */
		/* -------------------------- Random Access Iterator ------------------------ */
		/* ************************************************************************** */
			random_access_iterator	operator+(difference_type n) const {random_access_iterator tmp = *this; tmp += n; return tmp;}
			random_access_iterator	operator-(difference_type n) const {random_access_iterator tmp = *this; tmp -= n; return tmp;}
			random_access_iterator	&operator-=(difference_type n) {*this += -n; return *this;}
			reference				operator[](difference_type n) const {return *(this->_pointer + n);}
			friend bool				operator<(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {return lhs.base() < rhs.base();}
			template<class T2>
			friend bool				operator<(const random_access_iterator<T> &lhs, const random_access_iterator<T2> &rhs) {return lhs.base() < rhs.base();}
			friend bool				operator>(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {return lhs.base() > rhs.base();}
			template<class T2>
			friend bool				operator>(const random_access_iterator<T> &lhs, const random_access_iterator<T2> &rhs) {return lhs.base() > rhs.base();}

			friend bool				operator<=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {return lhs.base() <= rhs.base();}
			template<class T2>
			friend bool				operator<=(const random_access_iterator<T> &lhs, const random_access_iterator<T2> &rhs) {return lhs.base() <= rhs.base();}

			friend bool				operator>=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {return lhs.base() >= rhs.base();}
			template<class T2>
			friend bool				operator>=(const random_access_iterator<T> &lhs, const random_access_iterator<T2> &rhs) {return lhs.base() >= rhs.base();}

			friend random_access_iterator	operator+(difference_type n, random_access_iterator &rhs) {random_access_iterator tmp =rhs; tmp += n; return tmp;}
			friend random_access_iterator	operator-(difference_type n, random_access_iterator &rhs) {random_access_iterator tmp = rhs; tmp -= n; return tmp;}

			

	};
		template<class It>
		typename ft::iterator_traits<It>::difference_type
			do_distance(It first, It last, std::input_iterator_tag)
		{
			typename ft::iterator_traits<It>::difference_type result = 0;
			while (first != last) {
				++first;
				++result;
			}
			return result;
		}

		template<class It>
		typename ft::iterator_traits<It>::difference_type
			do_distance(It first, It last, std::random_access_iterator_tag)
		{
			return last - first;
		}

		template<class It>
		typename ft::iterator_traits<It>::difference_type
			do_distance(It first, It last, ft::input_iterator_tag)
		{
			typename ft::iterator_traits<It>::difference_type result = 0;
			while (first != last) {
				++first;
				++result;
			}
			return result;
		}

		template<class It>
		typename ft::iterator_traits<It>::difference_type
			do_distance(It first, It last, ft::random_access_iterator_tag)
		{
			return last - first;
		}

		template<class It>
		typename ft::iterator_traits<It>::difference_type
		distance(It first, It last)
		{
			return do_distance(first, last, typename ft::iterator_traits<It>::iterator_category());
		}
		
		template<class It>
		void do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
						ft::input_iterator_tag)
		{
			while (n > 0) {
				--n;
				++it;
			}
		}
		
		template<class It>
		void do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
						ft::bidirectional_iterator_tag)
		{
			while (n > 0) {
				--n;
				++it;
			}
			while (n < 0) {
				++n;
				--it;
			}
		}
		
		template<class It>
		void do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
						ft::random_access_iterator_tag)
		{
			it += n;
		}
		
		template<class It, class Distance>
		void advance(It& it, Distance n)
		{
			do_advance(it, typename ft::iterator_traits<It>::difference_type(n),
			typename ft::iterator_traits<It>::iterator_category());
		}
		template <typename T>
		typename ft::random_access_iterator<T>::difference_type
		operator-(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T> rhs)
		{
			return (lhs.base() - rhs.base());
		}
	
		/* For iterator - const_iterator */
		template<typename T_L, typename T_R>
		typename ft::random_access_iterator<T_L>::difference_type
		operator-(const ft::random_access_iterator<T_L> lhs,
					const ft::random_access_iterator<T_R> rhs)
		{
			return (lhs.base() - rhs.base());
		}
}
#endif
