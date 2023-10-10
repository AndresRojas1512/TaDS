#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "types_macros.h"
#include "read_house.h"
#include "helper.h"

// CASE 1: Select File
int input_file(char *filename);
// CASE 2: Import Data
int import_data(char *file_name, house_type *house_table, house_type *house_buffer, int *table_len);
// CASE 3, 4: Output Table
int print_houses_table(house_type *house_table, int house_table_len);
// CASE 5: Output Key Table (Generic)
int print_keys_table(key_type *keys_table, int house_table_len);
// CASE 7: Show Table Using Key Table
int sort_table_key_based(house_type *houses_table, key_type *keys_table, int houses_table_len);
// CASE 9: Delete in Price Range
int delete_in_price_range(house_type *house_table, double ll, double rl, int *house_table_len);
// CASE 10: Filter
int filter(house_type *house_table, int house_table_len, double ll, double rl);
// HELPER FUNCTIONS
void import_data_to_key(key_type *keys_table, house_type *houses_table, int houses_table_len, int *key_table_len);

#endif