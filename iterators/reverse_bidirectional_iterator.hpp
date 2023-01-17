#ifndef REVERSE_BIDIRECTIONAL_ITERATOR_HPP
#define REVERSE_BIDIRECTIONAL_ITERATOR_HPP

#include "../iterators/iterator_traits.hpp"

namespace ft{
	template <class Iter>
	class reverse_bidirectional_iterator
	{
		public:
			typedef			 Iter											iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_type::pointer  						pointer;
			typedef typename iterator_type::reference   					reference;
		
		private:
			iterator_type	_it;
		
		public:
			iterator_type base() const {return _it;}
		/* ************************************************************************** */
		/* ----------------------- Constructors && Destructors ---------------------- */
		/* ************************************************************************** */

			reverse_bidirectional_iterator() : _it() {}
			explicit reverse_bidirectional_iterator( iterator_type x ) {this->_it = x;}
			template< class U2>
			reverse_bidirectional_iterator( const reverse_bidirectional_iterator<U2>& other ) : _it(other.base()) {}

		/* ************************************************************************** */
		/* -------------------------------- Operators ------------------------------- */
		/* ************************************************************************** */
			template<class Iter2>
			friend bool operator==(const reverse_bidirectional_iterator<Iter>& lhs, const reverse_bidirectional_iterator<Iter2>& rhs){return lhs.base() == rhs.base();}
			template<class Iter2>
			friend bool operator!=(const reverse_bidirectional_iterator<Iter>& lhs, const reverse_bidirectional_iterator<Iter2>& rhs){return lhs.base() != rhs.base();}

			template <class Iter2>
    		reverse_bidirectional_iterator& operator=(const reverse_bidirectional_iterator<Iter2>& __u) {
        		_it = __u.base();
        		return *this;
    		}

			reference							operator*() const {iterator_type tmp = _it; return *--tmp;}
			reverse_bidirectional_iterator		&operator++(){_it--; return *this;}
			reverse_bidirectional_iterator 		operator++(int){reverse_bidirectional_iterator tmp = *this; _it--; return tmp;}

			reverse_bidirectional_iterator		&operator--(){_it++; return *this;}
			reverse_bidirectional_iterator		operator--(int){reverse_bidirectional_iterator tmp = *this; _it++; return tmp;}
			pointer								operator->() const {return &(operator*());}
	};
}
#endif
