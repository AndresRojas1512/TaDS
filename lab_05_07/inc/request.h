#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <stdlib.h>

#define REQUEST_PASSES_MAX_TIMES 15

#define ERROR_REQUEST_PASSES_INPUT 40
#define ERROR_REQUEST_PASSES_RANGE 41

typedef struct request_t
{
    int passes;
    double processing_time;
} request_t;

void request_init(request_t *request); // debug
void request_print(request_t *request);
int request_validate_passes(int *request_passes);

#endif