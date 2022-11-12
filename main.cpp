#include "tests/main.hpp"
#include "tests/vector/vector_prelude.hpp"
#include <cstdlib>

int main()
{
	test_default_constructor();
	test_fill_constructor();
	test_range_constructor();
	test_copy_constructor();
	
	test_operator_equal();

	test_assign_val();
	test_assign_range();
	test_assign_mix();
	return 0;
}
