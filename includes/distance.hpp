#ifndef DISTANCE_HPP
#define DISTANCE_HPP

#include "../iterators/iterator_traits.hpp"
#include <iterator>

namespace ft {
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
	distance(It first, It last)
	{
		return do_distance(first, last, typename ft::iterator_traits<It>::iterator_category());
	}
}

#endif