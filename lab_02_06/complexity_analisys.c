#include "complexity_analisys.h"
#define NUM_TESTS 6
#define MAX_ELEMENTS 2000
#define FILE_PATH_LEN 20

void swap_generic(void *lval, void *rval, size_t elem_size);
void quicksort(void *array, int nitems, size_t elem_size, comparator_t comparator);
void quicksort_recursion(void *array, int low, int high, size_t elem_size, comparator_t comparator);
int partition(int *array, int low, int high, size_t elem_size, comparator_t comparator);

int complex_analisys(int n_exp)
{
    int mysort_house_time[NUM_TESTS] = {0};
    int mysort_key_time[NUM_TESTS] = {0};
    int qsort_house_time[NUM_TESTS] = {0};
    int qsort_key_time[NUM_TESTS] = {0};
    int n_elements[NUM_TESTS] = {50, 100, 500, 1000, 1500, 2000};
    for (int exp = 0; exp < n_exp; exp++)
    {
        for (int i = 0; i < NUM_TESTS; i++)
        {
            char filepath[FILE_PATH_LEN];
            sprintf(filepath, "./tests/%dh.txt", n_elements[i]);
            house_type house_buffer;
            house_type house_table[MAX_ELEMENTS];
            key_type key_table[MAX_ELEMENTS];
            int house_table_len, key_table_len;
            // mysort house
            if (import_data_ca(filepath, house_table, &house_buffer, &house_table_len))
                return EXIT_FAILURE;
            unsigned long long beg_msh = microseconds_now();
            mysort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
            unsigned long long end_msh = microseconds_now();
            mysort_house_time[i] += (end_msh - beg_msh);
            
            //mysort key
            if (import_data_ca(filepath, house_table, &house_buffer, &house_table_len))
                return EXIT_FAILURE;
            import_data_to_key(key_table, house_table, house_table_len, &key_table_len);
            unsigned long long beg_msk = microseconds_now();
            mysort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
            unsigned long long end_msk = microseconds_now();
            mysort_key_time[i] += (end_msk - beg_msk);

            //qsort house
            if (import_data_ca(filepath, house_table, &house_buffer, &house_table_len))
                return EXIT_FAILURE;
            unsigned long long beg_qh = microseconds_now();
            quicksort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
            unsigned long long end_qh = microseconds_now();
            qsort_house_time[i] += (end_qh - beg_qh);

            // qsort key
            if (import_data_ca(filepath, house_table, &house_buffer, &house_table_len))
                return EXIT_FAILURE;
            import_data_to_key(key_table, house_table, house_table_len, &key_table_len);
            unsigned long long beg_qk = microseconds_now();
            quicksort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
            unsigned long long end_qk = microseconds_now();
            qsort_key_time[i] += (end_qk - beg_qk);
        }
    }
    for (int i = 0; i < NUM_TESTS; i++)
    {
        mysort_house_time[i] /= n_exp;
        mysort_key_time[i] /= n_exp;
        qsort_house_time[i] /= n_exp;
        qsort_key_time[i] /= n_exp;
    }
    printf("\n\tДанные при %d итераций:\n", n_exp);
    microseconds_table(mysort_house_time, mysort_key_time, qsort_house_time, qsort_key_time, n_elements);
    time_complexity(mysort_house_time, mysort_key_time, qsort_house_time, qsort_key_time, n_elements);
    space_complexity();
    return EXIT_SUCCESS;
}

unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;
    return val.tv_sec * 1000000ULL + val.tv_usec;
}

int import_data_ca(char *filename, house_type *house_table, house_type *house_buffer, int *table_len)
{
    int exit_code = EXIT_SUCCESS;
    FILE *file = fopen(filename, "r");
    if (!file)
        exit_code = ERROR_OPEN_FILE;
    else
    {
        *table_len = 0;
        while (!exit_code)
        {
            exit_code = read_house(file, house_buffer);
            if (!exit_code)
            {
                if ((*table_len) > MAX_ELEMENTS)
                    exit_code = ERROR_TABLE_OVERFLOW;
                else
                    house_table[(*table_len)++] = *house_buffer;
            }
        }
        if (!(*table_len))
            exit_code = ERROR_NO_DATA_IMPORTED;
        else if ((*table_len) && (exit_code == ERROR_READING_ADDRESS) && feof(file))
            exit_code = EXIT_SUCCESS;
        rewind(file);
        fclose(file);
    }
    return exit_code;
}

