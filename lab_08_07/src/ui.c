#include "ui.h"

void menu(void)
{
    printf("\n");
    puts("1. Ввод графа.");
    puts("2. Для каждой пары вершин найти длину кратчайшего пути между ними.");
    puts("3. Проверка связности графа.");
    // puts("4. Считать количество остовных деревев в графе.");
    // puts("5. Получить остовное дерево графа.");
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
    if (*choice > 3 || *choice < 0)
        return ERROR_CHOICE_READ_RANGE;
    return EXIT_SUCCESS;
}

void clean_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
