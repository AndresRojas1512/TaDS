#include <stdio.h>
#include <stdlib.h>
#include "stack_ll.h"
#include "stack_sa.h"
#include "exit_codes.h"
#include "ui.h"
#include "complexity_analysis.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;
    stack_static_array_t stack_sa;
    free_addresses_t free_addresses;
    int stack_size;
    FILE *file = stdin;
    int choice;
    double x; // the push value
    double poped_value;
    struct ListNode *top = NULL;
    stack_sa_init(&stack_sa, STACK_SIZE);
    do
    {
        menu();
        if (input_choice(&choice))
            puts("\nОшибка: Введите опцию (0 - 9).\n");
        else
        {
            switch (choice)
            {
            case 1: // Init Stack
                exit_code = EXIT_SUCCESS;
                printf("\nВведите размер стека: ");
                exit_code = stack_sa_read_size(file, &stack_size);
                if (exit_code == ERROR_READ_UB)
                    printf("\tОшибка: Ввод.\n");
                else if (exit_code == ERROR_READ_SIZE_RANGE)
                    printf("\tОшибка: Невалидное значение.\n");
                else
                    stack_sa_init(&stack_sa, stack_size);
                    printf("\tСтек инициализирован успешно.\n");
                break;
            case 2: // Push A
                exit_code = EXIT_SUCCESS;
                printf("Введите значение, добавляемого элемента в стек A: ");
                if (fscanf(file, "%lf", &x) != 1)
                {
                    exit_code = ERROR_READ_PUSH_VALUE;
                    printf("\tОшибка: Невалидное значение.\n");
                }
                if (!exit_code)
                {
                    exit_code = push_A(&stack_sa, x);
                    if (exit_code == ERROR_STACK_A_OVERFLOW)
                        printf("\tОшибка: Переполнение стека A.\n");
                    if (!exit_code)
                        printf("\tУспешно: Добавлен элемент в стек А.\n");
                    printf("Текущее состояние стека:\n");
                    stack_sa_output(&stack_sa);
                }
                break;
            case 3: // Push B
                exit_code = EXIT_SUCCESS;
                printf("Введите значение, добавляемого элемента в стек B: ");
                if (fscanf(file, "%lf", &x) != 1)
                {
                    exit_code = ERROR_READ_PUSH_VALUE;
                    printf("\tОшибка: Невалидное значение.\n");
                }
                if (!exit_code)
                {
                    exit_code = push_B(&stack_sa, x);
                    if (exit_code == ERROR_STACK_B_OVERFLOW)
                        printf("\tОшибка: Переполнение стека B.\n");
                    if (!exit_code)
                        printf("\tУспешно: Добавлен элемент в стек B.\n");
                    printf("Текущее состояние стека:\n");
                    stack_sa_output(&stack_sa);
                }
                break;
            case 4: // Pop Stack A
                exit_code = EXIT_SUCCESS;
                exit_code = pop_A(&stack_sa, &poped_value);
                if (exit_code == ERROR_STACK_A_UNDERFLOW)
                    printf("\tВнимание: Нет элементов для удаления (Стек пустой).\n");
                if (!exit_code)
                    printf("\tУспешно, удаленный элемент: %f\n", poped_value);
                printf("Текущее состояние стека:\n");
                    stack_sa_output(&stack_sa);
                break;
            case 5: // Pop Stack B
                exit_code = EXIT_SUCCESS;
                exit_code = pop_B(&stack_sa, &poped_value);
                if (exit_code == ERROR_STACK_B_UNDERFLOW)
                    printf("\tВнимание: Нет элементов для удаления (Стек пустой).\n");
                if (!exit_code)
                    printf("\tУспешно, удаленный элемент: %f\n", poped_value);
                printf("Текущее состояние стека:\n");
                    stack_sa_output(&stack_sa);
                break;
            case 6: // Push Linked List
                exit_code = EXIT_SUCCESS;
                printf("Введите значение, добавляемого элемента в стек: ");
                if (fscanf(file, "%lf", &x) != 1)
                {
                    exit_code = ERROR_READ_PUSH_VALUE;
                    printf("\tОшибка: Невалидное значение.\n");
                }
                if (!exit_code)
                {
                    exit_code = push(&top, x);
                    if (!exit_code)
                    {
                        printf("\tСтек: ");
                        stack_ll_print(top);
                        printf("\n");
                    }
                }
                break;
            case 7: // Pop Linked List
                exit_code = EXIT_SUCCESS;
                exit_code = pop(&top, &poped_value, &free_addresses);
                if (!exit_code)
                {
                    printf("\tСтек: ");
                    stack_ll_print(top);
                    printf("\n");
                    printf("\tУспешно, удаленный элемент: %f\n", poped_value);
                }
                else if (exit_code == ERROR_STACK_UNDERFLOW)
                    printf("\tВнимание: Нет элементов для удаления (Стек пустой).\n");
                break;
            case 8: // Output Freed Addresses
                exit_code = EXIT_SUCCESS;
                exit_code = free_addresses_print(&free_addresses);
                if (exit_code == ERROR_EMPTY_ADDRESSES_ARRAY)
                    printf("\tПока нет адрессов, удаленных элементов.\n");
                break;
            case 9:
                exit_code = EXIT_SUCCESS;
                complexity_analysis();
                break;
            }
        }
    }
    while (choice != 0 && choice != 9);
    return EXIT_SUCCESS;
}