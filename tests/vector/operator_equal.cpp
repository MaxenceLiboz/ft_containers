#include "vector_prelude.hpp"

void	test_operator_equal()
{
		SETUP_ARRAYS()

		NP::vector<std::string> v1;
		NP::vector<std::string> v2;

        v1 = v2;
        PRINT_ALL(v1);

        v2 = NP::vector<std::string>(b_string, b_string + b_size);
        PRINT_ALL(v2);

        v1 = v2;
        PRINT_ALL(v1);

        v2 = NP::vector<std::string>(s_string, s_string + s_size);
        PRINT_ALL(v2);

        v1 = v2;
        PRINT_ALL(v1);
}
