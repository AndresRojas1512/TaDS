#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "types_macros.h"
void reverse(char *str, size_t str_len);
void itos(int num, char *str);
void printer(char *general_address);
void print_record_primary(house_type *house_buffer);
void print_record_secondary(house_type *house_buffer);
int input_left_right_limits(double *ll, double *rl);
void clear_buffer(void);
void print_house(house_type *house_buffer);
double calc_price(double sqr_meters, double sqr_meters_price);
void print_table_header(void);
void print_keys_header(void);

#endif