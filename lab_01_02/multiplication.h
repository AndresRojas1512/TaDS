#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types_macros.h"

result_type multiply_real_numbers(real_type num1, real_type num2);
void print_result_fields(result_type *result);
void print_normalized(result_type *result);

#endif