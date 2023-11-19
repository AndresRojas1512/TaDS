#include "system_func.h"

void queue_sa_system(queue_sa_t *queue_sa, system_time_t *time_in_range, system_time_t *time_out_range, int process_count)
{
    // counters
    int requests_in = 0; // amount on enqueued requests
    int requests_out = 0; // amount of requests that left the system
    int requests_failed = 0; // amount of not appended requested
    int requests_calls = 0; // amount of times that the SU called a new element

    // time
    double time_machine_work = 0; // SU working
    double time_machine_idle = 0; // SU maiting

    double time_in = time_generate(time_in_range); // time for the first  request
    double time_out = -1; // processing time for a cur task

    int len_general = 0;

    request_t request_cur; // current request

    while (requests_out <= PROCESSED_REQUESTS)
    {
        if (time_out < 0 || time_in < time_out)
        {
            if (time_out < 0)
                time_machine_idle += time_in;
            time_machine_work += time_in;
            time_out -= time_in;
            time_in = time_generate(time_in_range);
            request_t request = {.passes = 0, .processing_time = (time_generate(time_out_range))};
            if (enqueue_sa(queue_sa, request))
                printf("Queue Overflow!\n");
            else
                requests_in++;
            if (time_out < 0 && queue_sa->count_passed_requests)
            {
                if (dequeue_sa(queue_sa, &request_cur))
                    printf("Dequeue Error\n");
                else
                    time_out = request_cur.processing_time;
            }
        }
        else
        {
            time_in -= time_out;
            time_machine_work += time_out;
            time_out = 0;
            
            request_cur.passes++;
            requests_calls++;
            
            if (request_cur.passes < process_count)
            {
                request_cur.processing_time = time_generate(time_out_range);
                if (enqueue_sa(queue_sa, request_cur))
                {
                    printf("Enqueue Error\n");
                    requests_failed++;
                }
            }
            else
            {
                len_general += queue_sa->count_passed_requests;
                requests_out++;
                if (requests_out % 100 == 0)
                    statistic_partial_print(requests_out, queue_sa->count_passed_requests, len_general / requests_out);
            }
            if (queue_sa_isempty(queue_sa))
                time_out -= 1;
            else
            {
                if (dequeue_sa(queue_sa, &request_cur))
                    printf("Dequeue Error.\n");
                time_out = request_cur.processing_time;
            }
        }
    }
    double time_expected;
    if ((time_in_range->t1 + time_in_range->t2) / 2 * 1000 > (time_out_range->t1 + time_out_range->t2) / 2 * process_count * 1000)
        time_expected = (time_in_range->t1 + time_in_range->t2) / 2 * 1000;
    else
        time_expected = requests_calls * (time_out_range->t1 + time_out_range->t2) / 2;
    
    double error_margin = fabs(time_machine_work - time_expected) / time_expected * 100;
    statistic_total_print(time_machine_work, time_expected, error_margin, requests_in, requests_out, requests_failed, requests_calls, time_machine_idle);
}

void queue_ll_system(struct ListNode **front, struct ListNode **rear, system_time_t *time_in_range, system_time_t *time_out_range, int process_count)
{
    return;
}

double time_generate(system_time_t *system_time)
{
    double t = (double)rand() / RAND_MAX;
    return (system_time->t2 - system_time->t1) * t + system_time->t1;
}

void statistic_partial_print(int requests_out, int queue_len, int median_len)
{
    printf("Requests processed: %d.\n", requests_out);
    printf("Queue len: %d.\n", queue_len);
    printf("Queue Median Len: %d\n", median_len);
}

void statistic_total_print(double time_machine_work, double time_expected, double error_margin, int requests_in, int requests_out, int requests_failed, int requests_calls, double time_machine_idle)
{
    printf("Machine working time: %f\n", time_machine_work);
    printf("Machine working time expected: %f\n", time_expected);
    printf("Margin error: %f\n", error_margin);
    printf("In Requests: %d\n", requests_in);
    printf("Out Requests: %d\n", requests_out);
    printf("Failed Requests: %d\n", requests_failed);
    printf("Machine Calls: %d\n", requests_calls);
    printf("Time Machine Idle: %f\n", time_machine_idle);
}

int time_range_validate(system_time_t *system_time, double llimit, double rlimit)
{
    double t1_buf, t2_buf;
    if (scanf("%lf %lf", &t1_buf, &t2_buf) != 2)
        return ERROR_SYSTEM_TIME_INPUT;
    if (t1_buf < llimit || t2_buf > rlimit || t2_buf < t1_buf)
        return ERROR_SYSTEM_TIME_RANGE;
    system_time->t1 = t1_buf;
    system_time->t2 = t2_buf;
    return EXIT_SUCCESS;
}