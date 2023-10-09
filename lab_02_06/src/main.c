#include <stdio.h>
#include <stdlib.h>
#include "types_macros.h"
#include "functional.h"
#include "sort.h"
#include "ui.h"
#include "helper.h"
#include "user_read.h"
#include "complexity_analisys.h"

int main(void)
{
    char filename[FILE_NAME_SIZE + 1];
    int exit_code = EXIT_SUCCESS;
    int choice;
    double ll, rl;
    house_type house_buffer;
    house_type house_table[MAX_TABLE_SIZE];
    key_type key_table[MAX_TABLE_SIZE];
    int house_table_len = 0;
    do
    {
        menu();
        if (input_choice(&choice))
            printf("Введите операцию:\n");
        else
        {
            switch (choice)
            {
            case 1:
                exit_code = input_file(filename);
                if (exit_code == ERROR_OPEN_FILE)
                    puts("\tОшибка Файл не найден");
                else if (exit_code == ERROR_FILE_NAME)
                    puts("\tОшибка при вводе имени файла");
                else if (!exit_code)
                    puts("\tУспешно: Файл найден");
                break;
            case 2:
                exit_code = import_data(filename, house_table, &house_buffer, &house_table_len);
                if (!exit_code)
                {
                    puts("\tУспешно: Данные импортированы! Таблица ключей оформлена");
                    import_data_to_key(key_table, house_table, house_table_len);
                }
                else
                {
                    if (exit_code == ERROR_OPEN_FILE)
                        puts("\tОшибка: Открытие файла.");
                    else if (exit_code == ERROR_TABLE_OVERFLOW)
                        puts("\tОшибка: Файл превышает макимальный объем данных");
                    else if (exit_code == ERROR_NO_DATA_IMPORTED)
                        puts("\tОшибка: Чтениие файла. Данные не соответсвуют формату");
                }
                break;
            case 3:
                exit_code = print_houses_table(house_table, house_table_len);
                if (exit_code == ERROR_NO_DATA_IMPORTED)
                    puts("\tОшибка: Нет данных для печатия");
                break;
            case 4:
                mysort(house_table, house_table_len, sizeof(house_type), house_price_comparator);
                exit_code = print_houses_table(house_table, house_table_len);
                if (exit_code == ERROR_NO_DATA_IMPORTED)
                    puts("\tОшибка: Нет данных для сортировки");
                break;
            case 5:
                exit_code = print_keys_table(key_table, house_table_len);
                if (exit_code == ERROR_NO_DATA_IMPORTED)
                    puts("\tОшибка: Нет данных для печатия");
                break;
            case 6:
                mysort(key_table, house_table_len, sizeof(key_type), key_price_comparator);
                exit_code = print_keys_table(key_table, house_table_len);
                if (exit_code == ERROR_NO_DATA_IMPORTED)
                    puts("\tОшибка: Нет данных для сортировки");
                break;
            case 7:
                exit_code = sort_table_key_based(house_table, key_table, house_table_len);
                if (exit_code == ERROR_NO_DATA_IMPORTED)
                    puts("\tОшибка: Нет данных для печатия");
                break;
            case 8:
                exit_code = append_house(&house_buffer, house_table, &house_table_len);
                if (exit_code == ERROR_CANNOT_ADD_OVERFLOW)
                    puts("\tОшибка: Таблица имеет масимальный размер");
                else if (exit_code == ERROR_INPUT_ADDRESS)
                    puts("\tОшибка: Ввод адреса");
                else if (exit_code == ERROR_READING_SQR_METERS)
                    puts("\tОшибка: Ввод квадратных метров");
                else if (exit_code == ERROR_READING_ROOMS_N)
                    puts("\tОшибка: Ввод колтичества комнат");
                else if (exit_code == ERROR_READING_SQR_METER_PRICE)
                    puts("\tОшибка: Цена квадратного метра");
                else if (exit_code == ERROR_READING_HOUSE_TYPE)
                    puts("\tОшибка: Ввод типа квартиры");
                else if (exit_code == ERROR_READING_ROOMS_N)
                    puts("\tОшибка: Ввод колтичества комнат");
                else if (exit_code == ERROR_READING_PRIM_FIELDS)
                    puts("\tОшибка: Ввод параметров первичного типа");
                else if (exit_code == ERROR_READING_SEC_FIELDS)
                    puts("\tОшибка: Ввод параметров вторичного типа");
                else if (!exit_code)
                {
                    puts("\tЗапись успешно добавлена");
                    print_houses_table(house_table, house_table_len);
                    import_data_to_key(key_table, house_table, house_table_len);
                }
                break;
            case 9:
                exit_code = input_left_right_limits(&ll, &rl);
                if (!exit_code)
                {
                    exit_code = delete_in_price_range(house_table, ll, rl, &house_table_len);
                    if (!exit_code)
                    {
                        exit_code = print_houses_table(house_table, house_table_len);
                        if (exit_code == ERROR_NO_DATA_IMPORTED)
                            puts("\tОшибка: Нет данных для печатия");
                    }
                    else if (exit_code == ERROR_NO_DATA_IMPORTED)
                        puts("\tОшибка: Нет данных для удаления");
                }
                else if (exit_code == ERROR_INPUT_LL)
                    puts("\tОшибка: Ввод левой границы интервала");
                else if (exit_code == ERROR_INPUT_RL)
                    puts("\tОшибка: Ввод правой границы интервала");
                break;
            case 10:
                exit_code = input_left_right_limits(&ll, &rl);
                if (!exit_code)
                    exit_code = filter(house_table, house_table_len, ll, rl);
                else if (exit_code == ERROR_INPUT_LL)
                    puts("\tОшибка: Ввод левой границы интервала");
                else if (exit_code == ERROR_INPUT_RL)
                    puts("\tОшибка: Ввод правой границы интервала");
                break;
            case 11:
                exit_code = complex_analisys();
            }
        }
    }
    while (choice && !exit_code);
    return exit_code;
}
