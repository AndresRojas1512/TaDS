#include "ui.h"

void menu(void)
{
    puts("1. Выбор файла");
    puts("2. Инициализировать таьлицы");
    puts("3. Вывод ипортированной таблицы");
    puts("4. Сортировка основной таблицы");
    puts("5. Вывод таблицы ключей");
    puts("6. Сортировка таблицы ключей");
    puts("7. Вывод основной таблицы таблицей ключей");
    puts("8. Добавление данных");
    puts("9. Удаление квартир (по цене квадрвтного метра)");
    puts("10. Найти вторичные 2-х комнатное желье в ценовом диапазоне без животных");
    puts("11. Исследование эффективности");
    puts("0. Выход");
}

int input_choice(int *choice)
{
    int exit_code = EXIT_SUCCESS;
    puts("--------------------------------------");
    if (scanf("%d", choice) != 1)
    {
        exit_code = EXIT_FAILURE;
    }
    clear_buffer();
    if (*choice > 11 || *choice < 0)
        exit_code = EXIT_FAILURE;
    return exit_code;
}