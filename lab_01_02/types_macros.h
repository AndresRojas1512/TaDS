#ifndef TYPES_MACROS_H
#define TYPES_MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct result_type
{
    char mantissa[1000 + 1];
    char base_sign;
    int decimal_point_index;
    int power;
} result_type;

#endif