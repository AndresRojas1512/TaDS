#include "avl.h"

/*
AVL create
*/
node_t *node_avl_create(char *data)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
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
int avl_import(node_t **root_avl, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int string_array_len)
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
node_t *right_rotate(node_t *y)
{
    node_t *x = y->left;
    node_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(bst_find_height(y->left), bst_find_height(y->right)) + 1;
    x->height = max(bst_find_height(x->left), bst_find_height(x->right)) + 1;

    return x;
}

/*
Left Rotate
*/
node_t *left_rotate(node_t *x)
{
    node_t *y = x->right;
    node_t *T2 = y->left;

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
int get_balance(node_t *N)
{
    if (N == NULL)
        return 0;
    return bst_find_height(N->left) - bst_find_height(N->right);
}

/*
AVL Insert
*/
node_t *avl_insert(node_t *node, char *data)
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

/*
AVL Delete
*/
node_t *avl_delete(node_t *root, char *data)
{
    if (root == NULL)
        return root;
    
    if (strcmp(data, root->data) < 0)
        root->left = avl_delete(root->left, data);

    else if (strcmp(data, root->data) > 0)
        root->right = avl_delete(root->right, data);

    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            node_t *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            node_t *temp = bst_findmin(root->right);
            strcpy(root->data, temp->data);
            root->right = avl_delete(root->right, temp->data);
        }
    }
    if (root == NULL)
        return root;

    root->height = 1 + max(bst_find_height(root->left), bst_find_height(root->right));
    int balance = get_balance(root);

    // Left Left
    if (balance > 1 && get_balance(root->left) >= 0)
        return right_rotate(root);

    // Left Right
    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // Right Right
    if (balance < -1 && get_balance(root->right) <= 0)
        return left_rotate(root);

    // Right Left
    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

node_t *avl_delete_by_letter(node_t *root, char letter)
{
    if (!root)
        return root;
    
    root->left = avl_delete_by_letter(root->left, letter);
    root->right = avl_delete_by_letter(root->right, letter);

    if (root->data[0] == letter)
    {
        if (!root->left || !root->right)
        {
            node_t *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            node_t *temp = bst_findmin(root->right);
            strcpy(root->data, temp->data);
            root->right = avl_delete(root->right, temp->data);
        }
    }
    if (root == NULL)
        return root;
    root->height = 1 + max(bst_find_height(root->left), bst_find_height(root->right));
    int balance = get_balance(root);

    // Left Left
    if (balance > 1 && get_balance(root->left) >= 0)
        return right_rotate(root);

    // Left Right
    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // Right Right
    if (balance < -1 && get_balance(root->right) <= 0)
        return left_rotate(root);

    // Right Left
    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}
