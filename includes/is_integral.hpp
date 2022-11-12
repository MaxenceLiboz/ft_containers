#ifndef FT_CONTAINERS_IS_INTEGRAL_HPP
#define FT_CONTAINERS_IS_INTEGRAL_HPP
/*
 * Checks whether T is an integral type.
 * Provides the member constant value which is equal to true, if T is the type:
 * bool, char, char16_t, char32_t, wchar_t, short, int, long, long long,
 * or any implementation-defined extended integer types, including any signed, unsigned.
 * Otherwise, value is equal to false.
 */

namespace ft {

	// Interface that will be use to define the integral type specification
	template <bool get_value, typename T>
	struct Iis_integral {
		typedef T type;
		static const bool value = get_value;
	};

	// Globals type = false
	template <typename>
	struct is_integral_type : public Iis_integral<false, int>{};

	// Types provided by Docs: https://en.cppreference.com/w/cpp/types/is_integral
	template <>
	struct is_integral_type<bool> : public Iis_integral<true, bool>{};
	template <>
	struct is_integral_type<char> : public Iis_integral<true, char>{};
	template <>
	struct is_integral_type<char16_t> : public Iis_integral<true, char16_t>{};
	template <>
	struct is_integral_type<char32_t> : public Iis_integral<true, char32_t>{};
	template <>
	struct is_integral_type<wchar_t> : public Iis_integral<true, wchar_t>{};
	template <>
	struct is_integral_type<short> : public Iis_integral<true, short>{};
	template <>
	struct is_integral_type<int> : public Iis_integral<true, int>{};
	template <>
	struct is_integral_type<long> : public Iis_integral<true, long>{};
	template <>
	struct is_integral_type<long long> : public Iis_integral<true, long long>{};

	// Extended integer, any signed and unsigned
	template <>
	struct is_integral_type<unsigned short int> : public Iis_integral<true, unsigned short int>{};
	template <>
	struct is_integral_type<unsigned int> : public Iis_integral<true, unsigned int>{};
	template <>
	struct is_integral_type<unsigned long int> : public Iis_integral<true, unsigned long int>{};
	template <>
	struct is_integral_type<unsigned long long int> : public Iis_integral<true, unsigned long long int>{};
	template <>
	struct is_integral_type<unsigned char> : public Iis_integral<true, unsigned char>{};
	template <>
	struct is_integral_type<signed char> : public Iis_integral<true, signed char>{};

	// ft::is_integral stuct
	template<typename T>
	struct is_integral : public is_integral_type<T>{};
}

#endif //FT_CONTAINERS_IS_INTEGRAL_HPP
