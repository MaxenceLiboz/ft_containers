#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft{
	template <class Iter>
	class reverse_iterator
	{
		public:
			typedef			 Iter											iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		
		private:
			pointer			_pointer;
			iterator_type	_it;
		
		public:
			iterator_type base() const {return _it;}
		/* ************************************************************************** */
		/* ----------------------- Constructors && Destructors ---------------------- */
		/* ************************************************************************** */

			reverse_iterator() : _it() {}
			explicit reverse_iterator( iterator_type x ) {this->_it = x;}
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ) : _it(other.base()) {}

		/* ************************************************************************** */
		/* -------------------------------- Operators ------------------------------- */
		/* ************************************************************************** */
			template<class Iter2>
			friend bool operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter2>& rhs){return lhs.base() == rhs.base();}
			template<class Iter2>
			friend bool operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter2>& rhs){return lhs.base() != rhs.base();}

			template<class Iter2>
			friend bool operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter2>& rhs)
			{
				return lhs.base() > rhs.base();
			}
			template<class Iter2>
			friend bool operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter2>& rhs)
			{
				return lhs.base() < rhs.base();
			}

			template<class Iter2>
			friend bool operator<=(const reverse_iterator<Iter>& __x, const reverse_iterator<Iter2>& __y)
			{
				return __x.base() >= __y.base();
			}

			template<class Iter2>
			friend bool operator>=(const reverse_iterator<Iter>& __x, const reverse_iterator<Iter2>& __y)
			{
				return __x.base() <= __y.base();
			}

			reverse_iterator 		operator+(difference_type n) const {return reverse_iterator(_it - n);}
			friend reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rhs){
    			return reverse_iterator<Iter>(rhs.base() - n);
			}
    		reverse_iterator& operator=(const reverse_iterator<Iter>& __u) {
        		_it = __u.base();
        		return *this;
    		}

			template <class Iter2>
			friend typename reverse_iterator<Iter2>::difference_type
			operator-(const reverse_iterator<Iter>& rhs, const reverse_iterator<Iter2>& lhs){
			    return lhs.base() - rhs.base();
			}
			// reverse_iterator		&operator=(const reverse_iterator &rhs) {this->_it = rhs._it; return *this;}
			reference				operator*() const {iterator_type tmp = _it; return *--tmp;}
			reverse_iterator		&operator++(){_it--; return *this;}
			reverse_iterator 		operator++(int){reverse_iterator tmp = *this; _it--; return tmp;}
			reverse_iterator		&operator+= (difference_type n) {this->_it -= n; return *this;}
			// reverse_iterator		operator-(difference_type n) const {reverse_iterator tmp = *this; tmp._it += n; return tmp;}
		    reverse_iterator  		operator-(difference_type n) const {return reverse_iterator(_it + n);}

			reverse_iterator		&operator--(){_it++; return *this;}
			reverse_iterator		operator--(int){reverse_iterator tmp = *this; _it++; return tmp;}
			reverse_iterator		&operator-= (difference_type n) {this->_it += n; return *this;}
			pointer					operator->() const {return &(operator*());}
			reference				operator[](difference_type n) const {return *(*this + n);}
			// friend reverse_iterator	operator+(difference_type n, reverse_iterator &rhs) {return rhs - n;}
			friend reverse_iterator	operator-(difference_type n, reverse_iterator &rhs) {return rhs + n;}
			// template <class Iterator>
			// friend reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
			// {
			// 	return rev_it - n;
			// }
			// template <class Iterator>
			// friend reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
			// {
			// 	return rev_it + n;
			// }
	};
}
#endif
