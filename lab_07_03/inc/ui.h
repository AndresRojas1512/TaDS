#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_ITER_THRESHOLD 20

#define ERROR_CHOICE_READ_UB 50
#define ERROR_CHOICE_READ_RANGE 51
#define ERROR_SCANF 52
#define ERROR_INPUT_RANGE 53

void menu(void);
void clean_buffer(void);
int input_choice(int *choice);
int input_iter_threshold(int *iter_threshold);

#endif