#ifndef QUEUE_SA
#define QUEUE_SA

#include <stdio.h>
#include <stdlib.h>
#include "request.h"

#define QUEUE_SA_SIZE 100000

#define IS_EMPTY 1
#define IS_NOT_EMPTY 0
#define IS_FULL 1
#define IS_NOT_FULL 0

#define ERROR_QUEUE_SA_FULL 10
#define ERROR_QUEUE_SA_EMPTY 11
#define ERROR_QUEUE_SA_SIZE_INPUT 12
#define ERROR_QUEUE_SA_SIZE_RANGE 13

typedef struct queue_sa_t
{
    request_t requests[QUEUE_SA_SIZE];
    int front;
    int rear;
    int capacity;
    int size;
} queue_sa_t;

void queue_sa_init(queue_sa_t *queue_sa, int capacity);
int queue_sa_isempty(queue_sa_t *queue_sa);
int queue_sa_isfull(queue_sa_t *queue_sa);
int enqueue_sa(queue_sa_t *queue_sa, request_t x);
int dequeue_sa(queue_sa_t *queue_sa, request_t *dequeued_val);
void queue_sa_print_general(queue_sa_t *queue_sa);

int queue_sa_validate_size(int *size);

#endif