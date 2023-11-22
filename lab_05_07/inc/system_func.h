#ifndef SYSTEM_FUNC
#define SYSTEM_FUNC

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "request.h"
#include "queue_sa.h"
#include "queue_ll.h"

#define ERROR_SYSTEM_TIME_INPUT 20
#define ERROR_SYSTEM_TIME_RANGE 21

#define PROCESSED_REQUESTS 1000
#define SYSTEM_TIME_LLIM 0
#define SYSTEM_TIME_RLIM 10000

typedef struct system_time_t
{
    double t1;
    double t2;
} system_time_t;

void queue_sa_system(queue_sa_t *queue_sa, system_time_t *time_in_range, system_time_t *time_out_range, int process_count);
void queue_ll_system(queue_ll_t *queue_ll, free_addresses_t *free_addresses, system_time_t *time_in_range, system_time_t *time_out_range, int process_count);
double time_generate(system_time_t *system_time);
void statistic_partial_print(int requests_out, int queue_len, int median_len);
void statistic_total_print(double time_machine_work, double time_expected, double error_margin, int requests_in, int requests_out, int requests_failed, int requests_calls, double time_machine_idle);
int time_range_validate(system_time_t *system_time, double llimit, double rlimit);
unsigned long long microseconds_now(void);
int addresses_file_output(void **addresses, int addresses_count);

#endif