#include "ui.h"

void menu(void)
{
    printf("\n");
    puts("1. Init BST");
    puts("2. Preorder Print");
    puts("3. Inorder Print");
    puts("4. Postorder Print");
    puts("5. Insert node");
    puts("6. Delete node");
    puts("7. Search node");
    puts("8. Delete Words with letter");
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
    if (*choice > 8 || *choice < 0)
        return ERROR_CHOICE_READ_RANGE;
    return EXIT_SUCCESS;
}

void clean_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}