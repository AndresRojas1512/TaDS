#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct request_t
{
    int passes;
    double processing_time;
} request_t;


void request_init(request_t *request); // debug
void request_print(request_t *request);

#endif