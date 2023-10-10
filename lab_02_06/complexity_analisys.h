#ifndef COMPLEXITY_ANALISYS_H
#define COMPLEXITY_ANALISYS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "types_macros.h"
#include "functional.h"
#include "sort.h"
#include "helper.h"
#include "read_house.h"

int complex_analisys(int n);
unsigned long long microseconds_now(void);
int import_data_ca(char *filename, house_type *house_table, house_type *house_buffer, int *table_len);
void print_array(int *array, int len);
void microseconds_table(int *mysort_house_time, int *mysort_key_time, int *qsort_house_time, int *qsort_key_time, int *n_elements);
void time_complexity(int *mysort_house_time, int *mysort_key_time, int *qsort_house_time, int *qsort_key_time, int *n_elements);
void space_complexity(void);

#endif