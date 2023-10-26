#ifndef MATRIX_H
#define MATRIX_H

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
    int rows; // check if multiplication is possible
    int elems_amount; // size of both vectors
} vector_mtd_t;

#endif