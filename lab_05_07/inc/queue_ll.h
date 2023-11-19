#ifndef QUEUE_LL
#define QUEUE_LL

#include <stdio.h>
#include <stdlib.h>
#include "request.h"

#define ERROR_NODE_ALLOCATION 30
#define ERROR_EMPTY_QUEUE 31

struct ListNode
{
    request_t request;
    struct ListNode *next;
};

int enqueue_ll(struct ListNode **front, struct ListNode **rear, request_t *request);
int dequeue_ll(struct ListNode **front, struct ListNode **rear, request_t *dequeued_val);
struct ListNode *node_create(request_t request);
void node_free(struct ListNode *node);
int queue_ll_print(struct ListNode *front);
#endif