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

int pop(struct ListNode **top, int *poped_value, free_addresses_t *free_addresses)
{
    if (!(*top))
        return ERROR_STACK_UNDERFLOW;
    *poped_value = (*top)->data;
    struct ListNode *tmp = *top;
    (*top) = (*top)->next;
    free_addresses_add(free_addresses, tmp);
    free(tmp);
}

void stack_ll_print(struct ListNode *top)
{
    if (!top)
        return;
    stack_ll_print(top->next);
    printf("%d-(%p) ", top->data, (void *)top);
}


// ADDRESS OPERATIONS
void free_addresses_init(free_addresses_t *free_addresses)
{
    free_addresses->count = 0;
}

void free_addresses_add(free_addresses_t *free_addresses, void *address)
{
    free_addresses->addresses[free_addresses->count++] = address;
}

int free_addresses_print(free_addresses_t *free_addresses)
{
    printf("Освобожденные адреса: ");
    if (!free_addresses->count)
        return ERROR_EMPTY_ADDRESSES_ARRAY;
    for (int i = 0; i < free_addresses->count; i++)
        printf("%p ", free_addresses->addresses[i]);
    printf("\n");
    return EXIT_SUCCESS;
}