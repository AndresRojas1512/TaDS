#include "ui.h"

void menu(void)
{
    puts("1. Init Stack");
    puts("2. Push Stack A");
    puts("3. Push Stack B");
    puts("4. Pop Stack A");
    puts("5. Pop Stack B");
    puts("6. Output Struct");
    puts("7. Push Linked List Stack");
    puts("8. Pop Linked List Stack");
    puts("9. Complexity Analysis");
    puts("0. Выход");
}

int input_choice(int *choice)
{
    puts("--------------------------------------");
    printf("Enter the operation: ");
    if (scanf("%d", choice) != 1)
        return ERROR_CHOICE_READ_UB;
    clean_buffer();
    if (*choice > 9 || *choice < 0)
        return ERROR_CHOICE_READ_RANGE;
    return EXIT_SUCCESS;
}

void clean_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}