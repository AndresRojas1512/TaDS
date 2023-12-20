#include "avl.h"

/*
AVL create
*/
node_avl_t *node_avl_create(char *data)
{
    node_avl_t *new_node = (node_avl_t *)malloc(sizeof(node_avl_t));
    if (!new_node)
        return NULL;
    strcpy(new_node->data, data);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}

/*
Loop through an array of strings and append each word to the avl
*/
int avl_import(node_avl_t **root_avl, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int string_array_len)
{
    for (int i = 0; i < string_array_len; i++)
    {
        *root_avl = avl_insert(*root_avl, string_array[i]);
        if (!(*root_avl))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*
Right Rotate
*/
node_avl_t *right_rotate(node_avl_t *y)
{
    node_avl_t *x = y->left;
    node_avl_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(bst_find_height(y->left), bst_find_height(y->right)) + 1;
    x->height = max(bst_find_height(x->left), bst_find_height(x->right)) + 1;

    return x;
}

/*
Left Rotate
*/
node_avl_t *left_rotate(node_avl_t *x)
{
    node_avl_t *y = x->right;
    node_avl_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(bst_find_height(x->left), bst_find_height(x->right)) + 1;
    y->height = max(bst_find_height(y->left), bst_find_height(y->right)) + 1;

    return y;
}

/*
Find max
*/
int max(int a, int b)
{
    return (a > b)? a : b;
}

/*
Get Balance Factor
*/
int get_balance(node_avl_t *N)
{
    if (N == NULL)
        return 0;
    return bst_find_height(N->left) - bst_find_height(N->right);
}

/*
AVL Insert
*/
node_avl_t *avl_insert(node_avl_t *node, char *data)
{
    if (node == NULL)
        return node_create(data);

    if (strcmp(data, node->data) < 0)
        node->left = avl_insert(node->left, data);
    else if (strcmp(data, node->data) > 0)
        node->right = avl_insert(node->right, data);
    else
        return node;

    node->height = 1 + max(bst_find_height(node->left), bst_find_height(node->right));
    int balance = get_balance(node);

    // Left Left
    if (balance > 1 && strcmp(data, node->left->data) < 0)
        return right_rotate(node);

    // Right Right
    if (balance < -1 && strcmp(data, node->right->data) > 0)
        return left_rotate(node);

    // Left Right
    if (balance > 1 && strcmp(data, node->left->data) > 0)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Right Left
    if (balance < -1 && strcmp(data, node->right->data) < 0)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}