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
    int stack_size;
    FILE *file = stdin;
    int choice;
    int x; // the push value
    int pop_value;
    struct ListNode *top = NULL;
    do
    {
        menu();
        if (input_choice(&choice))
            puts("\nError: Invalid operation\n");
        else
        {
            switch (choice)
            {
            case 1: // Init Stack
                printf("\nEnter the Stack Size: ");
                exit_code = stack_sa_read_size(file, &stack_size);
                if (exit_code == ERROR_READ_UB)
                    printf("\tError: Input Error\n");
                else if (exit_code == ERROR_READ_SIZE_RANGE)
                    printf("\tError: Invalid Size Value\n");
                else
                    stack_sa_init(&stack_sa, stack_size);
                    printf("\tStack Initialized Succesfuly\n");
                break;
            case 2: // Push A
                printf("Enter the Value to Push to A: ");
                if (fscanf(file, "%d", &x) != 1)
                    return ERROR_READ_PUSH_VALUE;
                exit_code = push_A(&stack_sa, x);
                if (exit_code == ERROR_STACK_A_OVERFLOW)
                    printf("\tError: Stack A Overflow\n");
                if (!exit_code)
                    printf("\tPush A Succesful!\n");
                break;
            case 3: // Push B
                printf("Enter the Value to Push to B: ");
                if (fscanf(file, "%d", &x) != 1)
                    return ERROR_READ_PUSH_VALUE;
                exit_code = push_B(&stack_sa, x);
                if (exit_code == ERROR_STACK_B_OVERFLOW)
                    printf("\tError: Stack B Overflow\n");
                if (!exit_code)
                    printf("\tPush B Succesful!\n");
                break;
            case 4: // Pop Stack A
                exit_code = pop_A(&stack_sa, &pop_value);
                if (exit_code == ERROR_STACK_A_UNDERFLOW)
                    printf("Stack A Underflow\n");
                if (!exit_code)
                    printf("\tPop Succesful: %d\n", pop_value);
                break;
            case 5: // Pop Stack B
                exit_code = pop_B(&stack_sa, &pop_value);
                if (exit_code == ERROR_STACK_B_UNDERFLOW)
                    printf("Stack B Underflow\n");
                if (!exit_code)
                    printf("\tPop Succesful: %d\n", pop_value);
                break;
            case 6: // Output
                stack_sa_output(&stack_sa);
                break;
            case 7: // Push Linked List
                printf("Enter the Value to Push: ");
                if (fscanf(file, "%d", &x) != 1)
                    return ERROR_READ_PUSH_VALUE;
                exit_code = push(&top, x);
                stack_ll_print(top);
                printf("\n");
                break;
            case 8: // Pop Linked List
                pop(&top);
                stack_ll_print(top);
                printf("\n");
                break;
            case 9:
                complexity_analysis();
            }
        }
    }
    while (choice && choice != 9);
}