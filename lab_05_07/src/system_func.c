#define _POSIX_C_SOURCE 199309L
#include "system_func.h"

void queue_sa_system(queue_sa_t *queue_sa, system_time_t *time_in_range, system_time_t *time_out_range, int request_repeat_times)
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

    // printf("Queue Status Before Process:\n");
    // queue_sa_print_general(queue_sa);

    request_t request_cur; // current request
    request_init(&request_cur);
    
    unsigned long long time_start = microseconds_now(); // time start

    while (requests_out != PROCESSED_REQUESTS)
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
            {
                requests_failed++;
                // printf("Queue Overflow!\n");
            }
            else
                requests_in++;
            if (time_out < 0 && queue_sa->size)
            {
                if (dequeue_sa(queue_sa, &request_cur))
                    printf("Ошибка: Dequeue\n");
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
            
            if (request_cur.passes < request_repeat_times)
            {
                request_cur.processing_time = time_generate(time_out_range);
                if (enqueue_sa(queue_sa, request_cur))
                {
                    // printf("Enqueue Error\n");
                    requests_failed++;
                }
            }
            else
            {
                len_general += queue_sa->size;
                requests_out++;
                if (requests_out % 100 == 0)
                    statistic_partial_print(requests_out, queue_sa->size, len_general / requests_out);
            }
            if (queue_sa_isempty(queue_sa))
                time_out -= 1;
            else
            {
                if (dequeue_sa(queue_sa, &request_cur))
                    printf("Ошибка: Dequeue\n\n");
                time_out = request_cur.processing_time;
            }
        }
    }

    unsigned long long time_end = microseconds_now();
    unsigned long long time_system_elapsed = time_end - time_start;
    // printf("\tSystem Time: %lld\n", time_system_elapsed);

    double time_expected;
    if ((time_in_range->t1 + time_in_range->t2) / 2 * PROCESSED_REQUESTS > (time_out_range->t1 + time_out_range->t2) / 2 * request_repeat_times * PROCESSED_REQUESTS)
        time_expected = (time_in_range->t1 + time_in_range->t2) / 2 * PROCESSED_REQUESTS;
    else
        time_expected = requests_calls * (time_out_range->t1 + time_out_range->t2) / 2;
    
    double error_margin = fabs(time_machine_work - time_expected) / time_expected * 100;
    statistic_total_print(time_machine_work, time_expected, error_margin, requests_in, requests_out, requests_failed, requests_calls, time_machine_idle);
}