void print_array(int *array, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void microseconds_table(int *mysort_house_time, int *mysort_key_time, int *qsort_house_time, int *qsort_key_time, int *n_elements)
{
    puts("Время, us:");
    printf("|___________________________________________________________________________________\n");
    printf("| N elements | mysort_house, us | mysort_key, us | qsort_house, us | qsort_key, us |\n");
    printf("|__________________________________________________________________________________|\n");
    for (int i = 0; i < 6; i++)
        printf("| %10d | %16d | %14d | %15d | %13d |\n", n_elements[i], mysort_house_time[i], mysort_key_time[i], qsort_house_time[i], qsort_key_time[i]);
    printf("|__________________________________________________________________________________|\n");
}

void time_complexity(int *mysort_house_time, int *mysort_key_time, int *qsort_house_time, int *qsort_key_time, int *n_elements)
{
    puts("Сравнение эффективности по времени в процентах:");
    printf("____________________________________________________________________________________\n");
    printf("| N elements |   mysort_house   |   mysort_key   |   qsort_house   |   qsort_key   |\n");
    printf("|__________________________________________________________________________________|\n");
    for (int i = 0; i < 6; i++)
    {
        double mysort_key_percentage = (((double)mysort_house_time[i] - (double)mysort_key_time[i]) / (double)mysort_house_time[i]) * 100.0;
        // double qsort_house_percentage = (((double)mysort_house_time[i] - (double)qsort_house_time[i]) / (double)mysort_house_time[i]) * 100.0;
        double qsort_key_percentage = (((double)qsort_house_time[i] - (double)qsort_key_time[i]) / (double)qsort_house_time[i]) * 100.0;
        printf("| %10d |        --       | %14.3lf |        --        | %13.3lf |\n", n_elements[i], mysort_key_percentage, qsort_key_percentage);
    }
    printf("|__________________________________________________________________________________|\n");
}

void space_complexity(void)
{
    puts("Исследование использования памяти в байтах: ");
    double size_percentage = (((double)sizeof(key_type)) / (double)sizeof(house_type)) * 100.0;
    printf("_________________________________________\n");
    printf("| house_type, bytes |     key, bytes    |\n");
    printf("|_______________________________________|\n");
    printf("| %17zu | %17zu |\n", sizeof(house_type), sizeof(key_type) + sizeof(house_type));
    printf("|_______________________________________|\n");
    printf("\n");
    puts("Исследование использования памяти в процентах: ");
    printf("_________________________________________\n");
    printf("| house_type, bytes |     key, bytes    |\n");
    printf("|_______________________________________|\n");
    printf("|         --        | %17.3lf |\n", size_percentage);
    printf("|_______________________________________|\n");
}

// QUICKSORT
void swap_generic(void *lval, void *rval, size_t elem_size)
{
    char tmp;
    char *ptr_lval = lval;
    char *ptr_rval = rval;
    for (size_t i = 0; i < elem_size; i++, ptr_lval++, ptr_rval++)
    {
        tmp = *ptr_lval;
        *ptr_lval = *ptr_rval;
        *ptr_rval = tmp;
    }
}

void quicksort(void *array, int nitems, size_t elem_size, comparator_t comparator)
{
    srand(time(NULL));
    quicksort_recursion(array, 0, nitems - 1, elem_size, comparator);
}

void quicksort_recursion(void *array, int low, int high, size_t elem_size, comparator_t comparator)
{
    if (low < high)
    {
        int pivot_index = partition(array, low, high, elem_size, comparator);
        quicksort_recursion(array, low, pivot_index - 1, elem_size, comparator);
        quicksort_recursion(array ,pivot_index + 1, high, elem_size, comparator);
    }
}

int partition(int *array, int low, int high, size_t elem_size, comparator_t comparator)
{
    int pivot_index = low + (rand() % (high - low));
    char *base_ptr = (char *) array;
    if (pivot_index != high)
        swap_generic(base_ptr + pivot_index * elem_size, base_ptr + high * elem_size, elem_size);
    void *pivot_value = base_ptr + high * elem_size;
    int i = low;
    for (int j = low; j < high; j++)
    {
        if (comparator(base_ptr + j * elem_size, pivot_value) <= 0)
        {
            swap_generic(base_ptr + i * elem_size, base_ptr + j * elem_size, elem_size);
            i++;
        }
    }
    swap_generic(base_ptr + i * elem_size, pivot_value, elem_size);
    return i;
}