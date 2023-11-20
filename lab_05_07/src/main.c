#include <stdio.h>
#include <stdlib.h>
#include "request.h"
#include "queue_sa.h"
#include "queue_ll.h"
#include "system_func.h"
#include "complexity_analysis.h"
#include "ui.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;

    queue_sa_t queue_sa; // queue_sa
    queue_ll_t queue_ll; // queue_ll
    free_addresses_t free_addresses;

    int queue_sa_size;

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
            case 1: // QUEUE_SA_SYSTEM
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
            case 2: // QUEUE_LL_SYSTEM
                queue_ll_init(&queue_ll);
                free_addresses_init(&free_addresses);
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
                
                queue_ll_system(&queue_ll, &free_addresses, &time_in_range, &time_out_range, request_passes);
                break;
            case 3:
                exit_code = complexity_analysis();
                break;
            }
        }
    }
    while (choice != 0);

    return exit_code;
}