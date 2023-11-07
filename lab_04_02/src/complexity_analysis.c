#include "complexity_analysis.h"

int complexity_analysis(void)
{
    int exit_code = EXIT_SUCCESS;
    FILE *file;
    double popped_value;
    stack_static_array_t stack_sa;
    struct ListNode buffer;
    struct ListNode *stack_ll = NULL;
    int elements[N_FILES] = {1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    int data_array[STACK_SIZE];

    // Microseconds Data
    unsigned long long data_time_sa[N_FILES];
    unsigned long long data_time_ll[N_FILES];
    array_init_zeros(data_time_sa, N_FILES);
    array_init_zeros(data_time_ll, N_FILES);

    unsigned long long cleanup_time_sa[N_FILES];
    unsigned long long cleanup_time_ll[N_FILES];
    array_init_zeros(cleanup_time_sa, N_FILES);
    array_init_zeros(cleanup_time_ll, N_FILES);

    double data_percentage_time_sa[N_FILES];
    double cleanup_percentage_time_sa[N_FILES];

    //  Memory Usage Data
    int percentages[NUM_PERCENTAGES] = {1, 10, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t memory_usage_ll[NUM_PERCENTAGES];
    size_t memory_usage_sa;

    double mem_percentage_sa[NUM_PERCENTAGES];

    
    int num_trials = NUM_TRIALS;

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
    // printf("Data time (Static Array): ");
    // array_print(data_time_sa, N_FILES);
    // printf("Data time (Linked List): ");
    // array_print(data_time_ll, N_FILES);
    // printf("Clean time (Static Array): ");
    // array_print(cleanup_time_sa, N_FILES);
    // printf("Clean time (Linked List): ");
    // array_print(cleanup_time_ll, N_FILES);
    // Time, us
    microseconds_table(data_time_sa, data_time_ll, cleanup_time_sa, cleanup_time_ll, elements, N_FILES);
    calc_time_percentage(data_time_sa, data_time_ll, cleanup_time_sa, cleanup_time_ll, data_percentage_time_sa, cleanup_percentage_time_sa, N_FILES);
    time_table_percentage(data_percentage_time_sa, cleanup_percentage_time_sa, elements, N_FILES);
    // Memory Usage, bytes
    memory_usage_analysis(buffer, STACK_SIZE, percentages, NUM_PERCENTAGES, memory_usage_ll, &memory_usage_sa);
    bytes_table(percentages, memory_usage_ll, memory_usage_sa, NUM_PERCENTAGES);
    calc_mem_percentage(memory_usage_ll, memory_usage_sa, mem_percentage_sa, NUM_PERCENTAGES);
    bytes_table_percentage(percentages, mem_percentage_sa, NUM_PERCENTAGES);
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

void array_print_size_t(size_t *array, int n)
{
    for (int i = 0; i < n; i++)
        printf("%zu ", array[i]);
    printf("\n");
}

void array_print_double(double *array, int n)
{
    for (int i = 0; i < n; i++)
        printf("%f ", array[i]);
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

void microseconds_table(unsigned long long *data_time_sa, unsigned long long *data_time_ll, unsigned long long *cleanup_time_sa, unsigned long long *cleanup_time_ll, int *elements, int rows)
{
    puts("Время, us:");
    printf("_______________________________________________________________________________________________\n");
    printf("| N elements | Push (Статика), us | Push (Список), us || Pop (Статика), us | Pop (Список), us |\n");
    printf("|_____________________________________________________________________________________________|\n");
    for (int i = 0; i < rows; i++)
        printf("| %10d | %18lld | %16lld || %18lld | %16lld |\n", elements[i], data_time_sa[i], data_time_ll[i], cleanup_time_sa[i], cleanup_time_ll[i]);
    printf("|_____________________________________________________________________________________________|\n");
}

void time_table_percentage(double *data_percentage_time_sa, double *cleanup_percentage_time_sa, int *elements, int rows)
{
    puts("Время, us:");
    printf("_______________________________________________________________________________________________\n");
    printf("| N elements | Push (Статика), us | Push (Список), us || Pop (Статика), us | Pop (Список), us |\n");
    printf("|_____________________________________________________________________________________________|\n");
    for (int i = 0; i < rows; i++)
    {
        printf("| %10d | %18f |         --        || %18f |        --       |\n", elements[i], data_percentage_time_sa[i], cleanup_percentage_time_sa[i]);
    }
    printf("|_____________________________________________________________________________________________|\n");
}

void bytes_table(int *percentages, size_t *memory_usage_ll, size_t memory_usage_sa, int num_percentages)
{
    printf("__________________________________________________________\n");
    printf("| Процент | Стек (Статика), bytes | Стек (Список), bytes |\n");
    printf("|________________________________________________________|\n");
    for (int i = 0; i < num_percentages; i++)
        printf("| %7d | %21zu | %20zu |\n", percentages[i], memory_usage_sa, memory_usage_ll[i]);
    printf("|________________________________________________________|\n");
}

void bytes_table_percentage(int *percentages, double *mem_percentage_sa, int num_percentages)
{
    printf("__________________________________________________________\n");
    printf("| Процент | Стек (Статика), bytes | Стек (Список), bytes |\n");
    printf("|________________________________________________________|\n");
    for (int i = 0; i < num_percentages; i++)
        printf("| %7d | %21f |          --          |\n", percentages[i], mem_percentage_sa[i]);
    printf("|________________________________________________________|\n");
}

void memory_usage_analysis(struct ListNode node, int static_stack_size, int *percentages, int num_percentages, size_t *memory_usage_ll, size_t *memory_usage_sa)
{
    size_t node_size = sizeof(struct ListNode);
    *memory_usage_sa = static_stack_size * sizeof(int);
    for (int i = 0; i < num_percentages; i++)
    {
        int num_elements = (static_stack_size * percentages[i]) / 100;
        size_t bytes_ll = num_elements * node_size;
        memory_usage_ll[i] = bytes_ll;
    }
}

void calc_time_percentage(unsigned long long *data_time_sa, unsigned long long *data_time_ll, unsigned long long *cleanup_time_sa, unsigned long long *cleanup_time_ll, double *data_percentage_time_sa, double *cleanup_percentage_time_sa, int data_n)
{
    for (int i = 0; i < data_n; i++)
    {
        data_percentage_time_sa[i] = (((double)data_time_ll[i] - (double)data_time_sa[i]) / (double)data_time_ll[i]) * 100.0;
        cleanup_percentage_time_sa[i] = (((double)cleanup_time_ll[i] - (double)cleanup_time_sa[i]) / (double)cleanup_time_ll[i]) * 100.0;
    }
    // array_print_double(data_percentage_time_sa, data_n);
    // array_print_double(cleanup_percentage_time_sa, data_n);
}

void calc_mem_percentage(size_t *memory_usage_ll, size_t memory_usage_sa, double *mem_percentage_sa, int data_n)
{
    for (int i = 0; i < data_n; i++)
        mem_percentage_sa[i] = (((double)memory_usage_ll[i] - memory_usage_sa) / (double)memory_usage_ll[i]) * 100.0;
    // array_print_double(mem_percentage_sa, data_n);
}