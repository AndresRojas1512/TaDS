#include "functional.h"

// CASE 1: Select File
int input_file(char *filename)
{
    int exit_code = EXIT_SUCCESS;
    char buffer[20 + 2];
    printf("Введите имя файла (макс. длина имнеи 20 символов): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        exit_code = ERROR_READING_UB;
    else
    {
        int buffer_len = strlen(buffer);
        if (buffer[0] == '\n')
            exit_code = ERROR_FILE_NAME;
        else if (buffer_len == (20 + 1) && buffer[buffer_len - 1] != '\n')
            exit_code = ERROR_FILE_NAME;
        else
        {
            buffer[buffer_len - 1] = '\0';
            strcpy(filename, buffer);
            FILE *file = fopen(filename, "r");
            if (!file)
                exit_code = ERROR_OPEN_FILE;
            else
            {
                rewind(file);
                fclose(file);
            }
        }
    }
    return exit_code;
}

// CASE 2: Import Data
int import_data(char *filename, house_type *house_table, house_type *house_buffer, int *table_len)
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
                if ((*table_len) > MAX_TABLE_SIZE)
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

// CASE 3: Print Table
int print_houses_table(house_type *house_table, int house_table_len)
{
    int exit_code = EXIT_SUCCESS;
    if (!house_table_len)
        exit_code = ERROR_NO_DATA_IMPORTED;
    else
    {
        print_table_header();
        for (int i = 0; i < house_table_len; i++) {
            if (house_table[i].is_primary)
                print_record_primary(&house_table[i]);
            else
                print_record_secondary(&house_table[i]);
        }
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    return exit_code;
}

// CASE 5: Output Key Table (Generic)
int print_keys_table(key_type *keys_table, int key_table_len) // DONE
{
    int exit_code = EXIT_SUCCESS;
    if (!key_table_len)
        exit_code = ERROR_NO_DATA_IMPORTED;
    else
    {
        printf("\n");
        print_keys_header();
        for (int i = 0; i < key_table_len; i++)
            printf("| %-6d | %-15lf |\n", keys_table[i].ot_idx, keys_table[i].sqr_meter_price);
        printf("----------------------------\n");
    }
    return exit_code;
}

// CASE 7: Show Table Using Key Table
int sort_table_key_based(house_type *houses_table, key_type *keys_table, int key_table_len) // DONE
{
    if (!key_table_len)
        return ERROR_NO_DATA_IMPORTED;
    for (int i = 0; i < key_table_len; i++)
    {
        if (houses_table[keys_table[i].ot_idx].is_primary)
            print_record_primary(&houses_table[keys_table[i].ot_idx]);
        else if (!(houses_table[keys_table[i].ot_idx].is_primary))
            print_record_secondary(&houses_table[keys_table[i].ot_idx]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}

// CASE 9: Delete in Price Range
int delete_in_price_range(house_type *house_table, double ll, double rl, int *house_table_len)
{
    int exit_code = EXIT_SUCCESS;
    if (!(*house_table_len))
        exit_code = ERROR_NO_DATA_IMPORTED;
    else
    {
        int j = 0;
        for (int i = 0; i < *house_table_len; i++)
        {
            if (house_table[i].sqr_meter_price < ll || house_table[i].sqr_meter_price > rl)
                house_table[j++] = house_table[i];
        }
        *house_table_len = j;
        if (!(*house_table_len))
            printf("\tВнимание: После удаления, таблица стала пустой\n");
    }
    return exit_code;
}

// CASE 10: Filter
int filter(house_type *house_table, int house_table_len, double ll, double rl)
{
    int exit_code = EXIT_SUCCESS;
    if (!house_table_len)
        exit_code = EXIT_FAILURE;
    else
    {
        int count = 0;
        printf("\n");
        print_table_header();
        for (int i = 0; i < house_table_len; i++)
        {
            if ((house_table[i].is_primary == 0) && (house_table[i].rooms_n == 2) && (calc_price(house_table[i].sqr_meters, house_table[i].sqr_meter_price) >= ll) && (calc_price(house_table[i].sqr_meters, house_table[i].sqr_meter_price) <= rl))
            {
                print_house(&house_table[i]);
                count++;
            }
        }
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n");
        printf("\tКоличество: %d\n", count);
        if (!count)
            printf("\tФильтр пуст: Нет таких данных.\n");
    }
    return exit_code;
}

// HELPER
void import_data_to_key(key_type *keys_table, house_type *houses_table, int houses_table_len, int *key_table_len)
{
    for (int i = 0; i < houses_table_len; i++)
    {
        keys_table[i].ot_idx = i;
        keys_table[i].sqr_meter_price = houses_table[i].sqr_meter_price;
    }
    *key_table_len = houses_table_len;
}
