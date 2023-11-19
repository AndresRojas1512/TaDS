#include <stdio.h>
#include <stdlib.h>
#include "request.h"
#include "queue_sa.h"
#include "queue_ll.h"
#include "system_func.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;
    queue_sa_t queue_sa;
    request_t request_01 = {.passes = 1, .processing_time = 1.1};
    request_t request_02 = {.passes = 2, .processing_time = 2.2};
    request_t request_03 = {.passes = 3, .processing_time = 3.3};
    request_t request_04 = {.passes = 4, .processing_time = 4.4};
    struct ListNode *front = NULL;
    struct ListNode *rear = NULL;
    request_t dequeued_val;

    // STATIC QUEUE TEST
    // queue_sa_init(&queue_sa, 3);
    // if (enqueue_sa(&queue_sa, request_01))
    //     return EXIT_FAILURE;
    // if (enqueue_sa(&queue_sa, request_02))
    //     return EXIT_FAILURE;
    // if (dequeue_sa(&queue_sa, &dequeued_val))
    //     return EXIT_FAILURE;
    // else
    //     request_print(&dequeued_val);
    // if (enqueue_sa(&queue_sa, request_03))
    //     return EXIT_FAILURE;
    // if (enqueue_sa(&queue_sa, request_04))
    //     return EXIT_FAILURE;
    // queue_sa_print_general(&queue_sa);

    // LL QUEUE TEST
    if (enqueue_ll(&front, &rear, &request_01))
        return EXIT_FAILURE;
    if (enqueue_ll(&front, &rear, &request_02))
        return EXIT_FAILURE;
    if (dequeue_ll(&front, &rear, &dequeued_val))
        return EXIT_FAILURE;
    else
    {
        printf("Dequeued Val: ");
        request_print(&dequeued_val);
    }
    queue_ll_print(front);
    return exit_code;
}