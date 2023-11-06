#include "complexity_analysis.h"

int complexity_analysis(void)
{
    int exit_code = EXIT_SUCCESS;
    FILE *file;
    int popped_value;
    stack_static_array_t stack_sa;
    struct ListNode *stack_ll = NULL;
    int elements[N_FILES] = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int data_array[STACK_SIZE];
    unsigned long long data_time_sa[N_FILES];
    unsigned long long data_time_ll[N_FILES];
    array_init_zeros(data_time_sa, N_FILES);
    array_init_zeros(data_time_ll, N_FILES);

    unsigned long long cleanup_time_sa[N_FILES];
    unsigned long long cleanup_time_ll[N_FILES];
    array_init_zeros(cleanup_time_sa, N_FILES);
    array_init_zeros(cleanup_time_ll, N_FILES);

    int num_trials = 30;

    for (int i = 0; i < N_FILES; i++)
    {
        char filepath[FILEPATH_LEN];
        sprintf(filepath, "./data/%d.txt", elements[i]);
        exit_code = import_data_to_array(filepath, data_array, elements[i]);
        if (!exit_code)
        {
            unsigned long long total_time_sa = 0;
            unsigned long long total_time_ll = 0;

            for (int trial = 0; trial < num_trials; trial++)
            {
                // TIME FOR STATIC STACK PUSH
                stack_sa_init(&stack_sa, elements[i]);
                unsigned long long beg_sa = microseconds_now();
                for (int j = 0; j < (elements[i] / 2); j++) // Push to A
                    exit_code = push_A(&stack_sa, data_array[j]);
                for (int j = (elements[i] / 2); j < elements[i]; j++) // Push to B
                    exit_code = push_B(&stack_sa, data_array[j]);
                unsigned long long end_sa = microseconds_now();
                total_time_sa += end_sa - beg_sa;

                // TIME FOR STATIC STACK CLEANUP
                unsigned long long beg_cleanup_sa = microseconds_now();
                while (!is_empty_A(&stack_sa) || !is_empty_B(&stack_sa))
                {
                    if (!is_empty_A(&stack_sa))
                        pop_A(&stack_sa, &popped_value);
                    if (!is_empty_B(&stack_sa))
                        pop_B(&stack_sa, &popped_value);
                }
                unsigned long long end_cleanup_sa = microseconds_now();
                cleanup_time_sa[i] += end_cleanup_sa - beg_cleanup_sa;

                // TIME FOR LINKED LIST STACK PUSH
                unsigned long long beg_ll = microseconds_now();
                for (int j = 0; j < elements[i]; j++)
                {
                    exit_code = push(&stack_ll, data_array[j]);
                    if (exit_code)
                        break;
                }
                unsigned long long end_ll = microseconds_now();
                total_time_ll += end_ll - beg_ll;
                
                // TIME FOR LINKED LIST STACK CLEANUP
                unsigned long long beg_cleanup_ll = microseconds_now();
                while (stack_ll != NULL)
                    pop_ca(&stack_ll);
                unsigned long long end_cleanup_ll = microseconds_now();
                cleanup_time_ll[i] += end_cleanup_ll - beg_cleanup_ll;
            }
            data_time_sa[i] = total_time_sa / num_trials;
            data_time_ll[i] = total_time_ll / num_trials;
            cleanup_time_sa[i] = cleanup_time_sa[i] / num_trials;
            cleanup_time_ll[i] = cleanup_time_ll[i] / num_trials;
        }
    }
    printf("Data time (Static Array): ");
    array_print(data_time_sa, N_FILES);
    printf("Data time (Linked List): ");
    array_print(data_time_ll, N_FILES);
    printf("Clean time (Static Array): ");
    array_print(cleanup_time_sa, N_FILES);
    printf("Clean time (Linked List): ");
    array_print(cleanup_time_ll, N_FILES);
    return exit_code;
}

unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;
    return val.tv_sec * 1000000ULL + val.tv_usec;
}

int import_data_to_array(char *filepath, int *data_array, int n_elements)
{
    int buffer;
    FILE *file = fopen(filepath, "r");
    if (!file)
        return ERROR_CANNOT_OPEN_FILE;
    for (int i = 0; i < n_elements; i++)
    {
        if (fscanf(file, "%d", &buffer) != 1)
            return ERROR_READ_FILE_CONTENT;
        data_array[i] = buffer;
    }
    return EXIT_SUCCESS;
}

void array_print(unsigned long long *array, int n)
{
    for (int i = 0; i < n; i++)
        printf("%lld ", array[i]);
    printf("\n");
}

void array_init_zeros(unsigned long long *array, int n)
{
    for (int i = 0; i < n; i++)
        array[i] = 0;
}

void pop_ca(struct ListNode **top)
{
    if (!(*top))
        return;
    struct ListNode *tmp = *top;
    (*top) = (*top)->next;
    free(tmp);
}

int is_empty_A(stack_static_array_t *stack_sa)
{
    return (stack_sa->top_A == -1);
}

int is_empty_B(stack_static_array_t *stack_sa)
{
    return (stack_sa->top_B == stack_sa->stack_size);
}