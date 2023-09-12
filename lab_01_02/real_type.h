#ifndef REAL_TYPE_H
#define REAL_TYPE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types_macros.h"

int validate_real_string(char *real_string);
int validate_real_type(char *str);
int parse_number(char *str, real_type *real_number);
void print_real_struct(real_type *real_number);
void normalize(const real_type *input, real_type *output);

#endif