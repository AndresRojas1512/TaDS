#ifndef STACK_LL
#define STACK_LL

#include <stdio.h>
#include <stdlib.h>

#define ERROR_NODE_CREATION 20

struct ListNode
{
    int data;
    struct ListNode *next;
};

struct ListNode *node_create(int x);
int push(struct ListNode **top, int x);
void stack_ll_print(struct ListNode *top);
void pop(struct ListNode **top);

#endif