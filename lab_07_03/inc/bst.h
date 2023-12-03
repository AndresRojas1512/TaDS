#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

typedef struct node node_t;

struct node
{
    char data[STRING_MAX_SIZE + 1];
    node_t *right;
    node_t *left;
};

node_t *node_create(char *data);
void node_free(node_t *node);
int bst_import(node_t **root, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int string_array_len);

node_t *bst_insert(node_t *root, char *data);
node_t *bst_delete(node_t *root, char *data);
node_t *bst_search(node_t *root, char *data);
node_t *bst_delete_by_letter(node_t *root, char letter);
node_t *bst_delete_min_node(node_t *root, int *delete_count, char *min_value);
void bst_preorder(node_t *root);
void bst_inorder(node_t *root);
void bst_postorder(node_t *root);

void bst_to_dot(FILE *file, node_t *root);
void bst_graphviz_format(FILE *file, node_t *root);
int maximum(int a, int b);
int bst_find_height(node_t *root);

#endif