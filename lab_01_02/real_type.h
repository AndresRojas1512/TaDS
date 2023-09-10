#ifndef REAL_TYPE_H
#define REAL_TYPE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_REAL_LEN 51
#define MAX_REAL_MANTISSA_LEN 40
#define MAX_REAL_POWER_LEN 5

typedef struct real_type
{
    char mantissa[40 + 1];
    char base_sign;
    int decimal_index;
    int power;
} real_type;

int validate_real_string(char *real_string);
int validate_real_type(char *str);
int parse_number(char *str, real_type *real_number);
void print_real_struct(real_type *real_number);

#endif