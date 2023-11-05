#ifndef STACK_SA
#define STACK_SA

#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 10000

#define ERROR_READ_SIZE_RANGE 100
#define ERROR_READ_UB 101
#define ERROR_STACK_A_OVERFLOW 102
#define ERROR_STACK_B_OVERFLOW 103
#define ERROR_STACK_A_UNDERFLOW 104
#define ERROR_STACK_B_UNDERFLOW 105
#define ERROR_EMPTY_STACK_A 106
#define ERROR_EMPTY_STACK_B 107

typedef struct stack_static_array_t
{
    int stack[STACK_SIZE];
    int top_A;
    int top_B;
    int stack_size;
    int cur_size_A;
    int cur_size_B;
} stack_static_array_t;

// Data Input
int stack_sa_read_size(FILE *file, int *stack_size);
// Default Values Init
void stack_sa_init(stack_static_array_t *stack_sa, int stack_size);
// Printers
void stack_sa_output(stack_static_array_t *stack_sa); // General
int stack_sa_output_A(stack_static_array_t *stack_sa);
int stack_sa_output_B(stack_static_array_t *stack_sa);

// Push Operation
int push_A(stack_static_array_t *stack_sa, int x);
int push_B(stack_static_array_t *stack_sa, int x);

// Pop Operation
int pop_A(stack_static_array_t *stack_sa, int *pop_value);
int pop_B(stack_static_array_t *stack_sa, int *pop_value);

#endif