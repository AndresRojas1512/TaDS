#ifndef SYSTEM_FUNC
#define SYSTEM_FUNC

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "request.h"
#include "queue_sa.h"
#include "queue_ll.h"

#define PROCESSED_REQUESTS 1000

typedef struct system_time_t
{
    double t1;
    double t2;
} system_time_t;

double time_generate(system_time_t *system_time);
void statistic_partial_print(int requests_out, int queue_len, int median_len);
void statistic_total_print(double time_machine_work, double time_expected, double error_margin, int requests_in, int requests_out, int requests_failed, int requests_calls, double time_machine_idle);

#endif