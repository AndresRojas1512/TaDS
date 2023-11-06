#ifndef STACK_LL
#define STACK_LL

#include <stdio.h>
#include <stdlib.h>

#define MAX_FREED_ADDRESSES 100000

#define ERROR_NODE_CREATION 20
#define ERROR_STACK_UNDERFLOW 21
#define ERROR_EMPTY_ADDRESSES_ARRAY 22
#define ERROR_EMPTY_STACK_LL 23

struct ListNode
{
    int data;
    struct ListNode *next;
};

typedef struct free_addresses_t
{
    void *addresses[MAX_FREED_ADDRESSES];
    int count;
} free_addresses_t;

struct ListNode *node_create(int x);
int push(struct ListNode **top, int x);
int pop(struct ListNode **top, int *poped_value, free_addresses_t *free_addresses);
void stack_ll_print(struct ListNode *top);
void free_addresses_init(free_addresses_t *free_addresses);
void free_addresses_add(free_addresses_t *free_addresses, void *address);
int free_addresses_print(free_addresses_t *free_addresses);

#endif