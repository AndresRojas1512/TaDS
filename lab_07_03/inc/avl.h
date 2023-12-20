#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

typedef struct node_avl node_avl_t;

struct node_avl
{
    char data[STRING_MAX_SIZE + 1];
    node_avl_t *right;
    node_avl_t *left;
    int height;
};

int max(int a, int b);
int get_balance(node_avl_t *N);
int avl_import(node_avl_t **root_avl, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int string_array_len);
node_avl_t *node_avl_create(char *data);
node_avl_t *right_rotate(node_avl_t *y);
node_avl_t *left_rotate(node_avl_t *x);
node_avl_t *avl_insert(node_avl_t *node, char *data);

#endif