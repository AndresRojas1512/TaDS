#define _POSIX_C_SOURCE 199309L
#include "complexity_analysis.h"

int complexity_analysis(void)
{
    int exit_code = EXIT_SUCCESS;
    request_t dequeued_value;
    free_addresses_t free_addresses;
    free_addresses_init(&free_addresses);

    // debug
    free_addresses_t free_addresses_dequeue;
    free_addresses_init(&free_addresses_dequeue);
    // enddebug

    queue_sa_t queue_sa;
    queue_ll_t queue_ll;

    queue_ll_init(&queue_ll);

    int files[N_FILES] = {1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    request_t data_array[DATA_ARRAY_SIZE];
    
    unsigned long long data_time_queue_sa_fill[N_FILES];
    unsigned long long data_time_queue_sa_cleanup[N_FILES];
    unsigned long long data_time_queue_ll_fill[N_FILES];
    unsigned long long data_time_queue_ll_cleanup[N_FILES];

    array_init_zeros(data_time_queue_sa_fill, N_FILES);
    array_init_zeros(data_time_queue_sa_cleanup, N_FILES);
    array_init_zeros(data_time_queue_ll_fill, N_FILES);
    array_init_zeros(data_time_queue_ll_cleanup, N_FILES);

    int percentages[NUM_PERCENTAGES] = {1, 10, 20, 30, 40, 50, 60, 67, 70, 80, 90, 100};
    size_t memory_usage_sa;
    size_t memory_usage_ll[NUM_PERCENTAGES];

    int num_trials = NUM_TRIALS;

    for (int i = 0; i < N_FILES; i++)
    {
        char filepath[FILEPATH_LEN];
        sprintf(filepath, "./data/%d.txt", files[i]);
        exit_code = data_array_import(filepath, data_array, files[i]);
        if (!exit_code)
        {
            unsigned long long fill_total_time_sa = 0;
            unsigned long long cleanup_total_time_sa = 0;

            unsigned long long fill_total_time_ll = 0;
            unsigned long long cleanup_total_time_ll = 0;

            for (int trial = 0; trial < num_trials; trial++)
            {
                queue_sa_init(&queue_sa, files[i]);

                // queue_sa fill time
                unsigned long long beg_fill_sa = microseconds_now();
                for (int j = 0; j < files[i] && !exit_code; j++)
                {
                    exit_code = enqueue_sa(&queue_sa, data_array[j]);
                    if (exit_code)
                        printf("Error: Enqueue Static\n");
                }
                unsigned long long end_fill_sa = microseconds_now();
                fill_total_time_sa += end_fill_sa - beg_fill_sa;

                // queue_ll fill time
                unsigned long long beg_cleanup_sa = microseconds_now();
                while (!queue_sa_isempty(&queue_sa))
                {
                    if (dequeue_sa(&queue_sa, &dequeued_value))
                        printf("Error: Dequeue Static\n");
                }
                unsigned long long end_cleanup_sa = microseconds_now();
                cleanup_total_time_sa+= end_cleanup_sa - beg_cleanup_sa;

                // queue_ll fill time todo
                unsigned long long beg_fill_ll = microseconds_now();
                for (int j = 0; j < files[i] & !exit_code; j++)
                {
                    exit_code = enqueue_ll_ca(&queue_ll, &data_array[j]);
                    if (exit_code)
                        printf("Error: Enqueue List\n");
                }
                unsigned long long end_fill_ll = microseconds_now();
                fill_total_time_ll += end_fill_ll - beg_fill_ll;

                // queue_ll cleanup time todo
                unsigned long long beg_cleanup_ll = microseconds_now();
                while (!queue_ll_isempty(&queue_ll))
                {
                    exit_code = dequeue_ll_ca(&queue_ll, &dequeued_value);
                    if (exit_code)
                        printf("Error: Dequeue List\n");
                }
                free_addresses.count = 0;
                unsigned long long end_cleanup_ll = microseconds_now();
                cleanup_total_time_ll += end_cleanup_ll - beg_cleanup_ll;
            }
            data_time_queue_sa_fill[i] = fill_total_time_sa / num_trials;
            data_time_queue_sa_cleanup[i] = cleanup_total_time_sa / num_trials;
            data_time_queue_ll_fill[i] = fill_total_time_ll / num_trials;
            data_time_queue_ll_cleanup[i] = cleanup_total_time_ll / num_trials;
        }
    }
    memory_usage_analysis(&queue_ll, &queue_sa, percentages, NUM_PERCENTAGES, &memory_usage_sa, memory_usage_ll);
    microseconds_table(data_time_queue_sa_fill, data_time_queue_ll_fill, data_time_queue_sa_cleanup, data_time_queue_ll_cleanup, files, N_FILES);
    bytes_table(percentages, memory_usage_ll, memory_usage_sa, NUM_PERCENTAGES);
    
    return exit_code;
}

int data_array_import(char *filepath, request_t *data_array, int n_elements)
{
    request_t request_buffer;
    FILE *file = fopen(filepath, "r");
    if (!file)
        return EXIT_FAILURE;
    for (int i = 0; i < n_elements; i++)
    {
        if (fscanf(file, "%d %lf\n", &request_buffer.passes, &request_buffer.processing_time) != 2)
            return EXIT_FAILURE;
        data_array[i] = request_buffer;
    }
    fclose(file);
    return EXIT_SUCCESS;
}

void data_array_print(request_t *data_array, int n_elements)
{
    for (int i = 0; i < n_elements; i++)
        request_print(&data_array[i]);
}

void data_time_print(unsigned long long *data_time, int n_elements)
{
    for (int i = 0; i < n_elements; i++)
        printf("%lld\n", data_time[i]);
}

void array_init_zeros(unsigned long long *array, int n)
{
    for (int i = 0; i < n; i++)
        array[i] = 0;
}

void microseconds_table(unsigned long long *data_time_queue_sa_fill, unsigned long long *data_time_queue_ll_fill, unsigned long long *data_time_queue_sa_cleanup, unsigned long long *data_time_queue_ll_cleanup, int *elements, int rows)
{
    puts("Время, us:");
    printf("_____________________________________________________________________________________________________________________\n");
    printf("| N elements | Добавление (Статика), us | Добавление (Список), us || Удаление (Статика), us | Удаление (Список), us |\n");
    printf("|___________________________________________________________________________________________________________________|\n");
    for (int i = 0; i < rows; i++)
        printf("| %10d | %24lld | %23lld || %22lld | %21lld |\n", elements[i], data_time_queue_sa_fill[i], data_time_queue_ll_fill[i], data_time_queue_sa_cleanup[i], data_time_queue_ll_cleanup[i]);
    printf("|___________________________________________________________________________________________________________________|\n");
}

void bytes_table(int *percentages, size_t *memory_usage_ll, size_t memory_usage_sa, int num_percentages)
{
    printf("________________________________________________________________\n");
    printf("| Процент | Очередь (Статика), bytes | Очередь (Список), bytes |\n");
    printf("|______________________________________________________________|\n");
    for (int i = 0; i < num_percentages; i++)
        printf("| %7d | %24zu | %23zu |\n", percentages[i], memory_usage_sa, memory_usage_ll[i]);
    printf("|______________________________________________________________|\n");
}

void memory_usage_analysis(queue_ll_t *queue_ll, queue_sa_t *queue_sa, int *percentages, int num_percentages, size_t *memory_usage_sa, size_t *memory_usage_ll)
{
    size_t node_size = sizeof(struct ListNode);
    // printf("node size: %zu\n", node_size);
    *memory_usage_sa = queue_sa->capacity * sizeof(request_t);
    for (int i = 0; i < num_percentages; i++)
    {
        int num_elements = (queue_sa->capacity * percentages[i]) / 100;
        size_t bytes_ll = num_elements * node_size;
        memory_usage_ll[i] = bytes_ll;
    }
}

int enqueue_ll_ca(queue_ll_t *queue_ll, request_t *request)
{
    if (!queue_ll || !request)
        return EXIT_FAILURE;

    struct ListNode *tmp = node_create(*request);
    if (!tmp)
        return ERROR_NODE_ALLOCATION;

    if ((queue_ll->front) == NULL && (queue_ll->rear) == NULL)
    {
        (queue_ll->front) = (queue_ll->rear) = tmp;
        queue_ll->len += 1;
    }
    else
    {
        queue_ll->rear->next = tmp;
        queue_ll->rear = tmp;
        queue_ll->len += 1;
    }
    return EXIT_SUCCESS;
}

int dequeue_ll_ca(queue_ll_t *queue_ll, request_t *dequeued_val)
{
    if (!queue_ll)
        return EXIT_FAILURE;
    struct ListNode *tmp = queue_ll->front;
    if (queue_ll->front == NULL)
        return ERROR_EMPTY_QUEUE;
    if (queue_ll->front == queue_ll->rear)
    {
        *dequeued_val = queue_ll->front->request;
        queue_ll->front = NULL;
        queue_ll->rear = NULL;
        queue_ll->len -= 1;
    }
    else
    {
        *dequeued_val = queue_ll->front->request;
        queue_ll->front = queue_ll->front->next;
        queue_ll->len -= 1;
    }
    node_free(tmp);
    return EXIT_SUCCESS;
}

