#include "ui.h"

void menu(void)
{
    printf("\n");
    puts("1. Инициализировать дерево.");
    puts("2. Префиксный обход.");
    puts("3. Инфиксный обход.");
    puts("4. Постфиксный обход.");
    puts("5. Добавление узла");
    puts("6. Удаление узла");
    puts("7. Поиск узла");
    puts("8. Удаление слов, начинающие с заданной буквой.");
    puts("9. Анализ эффективности.");
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
    if (*choice > OPERARIONS_N || *choice < 0)
        return ERROR_CHOICE_READ_RANGE;
    return EXIT_SUCCESS;
}

void clean_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}