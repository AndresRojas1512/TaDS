#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_CHOICE_READ_UB 20
#define ERROR_CHOICE_READ_RANGE 21

void menu(void);
int input_choice(int *choice);
void clean_buffer(void);

#endif