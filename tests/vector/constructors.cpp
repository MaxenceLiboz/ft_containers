#include "./vector_prelude.hpp"

void	test_default_constructor()
{
	NP::vector<char>	a;
	PRINT_ALL(a);

	NP::vector<int>	b;
	PRINT_ALL(b);

	NP::vector<long>	c;
	PRINT_ALL(c);

	NP::vector<long int>	d;
	PRINT_ALL(d);

	NP::vector<std::string>	e;
	PRINT_ALL(e);
}

void	test_fill_constructor()
{
	NP::vector<char>	a(100, 'a');
	PRINT_ALL(a);

	NP::vector<int>	b(134, 431);
	PRINT_ALL(b);

	NP::vector<long>	c(34, 2148473649);
	PRINT_ALL(c);

	NP::vector<long int>	d(12, 21464748490);
	PRINT_ALL(d);

	NP::vector<std::string>	e(23, "Hello world");
	PRINT_ALL(e);
}

void	test_range_constructor()
{
	NP::vector<char>	a(100, 'a');
	PRINT_ALL(a);
	NP::vector<char>	f(a.begin(), a.end());
	PRINT_ALL(f);

	NP::vector<int>	b(134, 431);
	PRINT_ALL(b);
	NP::vector<int>	g(b.begin(), b.end());
	PRINT_ALL(g);

	NP::vector<long>	c(34, 2148473649);
	PRINT_ALL(c);
	NP::vector<long>	h(c.begin(), c.end());
	PRINT_ALL(h);

	NP::vector<long int>	d(12, 21464748490);
	PRINT_ALL(d);

	NP::vector<long int>	j(d.begin(), d.end());
	PRINT_ALL(j);

	NP::vector<std::string>	e(23, "Hello world");
	PRINT_ALL(e);
	NP::vector<std::string>	k(e.begin(), e.end());
	PRINT_ALL(k);
}

void	test_copy_constructor()
{
	NP::vector<char>	a(100, 'a');
	PRINT_ALL(a);
	NP::vector<char>	f(a);
	PRINT_ALL(f);

	NP::vector<int>	b(134, 431);
	PRINT_ALL(b);
	NP::vector<int>	g(b);
	PRINT_ALL(g);

	NP::vector<long>	c(34, 2148473649);
	PRINT_ALL(c);
	NP::vector<long>	h(c);
	PRINT_ALL(h);

	NP::vector<long int>	d(12, 21464748490);
	PRINT_ALL(d);

	NP::vector<long int>	j(d);
	PRINT_ALL(j);

	NP::vector<std::string>	e(23, "Hello world");
	PRINT_ALL(e);
	NP::vector<std::string>	k(e);
	PRINT_ALL(k);
}
