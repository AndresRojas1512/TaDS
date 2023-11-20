#include "queue_ll.h"

void queue_ll_init(queue_ll_t *queue_ll)
{
    queue_ll->front = NULL;
    queue_ll->rear = NULL;
    queue_ll->len = 0;
}

void free_addresses_init(free_addresses_t *free_addresses)
{
    free_addresses->count = 0;
}

int enqueue_ll(queue_ll_t *queue_ll, request_t *request) // done
{
    if (!queue_ll || !request)
        return EXIT_FAILURE;

    struct ListNode *tmp = node_create(*request);
    if (!tmp)
        return ERROR_NODE_ALLOCATION;

    if ((queue_ll->front) == NULL && (queue_ll->rear) == NULL)
    {
        (queue_ll->front) = (queue_ll->rear) = tmp;
        queue_ll->len += 1;
    }
    else
    {
        queue_ll->rear->next = tmp;
        queue_ll->rear = tmp;
        queue_ll->len += 1;
    }
    return EXIT_SUCCESS;
}

int queue_ll_isempty(queue_ll_t *queue_ll) // done
{
    if (!queue_ll) // considered empty if queue_ll is null
        return 1;
    if (!queue_ll->front && !queue_ll->rear)
        return 1;
    return 0;
}

int dequeue_ll(queue_ll_t *queue_ll, request_t *dequeued_val, free_addresses_t *free_addresses) // todo : add freed memory to array
{
    if (!queue_ll)
        return EXIT_FAILURE;
    struct ListNode *tmp = queue_ll->front;
    if (queue_ll->front == NULL)
        return ERROR_EMPTY_QUEUE;
    if (queue_ll->front == queue_ll->rear)
    {
        *dequeued_val = queue_ll->front->request;
        queue_ll->front = NULL;
        queue_ll->rear = NULL;
        queue_ll->len -= 1;
    }
    else
    {
        *dequeued_val = queue_ll->front->request;
        queue_ll->front = queue_ll->front->next;
        queue_ll->len -= 1;
    }
    free_addresses->addresses[free_addresses->count] = tmp;
    free_addresses->count++;
    node_free(tmp);
    return EXIT_SUCCESS;
}

struct ListNode *node_create(request_t request) // done
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

int queue_ll_print(queue_ll_t *queue_ll) // done
{
    printf("Queue Status:\n");
    if (queue_ll->front == NULL)
        return ERROR_EMPTY_QUEUE;
    struct ListNode *cur = queue_ll->front;
    while (cur)
    {
        request_print(&(cur->request));
        cur = cur->next;
    }
    return EXIT_SUCCESS;
}

int memory_check(queue_ll_t *queue_ll, free_addresses_t *free_addresses) // done
{
    void *mem_rear = queue_ll->rear;
    int found = 0;
    for (int i = 0; i < free_addresses->count; i++)
    {
        if (mem_rear == free_addresses->addresses[i])
        {
            found = 1;
            for (int j = i; j < free_addresses->count - 1; j++)
            {
                void *temp = free_addresses->addresses[j];
                free_addresses->addresses[j] = free_addresses->addresses[j + 1];
                free_addresses->addresses[j + 1] = temp;
            }
        }
    }
    if (found)
        free_addresses->count--;
    return found;
}

void free_addresses_count_equal(free_addresses_t *free_addresses, int *count)
{
    return;
}
