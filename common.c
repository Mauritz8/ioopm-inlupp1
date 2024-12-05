#include <string.h>
#include <stdbool.h>
#include "common.h"

bool ioopm_int_eq_function(elem_t a, elem_t b)
{
  return a.int_num == b.int_num;
}

bool ioopm_bool_eq_function(elem_t a, elem_t b)
{
    return a.boolean == b.boolean;
}
bool ioopm_float_eq_function(elem_t a, elem_t b)
{
    return a.float_num == b.float_num;
}

bool ioopm_str_eq_function(elem_t a, elem_t b)
{
  return strcmp(a.str, b.str) == 0;
}
