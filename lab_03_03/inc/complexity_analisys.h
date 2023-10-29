#ifndef COMPLEXITY_ANALISYS_H
#define COMPLEXITY_ANALISYS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "types_macros.h"
#include "matrix_vector_t.h"
#include "matrix_init.h"
#include "matrix_mem.h"
#include "matrix_io.h"
#include "vector_init.h"
#include "multiplication.h"
#include "user_interface.h"

#define MATRIX_SIZES 5
#define PERCENTAGES_N 6

int complexity_analisys(void);
unsigned long long microseconds_now(void);
int read_data(char *filename, matrix_std_t *matrix_std, matrix_mtd_t *matrix_mtd, vector_mtd_t *vector_mtd, matrix_std_t *vector_std);

#endif