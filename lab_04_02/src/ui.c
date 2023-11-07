#include "ui.h"

void menu(void)
{
    printf("\n");
    puts("1. Инициализация размера массива двух стеков (используется для тестирования переполнения).");
    puts("2. Добавление в стек А.");
    puts("3. Добавление в стек В.");
    puts("4. Удалениe из стека А.");
    puts("5. Удаление из стека В.");
    puts("6. Добавление в стек (формат односвязного списка)");
    puts("7. Удаление из стека (формат односвязного списка).");
    puts("8. Печать свободных облостей.");
    puts("9. Анализ эффективности.");
    puts("0. Выход.");
}

int input_choice(int *choice)
{
    puts("--------------------------------------");
    printf("Enter the operation: ");
    int result = scanf("%d", choice);
    clean_buffer();
    if (!result)
        return ERROR_CHOICE_READ_UB;
    if (*choice > 9 || *choice < 0)
        return ERROR_CHOICE_READ_RANGE;
    return EXIT_SUCCESS;
}

void clean_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}