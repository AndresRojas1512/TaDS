#include <stdio.h>
#include <stdlib.h>
#include "request.h"
#include "queue_sa.h"
#include "queue_ll.h"
#include "system_func.h"
#include "ui.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;

    queue_sa_t queue_sa; // queue_sa
    int queue_sa_size;
    struct ListNode *front = NULL; // queue_ll
    struct ListNode *rear = NULL; // queue_ll

    system_time_t time_in_range;
    system_time_t time_out_range;
    int request_passes;

    int choice;

    do
    {
        menu();
        if (input_choice(&choice))
            puts("\nОшибка: Введите опцию (0 - 4).\n");
        else
        {
            switch (choice)
            {
            case 1:
                printf("queue size: ");
                exit_code = queue_sa_validate_size(&queue_sa_size);
                if (exit_code)
                    return exit_code;
                printf("time in queue: ");
                exit_code = time_range_validate(&time_in_range, SYSTEM_TIME_LLIM, SYSTEM_TIME_RLIM);
                if (exit_code)
                    return exit_code;
                
                printf("time out su: ");
                exit_code = time_range_validate(&time_out_range, SYSTEM_TIME_LLIM, SYSTEM_TIME_RLIM);
                if (exit_code)
                    return exit_code;
                
                printf("request passes: ");
                exit_code = request_validate_passes(&request_passes);
                if (exit_code)
                    return exit_code;
                
                queue_sa_init(&queue_sa, queue_sa_size);
                queue_sa_system(&queue_sa, &time_in_range, &time_out_range, request_passes);
                break;
            case 2:
                puts("Two");
                break;
            
            case 3:
                puts("Three");
                break;
            }
        }
    }
    while (choice != 0);

    return exit_code;
}