#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "bst.h"


int max(int a, int b);
int get_balance(node_t *N);
int avl_import(node_t **root_avl, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int string_array_len);
node_t *node_avl_create(char *data);
node_t *right_rotate(node_t *y);
node_t *left_rotate(node_t *x);
node_t *avl_insert(node_t *node, char *data);
node_t *avl_delete(node_t *root, char *data);
node_t *avl_delete_by_letter(node_t *root, char letter);

#endif