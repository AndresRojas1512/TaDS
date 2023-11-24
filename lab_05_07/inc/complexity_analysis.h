#ifndef COMPLEXITY_ANALYSIS_H
#define COMPLEXITY_ANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <x86intrin.h>
#include "request.h"
#include "queue_sa.h"
#include "queue_ll.h"
#include "system_func.h"

#define N_FILES 11
#define NUM_PERCENTAGES 12
#define NUM_TRIALS 1000
#define FILEPATH_LEN 25
#define DATA_ARRAY_SIZE 100000

int complexity_analysis(void);
int data_array_import(char *filepath, request_t *data_array, int n_elements);
void data_array_print(request_t *data_array, int n_elements);
void data_time_print(unsigned long long *data_time, int n_elements);
void array_init_zeros(unsigned long long *array, int n);
void microseconds_table(unsigned long long *data_time_queue_sa_fill, unsigned long long *data_time_queue_ll_fill, unsigned long long *data_time_queue_sa_cleanup, unsigned long long *data_time_queue_ll_cleanup, int *elements, int rows);
void bytes_table(int *percentages, size_t *memory_usage_ll, size_t memory_usage_sa, int num_percentages);
void memory_usage_analysis(queue_ll_t *queue_ll, queue_sa_t *queue_sa, int *percentages, int num_percentages, size_t *memory_usage_sa, size_t *memory_usage_ll);

int enqueue_ll_ca(queue_ll_t *queue_ll, request_t *request);
int dequeue_ll_ca(queue_ll_t *queue_ll, request_t *dequeued_val);
#endif