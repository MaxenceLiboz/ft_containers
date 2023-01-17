#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"
#include <iostream>
#include <iterator>

namespace ft{
	template <class T>
	class random_access_iterator : public iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
		
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
