#include "vector_prelude.hpp"
#include "../main.hpp"

void	test_assign_val()
{
	NP::vector<int> a;
	NP::vector<int> b;

	b.assign(3124, 235);
	PRINT_ALL(b)

	a.assign(1000, 11);
	PRINT_ALL(a)

	a.assign(100, 20);
	PRINT_ALL(a)

	a.assign(b.capacity(), b[513]);
	PRINT_ALL(a)

	NP::vector<char> char_a;
	NP::vector<char> char_b;

	char_b.assign(3124, 'b');
	PRINT_ALL(char_b)

	char_a.assign(1000, '!');
	PRINT_ALL(char_a)

	char_a.assign(100, '_');
	PRINT_ALL(char_a)

	char_a.assign(char_b.capacity(), char_b[513]);
	PRINT_ALL(char_a)
}

void	test_assign_range()
{

	NP::vector<int> a;
	NP::vector<int> b;

	a.assign(323, 3);
	PRINT_ALL(a)

	b.assign(a.begin(), a.end() - 10);
	PRINT_ALL(b)


	b.assign(a.begin()+ 40, a.begin() + a.size() / 2);
	PRINT_ALL(b)

	NP::vector<char> char_a;

	std::istringstream str("1 2 3 4 5 6 7");
	std::istreambuf_iterator<char> it(str), end;

	PRINT_ALL(char_a)

	char_a.assign(it, end);

	PRINT_ALL(char_a)
}

void	test_assign_mix()
{
	NP::vector<int> a;
	NP::vector<int> b;

	a.assign(123, 12);
	PRINT_ALL(a)

	b.assign(a.begin(), a.end());
	PRINT_ALL(b)

	a.assign(b.begin() + 10, b.end() - 20);
	PRINT_ALL(a)

	b.assign(211111, 0);
	PRINT_ALL(b)
}


