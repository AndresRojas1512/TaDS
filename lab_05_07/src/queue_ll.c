#include "queue_ll.h"

int enqueue_ll(struct ListNode **front, struct ListNode **rear, request_t *request)
{
    struct ListNode *tmp = node_create(*request);
    if (!tmp)
        return ERROR_NODE_ALLOCATION;
    if ((*front) == NULL && (*rear) == NULL)
        (*front) = (*rear) = tmp;
    else
    {
        (*rear)->next = tmp;
        (*rear) = tmp;
    }
    return EXIT_SUCCESS;
}

int dequeue_ll(struct ListNode **front, struct ListNode **rear, request_t *dequeued_val)
{
    struct ListNode *tmp = *front;
    if (*front == NULL)
        return ERROR_EMPTY_QUEUE;
    if (*front == *rear)
    {
        *dequeued_val = (*front)->request;
        *front = NULL;
        *rear = NULL;
    }
    else
    {
        *dequeued_val = (*front)->request;
        *front = (*front)->next;
    }
    node_free(tmp);
    return EXIT_SUCCESS;
}

struct ListNode *node_create(request_t request)
{
    struct ListNode *tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!tmp)
        return NULL;
    tmp->request = request;
    tmp->next = NULL;
    return tmp;
}

void node_free(struct ListNode *node)
{
    free(node);
}

int queue_ll_print(struct ListNode *front)
{
    printf("Queue Status:\n");
    if (front == NULL)
        return ERROR_EMPTY_QUEUE;
    struct ListNode *cur = front;
    while (cur)
    {
        request_print(&(cur->request));
        cur = cur->next;
    }
    return EXIT_SUCCESS;
}

