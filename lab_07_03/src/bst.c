#include "bst.h"

/*
Node create. The string is static (strcmp)
*/
node_t *node_create(char *data)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (!new_node)
        return NULL;
    strcpy(new_node->data, data);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/*
Node free
*/
void node_free(node_t *node)
{
    free(node);
}

/*
Insert a node (word to the bst)
*/
node_t *bst_insert(node_t *root, char *data)
{
    if (!root)
    {
        node_t *new_node = node_create(data);
        return new_node;
    }
    else if (strcmp(root->data, data) >= 0)
        root->left = bst_insert(root->left, data);
    else if (strcmp(root->data, data) < 0)
        root->right = bst_insert(root->right, data);
    return root;
}

/*
Find minimum element
*/
node_t *bst_findmin(node_t *root)
{
    if (!root)
        return root;
    else if (!root->left)
        return root;
    else
        return bst_findmin(root->left);
}

/*
Delete a node
*/
node_t *bst_delete(node_t *root, char *data)
{
    if (!root)
        return root;
    else if (strcmp(data, root->data) < 0)
        root->left = bst_delete(root->left, data);
    else if (strcmp(data, root->data) > 0)
        root->right = bst_delete(root->right, data);
    else
    {
        if (root->left == NULL)
        {
            node_t *tmp = root->right;
            node_free(root);
            return tmp;
        }
        else if (root->right == NULL)
        {
            node_t *tmp = root->left;
            node_free(root);
            return tmp;
        }
        node_t *tmp = bst_findmin(root->right);
        strcpy(root->data, tmp->data);
        root->right = bst_delete(root->right, tmp->data);
    }
    return root;
}

/*
Delete words starting with letter
*/
node_t *bst_delete_by_letter(node_t *root, char letter)
{
    if (!root)
        return root;
    
    root->left = bst_delete_by_letter(root->left, letter);
    root->right = bst_delete_by_letter(root->right, letter);

    if (root->data[0] == letter)
    {
        if (!root->left)
        {
            node_t *tmp = root->right;
            node_free(root);
            return tmp;
        }
        else if (!root->right)
        {
            node_t *tmp = root->left;
            node_free(root);
            return tmp;
        }
        else
        {
            node_t *tmp = bst_findmin(root->right);
            strcpy(root->data, tmp->data);
            root->right = bst_delete(root->right, tmp->data);
        }
    }
    return root;
}

/*
Loop through an array of strings and append each word to the bst
*/
int bst_import(node_t **root, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int string_array_len)
{
    for (int i = 0; i < string_array_len; i++)
    {
        *root = bst_insert(*root, string_array[i]);
        if (!(*root))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*
Preorder traversal
*/
void bst_preorder(node_t *root)
{
    if (!root)
        return;
    printf("%s\n", root->data);
    bst_preorder(root->left);
    bst_preorder(root->right);
}

/*
Inorder traversal
*/
void bst_inorder(node_t *root)
{
    if (!root)
        return;
    bst_inorder(root->left);
    printf("%s\n", root->data);
    bst_inorder(root->right);
}

/*
Postorder traversal
*/
void bst_postorder(node_t *root)
{
    if (!root)
        return;
    bst_postorder(root->left);
    bst_postorder(root->right);
    printf("%s\n", root->data);
}

/*
Search a word
*/
node_t *bst_search(node_t *root, char *data)
{
    if (!root || !strcmp(root->data, data))
        return root;

    if (strcmp(data, root->data) > 0)
        return bst_search(root->right, data);
    
    return bst_search(root->left, data);
}

/*
Find Height
*/
int bst_find_height(node_t *root)
{
    if (!root)
        return -1;
    return maximum(bst_find_height(root->left), bst_find_height(root->right)) + 1;
}

/*
Write .gv file (dot)
*/
void bst_to_dot(FILE *file, node_t *root)
{
    if (!root)
        return;

    fprintf(file, "\"%s\";\n", root->data);

    if (root->left)
    {
        fprintf(file, "\"%s\" -> \"%s\";\n", root->data, root->left->data);
        bst_to_dot(file, root->left);
    }
    else
    {
        fprintf(file, "\"%s\" -> \"null_l_%s\" [style=invis];\n", root->data, root->data);
        fprintf(file, "\"null_l_%s\" [style=invis];\n", root->data);
    }

    if (root->right)
    {
        fprintf(file, "\"%s\" -> \"%s\";\n", root->data, root->right->data);
        bst_to_dot(file, root->right);
    }
    else
    {
        fprintf(file, "\"%s\" -> \"null_r_%s\" [style=invis];\n", root->data, root->data);
        fprintf(file, "\"null_r_%s\" [style=invis];\n", root->data);
    }
}

/*
Format .gv file to graphviz
*/
void bst_graphviz_format(FILE *file, node_t *root)
{
    fprintf(file, "digraph BST {\n");
    bst_to_dot(file, root);
    fprintf(file, "}\n");
}

/*
Maximum of two integers
*/
int maximum(int a, int b)
{
    return (a > b) ? a : b;
}