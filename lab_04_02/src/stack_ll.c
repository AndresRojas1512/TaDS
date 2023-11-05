#include "stack_ll.h"

struct ListNode *node_create(int x)
{
    struct ListNode *Node = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!Node)
        return NULL;
    Node->data = x;
    Node->next = NULL;
    return Node;
}

int push(struct ListNode **top, int x)
{
    struct ListNode *Node = node_create(x);
    if (!Node)
        return ERROR_NODE_CREATION;
    Node->next = (*top);
    (*top) = Node;
    return EXIT_SUCCESS;
}

void pop(struct ListNode **top)
{
    if (!(*top))
        return;
    struct ListNode *tmp = *top;
    (*top) = (*top)->next;
    free(tmp);
}

void stack_ll_print(struct ListNode *top)
{
    if (!top)
        return;
    stack_ll_print(top->next);
    printf("%d ", top->data);
}