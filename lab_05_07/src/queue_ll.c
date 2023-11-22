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

int enqueue_ll(queue_ll_t *queue_ll, request_t *request, free_addresses_t *free_addresses) // todo: add all memory addresses
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
    free_addresses->addresses[free_addresses->count] = queue_ll->rear;
    free_addresses->count++;
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

int dequeue_ll(queue_ll_t *queue_ll, request_t *dequeued_val, free_addresses_t *free_addresses) // todo : delete free memory array
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
            // for (int j = i; j < free_addresses->count - 1; j++)
            // {
            //     void *temp = free_addresses->addresses[j];
            //     free_addresses->addresses[j] = free_addresses->addresses[j + 1];
            //     free_addresses->addresses[j + 1] = temp;
            // }
        }
    }
    // if (found)
        // free_addresses->count--;
    return found;
}

void free_addresses_count_equal(free_addresses_t *free_addresses, int *count) // todo
{
    return;
}

void free_addresses_print(free_addresses_t *free_addresses)
{
    printf("N: %d\n", free_addresses->count);
    printf("Addresses:\n");
    for (int i = 0; i < free_addresses->count; i++)
        printf("%d: %p\n", i, free_addresses->addresses[i]);
}

int free_addresses_compare(free_addresses_t *free_addresses_enqueue, free_addresses_t *free_addresses_dequeue)
{
    for (int i = 0; i < free_addresses_enqueue->count; i++)
    {
        if (free_addresses_enqueue->addresses[i] != free_addresses_dequeue->addresses[i])
            return 1;
    }
    return 0;
}

void *free_addresses_remove_dup(free_addresses_t *free_addresses, int *free_addresses_single_count)
{
    *free_addresses_single_count = 0;
    void **fa_tmp = calloc(free_addresses->count, sizeof(void *));
    if (!fa_tmp)
        return NULL;
    
    int count = 0;
    for (int i = 0; i < free_addresses->count; i++)
    {
        int found = 0;
        for (int j = 0; j < count; j++)
        {
            if (free_addresses->addresses[i] == fa_tmp[j])
            {
                found = 1;
                break;
            }
        }
        if (!found)
            fa_tmp[count++] = free_addresses->addresses[i];
    }
    *free_addresses_single_count = count;
    void **tmp = realloc(fa_tmp, count * sizeof(void *));
    if (!tmp)
        return NULL;
    fa_tmp = tmp;
    return fa_tmp;
}

void queue_ll_free(queue_ll_t *queue_ll)
{
    if (!queue_ll->front)
        return;
    struct ListNode *tmp;
    while (queue_ll->front)
    {
        tmp = queue_ll->front;
        queue_ll->front = queue_ll->front->next;
        node_free(tmp);
    }
}