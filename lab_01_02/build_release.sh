#!/bin/bash

OUT_FILE=app.exe

gcc -std=c99 -Wall -Werror -Wextra -Wunused -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -c real_type.c main.c -lm
gcc -std=c99 -Wall -Werror -Wextra -Wunused -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla real_type.o main.o -o $OUT_FILE -lm