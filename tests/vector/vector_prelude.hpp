#pragma once

#include "../../containers/vector.hpp"
#include "../main.hpp"

#define PRINT_SIZE(v) std::cout << v.size(); PRINT_FILE_LINE()
#define PRINT_CAPACITY(v) std::cout << v.capacity(); PRINT_FILE_LINE()
#define PRINT_VECTOR(v) \
std::cout << "{";\
for(size_t i = 0; i < v.size(); i++) {std::cout << v[i] << (i == v.size() - 1 ? "" : ", ");}\
std::cout << "}";\
PRINT_FILE_LINE()\

#define PRINT_ALL(v) PRINT_SIZE(v) PRINT_CAPACITY(v) PRINT_VECTOR(v)

void	test_default_constructor();
void	test_fill_constructor();
void	test_range_constructor();
void	test_copy_constructor();

void	test_operator_equal();

void	test_assign_val();
void	test_assign_range();
void	test_assign_mix();


