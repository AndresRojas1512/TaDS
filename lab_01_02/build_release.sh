#!/bin/bash

OUT_FILE=app.exe

gcc -std=c99 -Wall -Werror -Wextra -Wunused -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -c user_interface.c real_type.c multiplication.c main.c -lm
gcc -std=c99 -Wall -Werror -Wextra -Wunused -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla user_interface.o real_type.o multiplication.o main.o -o $OUT_FILE -lm