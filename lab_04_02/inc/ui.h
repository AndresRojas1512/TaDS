#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_CHOICE_READ_UB 10
#define ERROR_CHOICE_READ_RANGE 11

void menu(void);
void clean_buffer(void);
int input_choice(int *choice);

#endif