// QUEUE_LL_SYSTEM
void queue_ll_system(queue_ll_t *queue_ll, free_addresses_t *free_addresses, system_time_t *time_in_range, system_time_t *time_out_range, int request_repeat_times)
{
    int requests_in = 0;
    int requests_out = 0;
    int requests_failed = 0;
    int requests_calls = 0;

    double time_machine_work = 0;
    double time_machine_idle = 0;

    double time_in = time_generate(time_in_range);
    double time_out = -1;
    
    int len_general = 0;

    int mem_reused = 0;
    int mem_new = 0;
    int mem_flag = 0;

    // debug addresses for dequeue
    free_addresses_t free_addresses_dequeue;
    free_addresses_init(&free_addresses_dequeue);

    free_addresses_init(free_addresses);

    request_t request_cur; // current request

    unsigned long long time_start = microseconds_now();
    
    while (requests_out != PROCESSED_REQUESTS)
    {
        if (time_out < 0 || time_in < time_out)
        {
            if (time_out < 0)
                time_machine_idle += time_in;
            time_machine_work += time_in;
            time_out -= time_in;
            time_in = time_generate(time_in_range);
            request_t request = {.passes = 0, .processing_time = time_generate(time_out_range)};
            if (enqueue_ll(queue_ll, &request, free_addresses))
            {
                // printf("Error Node Allocation\n");
                requests_failed++;
            }
            else
            {
                // mem_flag = memory_check(queue_ll, free_addresses);
                // if (mem_flag)
                    // mem_reused++;
                // else
                    // mem_new++;
                requests_in++;
            }
            if (time_out < 0 && !queue_ll_isempty(queue_ll))
            {
                if (dequeue_ll(queue_ll, &request_cur, &free_addresses_dequeue))
                    printf("Ошибка: Dequeue\n");
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

            if (request_cur.passes < request_repeat_times)
            {
                request_cur.processing_time = time_generate(time_out_range);
                if (enqueue_ll(queue_ll, &request_cur, free_addresses))
                {
                    // printf("Enqueue Error\n");
                    requests_failed++;
                }
                // else
                // {
                //     mem_flag = memory_check(queue_ll, free_addresses);
                //     if (mem_flag)
                //         mem_reused++;
                //     else
                //         mem_new++;
                // }
            }
            else
            {
                len_general += queue_ll->len;
                requests_out++;
                if (requests_out % 100 == 0)
                    statistic_partial_print(requests_out, queue_ll->len, len_general / requests_out);
            }
            if (queue_ll_isempty(queue_ll))
                time_out = -1;
            else
            {
                if (dequeue_ll(queue_ll, &request_cur, &free_addresses_dequeue))
                    printf("Ошибка: Dequeue\n");
                time_out = request_cur.processing_time;
            }
        }
    }

    // START DEBUG
    // debug allocated
    // printf("\tDebug Allocated: %d\n", free_addresses->count);
    // printf("\tNode Size: %zu\n", sizeof(struct ListNode));
    // free_addresses_print(free_addresses);

    // debug deallocated
    // printf("Debug Deallocated: %d\n", free_addresses_dequeue.count);
    // free_addresses_print(&free_addresses_dequeue);
    // enddebug deallocated

    // compare addresses
    // if (free_addresses_compare(free_addresses, &free_addresses_dequeue))
    //     printf("\tAre different\n");
    // else
    //     printf("\tAre the same\n");
    // END DEBUG
    
    unsigned long long time_end = microseconds_now();
    unsigned long long time_system_elapsed = time_end - time_start;
    // printf("\tSystem Time: %lld\n", time_system_elapsed);

    double time_expected;
    if ((time_in_range->t1 + time_in_range->t2) / 2 * PROCESSED_REQUESTS > (time_out_range->t1 + time_out_range->t2) / 2 * request_repeat_times * PROCESSED_REQUESTS)
        time_expected = (time_in_range->t1 + time_in_range->t2) / 2 * PROCESSED_REQUESTS;
    else
        time_expected = requests_calls * (time_out_range->t1 + time_out_range->t2) / 2;
    double error_margin = fabs(time_machine_work - time_expected) / time_expected * 100;
    statistic_total_print(time_machine_work, time_expected, error_margin, requests_in, requests_out, requests_failed, requests_calls, time_machine_idle);

    printf("\tПроверка фрагментации памяти\n");
    printf("Уникальные адресса памяти элементов по порядку обслуживания ОА были сохранены в файле addresses_output.txt\n");
    int free_addresses_singles_count = 0;
    void **free_addresses_singles = free_addresses_remove_dup(&free_addresses_dequeue, &free_addresses_singles_count);
    if (!free_addresses_singles)
        printf("Error: free_addresses_singles allocate\n");
    else
    {
        if (addresses_file_output(free_addresses_singles, free_addresses_singles_count))
            printf("Error: Write File Output\n");
    }
    free(free_addresses_singles);
    if ((!queue_ll_isempty(queue_ll)))
        queue_ll_free(queue_ll);
}

int addresses_file_output(void **addresses, int addresses_count)
{
    FILE *file;
    file = fopen("addresses_output.txt", "w");
    if (!file)
    {
        printf("Error: File Output Openning\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < addresses_count; i++)
        fprintf(file, "%p\n", addresses[i]);
    fclose(file);
    return EXIT_SUCCESS;
}

double time_generate(system_time_t *system_time)
{
    double t = (double)rand() / RAND_MAX;
    return (system_time->t2 - system_time->t1) * t + system_time->t1;
}

void statistic_partial_print(int requests_out, int queue_len, int median_len)
{
    printf("\n");
    printf("Количество обслужанных заявок: %d.\n", requests_out);
    printf("Текущая длина очереди: %d.\n", queue_len);
    printf("Средняя длина очереди: %d\n", median_len);
    printf("\n");
}

void statistic_total_print(double time_machine_work, double time_expected, double error_margin, int requests_in, int requests_out, int requests_failed, int requests_calls, double time_machine_idle)
{
    printf("\n");
    printf("Время работы ОА: %f\n", time_machine_work);
    printf("Ожидаемое время работы ОА: %f\n", time_expected);
    printf("Погрешность: %f\n", error_margin);
    printf("Количесвто вошедших в систему заявок: %d\n", requests_in);
    printf("Количество вышедших из системы заявок: %d\n", requests_out);
    // printf("Failed Requests: %d\n", requests_failed);
    printf("Количество срабатываний ОА: %d\n", requests_calls);
    printf("Время простоя ОА: %f\n", time_machine_idle);
    printf("\n");
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

unsigned long long microseconds_now(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
        return (unsigned long long) -1;
    return (unsigned long long)ts.tv_sec * 1000000ULL + (unsigned long long)ts.tv_nsec / 1000;
}