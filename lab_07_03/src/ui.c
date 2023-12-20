#include "ui.h"

void menu(void)
{
    printf("\n");
    puts("1. Инициализации деревьев и таблиц.");
    puts("2. Префиксный обход (дерево).");
    puts("3. Инфиксный обход (дерево).");
    puts("4. Постфиксный обход (дерево).");
    puts("5. Добавление слова.");
    puts("6. Удаление слова.");
    puts("7. Поиск слова.");
    puts("8. Удаление слов с заданной буквой.");
    puts("9. ");
    puts("10. ");
    puts("11. ");
    puts("0. Выход\n");
}

int input_choice(int *choice)
{
    puts("--------------------------------------");
    printf("Введите операцию: ");
    int result = scanf("%d", choice);
    clean_buffer();
    if (!result)
        return ERROR_CHOICE_READ_UB;
    if (*choice > 11 || *choice < 0)
        return ERROR_CHOICE_READ_RANGE;
    return EXIT_SUCCESS;
}

void clean_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int input_iter_threshold(int *iter_threshold)
{
    if (scanf("%d", iter_threshold) != 1)
        return ERROR_SCANF;
    if (*iter_threshold <= 0 || *iter_threshold > MAX_ITER_THRESHOLD)
        return ERROR_INPUT_RANGE;
    return EXIT_SUCCESS;
}