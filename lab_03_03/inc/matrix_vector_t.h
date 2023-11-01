#ifndef MATRIX_VECTOR_T_H
#define MATRIX_VECTOR_T_H

#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_std_t
{
    int **matrix;
    int rows;
    int cols;
} matrix_std_t;

typedef struct matrix_mtd_t
{
    int *A;
    int *JA;
    int *IA;
    int A_len;
    int JA_len;
    int IA_len;
    int rows;
    int cols;
} matrix_mtd_t;

typedef struct vector_mtd_t
{
    int *A;
    int *VA;
    int rows;
    int elems_amount;
} vector_mtd_t;

#endif