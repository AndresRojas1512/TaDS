#include "sort.h"

// CASE 4: Sort table (Table / Keys)
void mysort(void *pbeg, int nitems, size_t elem_size, comparator_t comparator)
{
    char *pend = (char *)pbeg + (nitems * elem_size);
    char *pstart = (char *)pbeg;
    if (pstart == pend)
        return;
    char *pend_minus_one = (char *)pend - elem_size;
    int swapped = 1;
    int pass = 1;
    while (swapped)
    {
        swapped = 0;
        if (pass % 2 == 1)
        {
            for (char *pcur = pstart; pcur < pend_minus_one; pcur += elem_size)
            {
                if (comparator(pcur, pcur + elem_size) > 0)
                {
                    swap(pcur, pcur + elem_size, elem_size);
                    swapped = 1;
                }
            }
            pend_minus_one -= elem_size;
        }
        else
        {
            for (char *pcur = pend_minus_one; pcur > pstart; pcur -= elem_size)
            {
                if (comparator(pcur - elem_size, pcur) > 0)
                {
                    swap(pcur - elem_size, pcur, elem_size);
                    swapped = 1;
                }
            }
            pstart += elem_size;
        }
        pass++;
    }
}

int house_price_comparator(const void *lval, const void *rval)
{
    const house_type *ptr_lval = (const house_type *)lval;
    const house_type *ptr_rval = (const house_type *)rval;
    if (ptr_lval->sqr_meter_price < ptr_rval->sqr_meter_price)
        return -1;
    if (ptr_lval->sqr_meter_price > ptr_rval->sqr_meter_price)
        return 1;
    return 0;
}

int key_price_comparator(const void *lval, const void *rval)
{
    const key_type *ptr_lval = (const key_type *)lval;
    const key_type *ptr_rval = (const key_type *)rval;
    if (ptr_lval->sqr_meter_price < ptr_rval->sqr_meter_price)
        return -1;
    if (ptr_lval->sqr_meter_price > ptr_rval->sqr_meter_price)
        return 1;
    return 0;
}

void swap(void *lval, void *rval, size_t elem_size)
{
    char tmp;
    char *ptr_lval = lval;
    char *ptr_rval = rval;
    for (size_t i = 0; i < elem_size; i++, ptr_lval++, ptr_rval++)
    {
        tmp = *ptr_lval;
        *ptr_lval = *ptr_rval;
        *ptr_rval = tmp;
    }
}

