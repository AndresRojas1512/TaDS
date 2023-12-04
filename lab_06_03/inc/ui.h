#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>

#define OPERARIONS_N 9

#define ERROR_CHOICE_READ_UB 30
#define ERROR_CHOICE_READ_RANGE 31

void menu(void);
void clean_buffer(void);
int input_choice(int *choice);

#endif