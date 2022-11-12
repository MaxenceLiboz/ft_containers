#ifndef FT_CONTAINERS_ENABLE_IF_HPP
#define FT_CONTAINERS_ENABLE_IF_HPP

/*
 * If B is true, std::enable_if has a public member typedef type, equal to T;
 * otherwise, there is no member typedef.
 */

namespace ft {
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };
}

#endif //FT_CONTAINERS_ENABLE_IF_HPP
