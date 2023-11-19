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