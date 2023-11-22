#ifndef QUEUE_LL
#define QUEUE_LL

#include <stdio.h>
#include <stdlib.h>
#include "request.h"

#define MAX_FREED_ADDRESSES 100000

#define ERROR_NODE_ALLOCATION 30
#define ERROR_EMPTY_QUEUE 31

struct ListNode
{
    request_t request;
    struct ListNode *next;
};

typedef struct queue_ll_t
{
    struct ListNode *front;
    struct ListNode *rear;
    int len;
} queue_ll_t;

typedef struct free_addresses_t
{
    void *addresses[MAX_FREED_ADDRESSES];
    int count;
} free_addresses_t;

void queue_ll_init(queue_ll_t *queue_ll);
void free_addresses_init(free_addresses_t *free_addresses);
int enqueue_ll(queue_ll_t *queue_ll, request_t *request, free_addresses_t *free_addresses);
int queue_ll_isempty(queue_ll_t *queue_ll);
int dequeue_ll(queue_ll_t *queue_ll, request_t *dequeued_val, free_addresses_t *free_addresses);
struct ListNode *node_create(request_t request);
void node_free(struct ListNode *node);
int queue_ll_print(queue_ll_t *queue_ll);
int memory_check(queue_ll_t *queue_ll, free_addresses_t *free_addresses);
void free_addresses_print(free_addresses_t *free_addresses);
int free_addresses_compare(free_addresses_t *free_addresses_enqueue, free_addresses_t *free_addresses_dequeue);
void *free_addresses_remove_dup(free_addresses_t *free_addresses, int *free_addresses_single_count);
void queue_ll_free(queue_ll_t *queue_ll);

#endif