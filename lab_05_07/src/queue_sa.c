#include "queue_sa.h"

void queue_sa_init(queue_sa_t *queue_sa, int general_size)
{
    queue_sa->front = -1;
    queue_sa->rear = -1;
    queue_sa->count_passed_requests = 0;
    queue_sa->general_size = general_size;
}

int queue_sa_isempty(queue_sa_t *queue_sa)
{
    if ((queue_sa->front == -1) && (queue_sa->rear == -1))
        return IS_EMPTY;
    return IS_NOT_EMPTY;
}

int queue_sa_isfull(queue_sa_t *queue_sa)
{
    if (((queue_sa->rear + 1) % queue_sa->general_size) == queue_sa->front)
        return IS_FULL;
    return IS_NOT_FULL;
}

int enqueue_sa(queue_sa_t *queue_sa, request_t x)
{
    if (queue_sa_isfull(queue_sa))
        return ERROR_QUEUE_SA_FULL;
    if (queue_sa_isempty(queue_sa))
    {
        queue_sa->front = 0;
        queue_sa->rear = 0;
    }
    else
        queue_sa->rear = (queue_sa->rear + 1) % queue_sa->general_size;
    queue_sa->requests[queue_sa->rear] = x;
    queue_sa->count_passed_requests += 1;
    return EXIT_SUCCESS;
}

int dequeue_sa(queue_sa_t *queue_sa, request_t *dequeued_val)
{
    if (queue_sa_isempty(queue_sa))
        return ERROR_QUEUE_SA_EMPTY;
    if (queue_sa->front == queue_sa->rear)
    {
        *dequeued_val = queue_sa->requests[queue_sa->front];
        queue_sa->front = -1;
        queue_sa->rear = -1;
    }
    else
    {
        *dequeued_val = queue_sa->requests[queue_sa->front];
        queue_sa->front = (queue_sa->front + 1) % queue_sa->general_size;
    }
    return EXIT_SUCCESS;
}

void queue_sa_print_general(queue_sa_t *queue_sa)
{
    printf("Gen Size: %d\n", queue_sa->general_size);
    printf("Passed Requests: %d\n", queue_sa->count_passed_requests);
    printf("Front: %d\n", queue_sa->front);
    printf("Rear: %d\n", queue_sa->rear);
    printf("Queue: \n");
    if (queue_sa_isempty(queue_sa))
        printf("Empty Queue.\n");
    else
    {
        int index = queue_sa->front;
        while (1)
        {
            request_print(&(queue_sa->requests[index]));
            if (index == queue_sa->rear)
                break;
            index = (index + 1) % queue_sa->general_size;
        }
    }
}