#include "complexity_analisys.h"

int complex_analisys(void)
{
    int mysort_house_time[6];
    int mysort_key_time[6];
    int qsort_house_time[6];
    int qsort_key_time[6];
    int n_elements[6] = {50, 100, 500, 1000, 1500, 2000};

    int exit_code = EXIT_SUCCESS;
    {
        house_type house_buffer;
        house_type house_table[50];
        int house_table_len;
        exit_code = import_data_ca("./tests/50h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_house_time[0] = end - beg;
    }
    {
        house_type house_buffer;
        house_type house_table[100];
        int house_table_len;
        exit_code = import_data_ca("./tests/100h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_house_time[1] = end - beg;
    }
    {
        house_type house_buffer;
        house_type house_table[500];
        int house_table_len;
        exit_code = import_data_ca("./tests/500h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_house_time[2] = end - beg;
    }
    {
        house_type house_buffer;
        house_type house_table[1000];
        int house_table_len;
        exit_code = import_data_ca("./tests/1000h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_house_time[3] = end - beg;
    }
    {
        house_type house_buffer;
        house_type house_table[1500];
        int house_table_len;
        exit_code = import_data_ca("./tests/1500h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_house_time[4] = end - beg;
    }
    {
        house_type house_buffer;
        house_type house_table[2000];
        int house_table_len;
        exit_code = import_data_ca("./tests/2000h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_house_time[5] = end - beg;
    }
    // print_array(mysort_house_time, 6);
    // KEY TABLE
    {
        house_type house_buffer;
        key_type key_table[50];
        house_type house_table[50];
        int house_table_len;
        exit_code = import_data_ca("./tests/50h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_key_time[0] = end - beg;
    }
    {
        house_type house_buffer;
        key_type key_table[100];
        house_type house_table[100];
        int house_table_len;
        exit_code = import_data_ca("./tests/100h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_key_time[1] = end - beg;
    }
    {
        house_type house_buffer;
        key_type key_table[500];
        house_type house_table[500];
        int house_table_len;
        exit_code = import_data_ca("./tests/500h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_key_time[2] = end - beg;
    }
    {
        house_type house_buffer;
        key_type key_table[1000];
        house_type house_table[1000];
        int house_table_len;
        exit_code = import_data_ca("./tests/1000h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_key_time[3] = end - beg;
    }
    {
        house_type house_buffer;
        key_type key_table[1500];
        house_type house_table[1500];
        int house_table_len;
        exit_code = import_data_ca("./tests/1500h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_key_time[4] = end - beg;
    }
    {
        house_type house_buffer;
        key_type key_table[2000];
        house_type house_table[2000];
        int house_table_len;
        exit_code = import_data_ca("./tests/2000h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        mysort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        mysort_key_time[5] = end - beg;
    }
    // print_array(mysort_key_time, 6);
    // QSORT
    {
        house_type house_buffer;
        house_type house_table[50];
        int house_table_len;
        exit_code = import_data_ca("./tests/50h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_house_time[0] = end - beg;
    }
    {
        house_type house_buffer;
        house_type house_table[100];
        int house_table_len;
        exit_code = import_data_ca("./tests/100h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_house_time[1] = end - beg;
    }
    {
        house_type house_buffer;
        house_type house_table[500];
        int house_table_len;
        exit_code = import_data_ca("./tests/500h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_house_time[2] = end - beg;
    }
    {
        house_type house_buffer;
        house_type house_table[1000];
        int house_table_len;
        exit_code = import_data_ca("./tests/1000h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_house_time[3] = end - beg;
    }
    {
        house_type house_buffer;
        house_type house_table[1500];
        int house_table_len;
        exit_code = import_data_ca("./tests/1500h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_house_time[4] = end - beg;
    }
    {
        house_type house_buffer;
        house_type house_table[2000];
        int house_table_len;
        exit_code = import_data_ca("./tests/2000h.txt", house_table, &house_buffer, &house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_house_time[5] = end - beg;
    }
    // print_array(qsort_house_time, 6);
    // KEY QSORT
    {
        house_type house_buffer;
        key_type key_table[50];
        house_type house_table[50];
        int house_table_len;
        exit_code = import_data_ca("./tests/50h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_key_time[0] = end - beg;
    }
    {
        house_type house_buffer;
        key_type key_table[100];
        house_type house_table[100];
        int house_table_len;
        exit_code = import_data_ca("./tests/100h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_key_time[1] = end - beg;
    }
    {
        house_type house_buffer;
        key_type key_table[500];
        house_type house_table[500];
        int house_table_len;
        exit_code = import_data_ca("./tests/500h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_key_time[2] = end - beg;
    }
    {
        house_type house_buffer;
        key_type key_table[1000];
        house_type house_table[1000];
        int house_table_len;
        exit_code = import_data_ca("./tests/1000h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_key_time[3] = end - beg;
    }
    {
        house_type house_buffer;
        key_type key_table[1500];
        house_type house_table[1500];
        int house_table_len;
        exit_code = import_data_ca("./tests/1500h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_key_time[4] = end - beg;
    }
    {
        house_type house_buffer;
        key_type key_table[2000];
        house_type house_table[2000];
        int house_table_len;
        exit_code = import_data_ca("./tests/2000h.txt", house_table, &house_buffer, &house_table_len);
        import_data_to_key(key_table, house_table, house_table_len);
        unsigned long long beg = microseconds_now();
        qsort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
        unsigned long long end = microseconds_now();
        // printf("%d %llu\n", house_table_len, end - beg);
        qsort_key_time[5] = end - beg;
    }
    // print_array(qsort_key_time, 6);
    output_results(mysort_house_time, mysort_key_time, qsort_house_time, qsort_key_time, n_elements);
    time_complexity(mysort_house_time, mysort_key_time, qsort_house_time, qsort_key_time, n_elements);
    space_complexity();
    return exit_code;
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
        exit_code = EXIT_FAILURE;
    else
    {
        *table_len = 0;
        while (!exit_code)
        {
            exit_code = read_house(file, house_buffer);
            if (!exit_code)
            {
                if ((*table_len) > 2001)
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

void output_results(int *mysort_house_time, int *mysort_key_time, int *qsort_house_time, int *qsort_key_time, int *n_elements)
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
        double qsort_house_percentage = (((double)mysort_house_time[i] - (double)qsort_house_time[i]) / (double)mysort_house_time[i]) * 100.0;
        double qsort_key_percentage = (((double)mysort_house_time[i] - (double)qsort_key_time[i]) / (double)mysort_house_time[i]) * 100.0;
        printf("| %10d |        --       | %14.3lf | %16.3lf | %13.3lf |\n", n_elements[i], mysort_key_percentage, qsort_house_percentage, qsort_key_percentage);
    }
    printf("|__________________________________________________________________________________|\n");
}

void space_complexity(void)
{
    puts("Исследование использования памяти в байтах: ");
    double size_percentage = (((double)sizeof(house_type) - (double)sizeof(key_type)) / (double)sizeof(house_type)) * 100.0;
    printf("_________________________________________\n");
    printf("| house_type, bytes |     key, bytes    |\n");
    printf("|_______________________________________|\n");
    printf("| %17zu | %17zu |\n", sizeof(house_type), sizeof(key_type));
    printf("|_______________________________________|\n");
    printf("\n");
    puts("Исследование использования памяти в процентах: ");
    printf("_________________________________________\n");
    printf("| house_type, bytes |     key, bytes    |\n");
    printf("|_______________________________________|\n");
    printf("|         --        | %17.3lf |\n", size_percentage);
    printf("|_______________________________________|\n");
}