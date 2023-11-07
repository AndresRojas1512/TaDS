#ifndef COMPLEXITY_ANALYSIS
#define COMPLEXITY_ANALYSIS

#include <stdio.h>
#include <stdlib.h>
#include "stack_ll.h"
#include "stack_sa.h"
#include <time.h>
#include <sys/time.h>

#define N_FILES 11
#define N_EXP 10
#define FILEPATH_LEN 20
#define NODE_SIZE (sizeof(struct ListNode))
#define NUM_TRIALS 100
#define NUM_PERCENTAGES 12
#define ERROR_CANNOT_OPEN_FILE 30
#define ERROR_READ_FILE_CONTENT 31

int complexity_analysis(void);
int import_data(char *filepath);
int import_data_to_array(char *filepath, int *data_array, int n_elements);
unsigned long long microseconds_now(void);
void array_init_zeros(unsigned long long *array, int n);
void pop_ca(struct ListNode **top);
void array_print(unsigned long long *array, int n);
void array_print_size_t(size_t *array, int n);
void array_print_double(double *array, int n);

int is_empty_A(stack_static_array_t *stack_sa);
int is_empty_B(stack_static_array_t *stack_sa);

void microseconds_table(unsigned long long *data_time_sa, unsigned long long *data_time_ll, unsigned long long *cleanup_time_sa, unsigned long long *cleanup_time_ll, int *elements, int rows);
void time_table_percentage(double *data_percentage_time_sa, double *cleanup_percentage_time_sa, int *elements, int rows);

void bytes_table(int *percentages, size_t *memory_usage_ll, size_t memory_usage_sa, int num_percentages);
void bytes_table_percentage(int *percentages, double *mem_percentage_sa, int num_percentages);

void calc_time_percentage(unsigned long long *data_time_sa, unsigned long long *data_time_ll, unsigned long long *cleanup_time_sa, unsigned long long *cleanup_time_ll, double *data_percentage_time_sa, double *cleanup_percentage_time_sa, int data_n);
void calc_mem_percentage(size_t *memory_usage_ll, size_t memory_usage_sa, double *mem_percentage_sa, int data_n);

void memory_usage_analysis(struct ListNode node, int static_stack_size, int *percentages, int num_percentages, size_t *memory_usage_ll, size_t *memory_usage_sa);
#endif