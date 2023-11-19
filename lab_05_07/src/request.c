#include "request.h"

void request_init(request_t *request)
{
    request->passes = 0;
    request->processing_time = 1;
}

void request_print(request_t *request)
{
    printf("Request: { passes: %d, processing_time: %f }\n", request->passes, request->processing_time);
}

int request_validate_passes(int *request_passes)
{
    if (scanf("%d", request_passes) != 1)
        return ERROR_REQUEST_PASSES_INPUT;
    if (*request_passes <= 0 || *request_passes > REQUEST_PASSES_MAX_TIMES)
        return ERROR_REQUEST_PASSES_RANGE;
    return EXIT_SUCCESS;
}