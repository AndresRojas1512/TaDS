#include "queue_sa.h"

void queue_sa_init(queue_sa_t *queue_sa, int capacity)
{
    queue_sa->front = -1;
    queue_sa->rear = -1;
    queue_sa->size = 0;
    queue_sa->capacity = capacity;
}

int queue_sa_isempty(queue_sa_t *queue_sa)
{
    if ((queue_sa->front == -1) && (queue_sa->rear == -1))
        return IS_EMPTY;
    return IS_NOT_EMPTY;
}

int queue_sa_isfull(queue_sa_t *queue_sa)
{
    if (((queue_sa->rear + 1) % queue_sa->capacity) == queue_sa->front)
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
        queue_sa->rear = (queue_sa->rear + 1) % queue_sa->capacity;
    queue_sa->requests[queue_sa->rear] = x;
    queue_sa->size += 1;
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
        queue_sa->front = (queue_sa->front + 1) % queue_sa->capacity;
    }
    queue_sa->size -= 1;
    return EXIT_SUCCESS;
}

void queue_sa_print_general(queue_sa_t *queue_sa)
{
    printf("Capacity: %d\n", queue_sa->capacity);
    printf("Passed Requests: %d\n", queue_sa->size);
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
            index = (index + 1) % queue_sa->capacity;
        }
    }
}

int queue_sa_validate_size(int *size)
{
    if (scanf("%d", size) != 1)
        return ERROR_QUEUE_SA_SIZE_INPUT;
    if (*size <= 0 || *size > QUEUE_SA_SIZE)
        return ERROR_QUEUE_SA_SIZE_RANGE;
    return EXIT_SUCCESS;
}
