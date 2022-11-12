#ifndef FT_CONTAINERS_EQUAL_HPP
#define FT_CONTAINERS_EQUAL_HPP


namespace ft {
	/*
	 * Compares the elements in the range [first1,last1) with those in the range beginning at first2,
	 * and returns true if all of the elements in both ranges match.
	 * Docs: https://cplusplus.com/reference/algorithm/equal/
	 */
	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1) {
			if (!pred(*first1,*first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}
}
#endif //FT_CONTAINERS_EQUAL_HPP
