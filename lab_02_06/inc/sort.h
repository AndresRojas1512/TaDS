#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types_macros.h"
#include "helper.h"

// CASE 4: Sort table (Table / Keys)
void mysort(void *pbeg, int nitems, size_t elem_size, comparator_t comparator);
int house_price_comparator(const void *lval, const void *rval);
int key_price_comparator(const void *lval, const void *rval);
void swap(void *lval, void *rval, size_t elem_size);


#endif