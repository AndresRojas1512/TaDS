#include "stack_sa.h"

int stack_sa_read_size(FILE *file, int *stack_size)
{
    if (fscanf(file, "%d", stack_size) != 1)
        return ERROR_READ_UB;
    if (!(*stack_size) || (*stack_size) > STACK_SIZE)
        return ERROR_READ_SIZE_RANGE;
    return EXIT_SUCCESS;
}

void stack_sa_init(stack_static_array_t *stack_sa, int stack_size)
{
    stack_sa->top_A = -1;
    stack_sa->top_B = stack_size;
    stack_sa->stack_size = stack_size;
    stack_sa->cur_size_A = 0;
    stack_sa->cur_size_B = 0;
}

void stack_sa_output(stack_static_array_t *stack_sa)
{
    printf("Top A: %d\n", stack_sa->top_A);
    printf("Top B: %d\n", stack_sa->top_B);
    printf("Stack Size: %d\n", stack_sa->stack_size);
    printf("Cur_size_A: %d\n", stack_sa->cur_size_A);
    printf("Cur_size_B: %d\n", stack_sa->cur_size_B);
    if (stack_sa_output_A(stack_sa))
        printf("Empty Stack A\n");
    if (stack_sa_output_B(stack_sa))
        printf("Empty Stack B\n");
}

int push_A(stack_static_array_t *stack_sa, int x)
{
    if ((stack_sa->top_A + 1 == stack_sa->top_B) || (stack_sa->top_A == stack_sa->stack_size - 1) || (stack_sa->top_B == 0))
        return ERROR_STACK_A_OVERFLOW;
    stack_sa->stack[++stack_sa->top_A] = x;
    stack_sa->cur_size_A += 1;
    return EXIT_SUCCESS;
}

int push_B(stack_static_array_t *stack_sa, int x)
{
    if ((stack_sa->top_A + 1 == stack_sa->top_B) || (stack_sa->top_A == stack_sa->stack_size - 1) || (stack_sa->top_B == 0))
        return ERROR_STACK_B_OVERFLOW;
    stack_sa->stack[--stack_sa->top_B] = x;
    stack_sa->cur_size_B += 1;
    return EXIT_SUCCESS;
}

int pop_A(stack_static_array_t *stack_sa, int *pop_value)
{
    if (stack_sa->top_A == -1)
        return ERROR_STACK_A_UNDERFLOW;
    *pop_value = stack_sa->stack[stack_sa->top_A];
    stack_sa->top_A--;
    stack_sa->cur_size_A -= 1;
    return EXIT_SUCCESS;
}

int pop_B(stack_static_array_t *stack_sa, int *pop_value)
{
    if (stack_sa->top_B == stack_sa->stack_size)
        return ERROR_STACK_B_OVERFLOW;
    *pop_value = stack_sa->stack[stack_sa->top_B];
    stack_sa->top_B++;
    stack_sa->cur_size_B -= 1;
    return EXIT_SUCCESS;
}

int stack_sa_output_A(stack_static_array_t *stack_sa)
{
    printf("Stack A: ");
    if (stack_sa->top_A == -1)
        return ERROR_EMPTY_STACK_A;
    for (int i = 0; i <= stack_sa->top_A; i++)
        printf("%d ", stack_sa->stack[i]);
    printf("\n");
    return EXIT_SUCCESS;
}

int stack_sa_output_B(stack_static_array_t *stack_sa)
{
    printf("Stack B: ");
    if (stack_sa->top_B == stack_sa->stack_size)
        return ERROR_EMPTY_STACK_B;
    for (int i = stack_sa->stack_size - 1; i >= stack_sa->top_B; i--)
        printf("%d ", stack_sa->stack[i]);
    printf("\n");
    return EXIT_SUCCESS;
}
