#include "hashtable.h"

/*
Hash function
*/
unsigned int hash(char *string, int hashtable_capacity)
{
    int len = strlen(string);
    unsigned int hash_value = 0;
    for (int i = 0; i < len; i++)
    {
        hash_value += string[i];
        hash_value = (hash_value * string[i]) % hashtable_capacity;
    }
    return hash_value;
}

/*
===== Open addressing =====
*/

/*
Allocate memory for the hashtable
*/
int hashtable_create_oa(hashtable_oa_t *hashtable_oa, int capacity)
{
    hashtable_oa->hashtable_arr = (string_t **)malloc(capacity * sizeof(string_t *));
    if (!hashtable_oa->hashtable_arr)
        return EXIT_FAILURE;
    hashtable_oa->capacity = capacity;
    hashtable_oa->size = 0;
    for (int i = 0; i < hashtable_oa->capacity; i++)
        hashtable_oa->hashtable_arr[i] = NULL;
    return EXIT_SUCCESS;
}

/*
Restructure the hashtable open addressing.
*/
int hashtable_restructure_oa(hashtable_oa_t *hashtable_oa)
{
    int new_capacity = hashtable_oa->capacity * 2;
    string_t **new_table = (string_t **)malloc(new_capacity * sizeof(string_t *));
    if (!new_table)
        return EXIT_FAILURE;
    
    for (int i = 0; i < new_capacity; i++)
        new_table[i] = NULL;

    hashtable_free_oa(hashtable_oa);
    hashtable_oa->hashtable_arr = new_table;
    hashtable_oa->capacity = new_capacity;
    hashtable_oa->size = 0;
    return EXIT_SUCCESS;
}

/*
Insert open addressing. Takes in count the amount of iterations
*/
int hashtable_insert_oa(hashtable_oa_t *hashtable_oa, char *string, int *iterations, int iters_n)
{
    *iterations = 0;
    if (!string)
        return EXIT_FAILURE;
    int index = hash(string, hashtable_oa->capacity);

    for (int i = 0; i < hashtable_oa->capacity; i++)
    {
        int try = (i + index) % hashtable_oa->capacity;
        (*iterations)++;
        if (*iterations > iters_n)
            return ERROR_OA_ITERATIONS_OVERFLOW;
        if (hashtable_oa->hashtable_arr[try] == NULL)
        {
            hashtable_oa->hashtable_arr[try] = (string_t *)malloc(sizeof(string_t));
            if (hashtable_oa->hashtable_arr[try] == NULL)
                return ERROR_OA_MEMORY_ALLOC;
            strcpy(hashtable_oa->hashtable_arr[try]->string, string);
            hashtable_oa->size++;
            return EXIT_SUCCESS;
        }
    }
    return ERROR_OA_INSERT;
}

/*
Print the hash table
*/
void hashtable_print_oa(hashtable_oa_t *hashtable_oa)
{
    printf("\tSTART\n");
    for (int i = 0; i < hashtable_oa->capacity; i++)
    {
        if (hashtable_oa->hashtable_arr[i] == NULL)
            printf("\t%d ---\n", i);
        else
            printf("\t%d - %s\n", i, hashtable_oa->hashtable_arr[i]->string);
    }
    printf("\tEND\n");
}

/*
Find element in open addressing
*/
string_t *hashtable_find_oa(hashtable_oa_t *hashtable_oa, char *string)
{
    if (!string)
        return NULL;
    int index = hash(string, hashtable_oa->capacity);
    for (int i = 0; i < hashtable_oa->capacity; i++)
    {
        int try = (i + index) % hashtable_oa->capacity;
        if ((hashtable_oa->hashtable_arr[try] != NULL) && !strcmp(hashtable_oa->hashtable_arr[try]->string, string))
            return hashtable_oa->hashtable_arr[try];
    }
    return NULL;
}

/*
Delete element from hashtable
*/
string_t *hashtable_delete_oa(hashtable_oa_t *hashtable_oa, char *string)
{
    string_t *tmp = NULL;
    if (!string)
        return NULL;
    int index = hash(string, hashtable_oa->capacity);
    for (int i = 0; i < hashtable_oa->capacity; i++)
    {
        int try = (i + index) % hashtable_oa->capacity;
        if (hashtable_oa->hashtable_arr[try] != NULL && !strcmp(hashtable_oa->hashtable_arr[try]->string, string))
        {
            tmp = hashtable_oa->hashtable_arr[try];
            hashtable_oa->hashtable_arr[try] = NULL;
            return tmp;
        }
    }
    return NULL;
}

void hashtable_free_oa(hashtable_oa_t *hashtable_oa)
{
    for (int i = 0; i < hashtable_oa->capacity; i++)
        free(hashtable_oa->hashtable_arr[i]);
    free(hashtable_oa->hashtable_arr);
}

/*
===== External chaining =====
*/

/*
Create hashtable of external chaining
*/
int hashtable_create_ec(hashtable_ec_t *hashtable_ec, int capacity)
{
    hashtable_ec->hashtable_ec_arr = (node_ht_t **)malloc(capacity * sizeof(node_ht_t *));
    if (!hashtable_ec->hashtable_ec_arr)
        return ERROR_EC_MEMORY_ALLOC;
    hashtable_ec->capacity = capacity;
    hashtable_ec->size = 0;
    for (int i = 0; i < capacity; i++)
        hashtable_ec->hashtable_ec_arr[i] = NULL;
    return EXIT_SUCCESS;
}

int hashtable_restructure_ec(hashtable_ec_t *hashtable_ec, int new_capacity) {
    node_ht_t **new_table = (node_ht_t **)malloc(new_capacity * sizeof(node_ht_t *));
    if (!new_table) {
        return ERROR_EC_MEMORY_ALLOC; // Memory allocation failure
    }

    for (int i = 0; i < new_capacity; i++) {
        new_table[i] = NULL;
    }

    // Free the old table's nodes
    for (int i = 0; i < hashtable_ec->capacity; i++) {
        node_ht_t *current = hashtable_ec->hashtable_ec_arr[i];
        while (current != NULL) {
            node_ht_t *next = current->next;
            free(current);  // Assuming each node was dynamically allocated
            current = next;
        }
    }
    free(hashtable_ec->hashtable_ec_arr); // Free the old table array

    hashtable_ec->hashtable_ec_arr = new_table;
    hashtable_ec->capacity = new_capacity;
    hashtable_ec->size = 0; // Reset size
    return EXIT_SUCCESS;
}

int hashtable_insert_ec(hashtable_ec_t *hashtable_ec, char *string, int iters_threshold) {
    if (!string) {
        return ERROR_EC_PARAMS; // Error due to invalid parameter
    }

    int index = hash(string, hashtable_ec->capacity);
    int list_length = 0;

    // Create a new node
    node_ht_t *new_node = node_ht_create(string);
    if (!new_node) {
        return ERROR_EC_MEMORY_ALLOC; // Error allocating memory for the new node
    }

    // Insert the node at the beginning of the list at the hash index
    new_node->next = hashtable_ec->hashtable_ec_arr[index];
    hashtable_ec->hashtable_ec_arr[index] = new_node;
    hashtable_ec->size++;

    // Count the length of the list at this index to check against the threshold
    node_ht_t *current = new_node;
    while (current) {
        list_length++;
        current = current->next;
    }

    // Check if the list length exceeds the threshold
    if (list_length > iters_threshold) {
        return ERROR_EC_ITERATIONS_OVERFLOW; // Signal that restructuring is needed
    }

    return EXIT_SUCCESS; // Successful insertion
}



void linked_list_append(node_ht_t **head, node_ht_t *new_node, int *list_length)
{
    *list_length = 0;
    if (!(*head))
        *head = new_node;
    else
    {
        node_ht_t *current = *head;
        (*list_length)++;
        while (current->next)
        {
            current = current->next;
            (*list_length)++;
        }
        current->next = new_node;
    }
    (*list_length)++;
}

/*
Free hashtable EC
*/
void hashtable_free_ec(hashtable_ec_t *hashtable_ec)
{
    for (int i = 0; i < hashtable_ec->capacity; i++)
        linked_list_free(&(hashtable_ec->hashtable_ec_arr[i]));
    free(hashtable_ec->hashtable_ec_arr);
}

/*
Print hashtable EC
*/
void hashtable_print_ec(hashtable_ec_t *hashtable_ec)
{
    printf("\tSTART\n");
    for (int i = 0; i < hashtable_ec->capacity; i++)
    {
        if (hashtable_ec->hashtable_ec_arr[i] == NULL)
            printf("%d ---\n", i);
        else
        {
            printf("%d - ", i);
            linked_list_print(hashtable_ec->hashtable_ec_arr[i]);
            printf("\n");
        }
    }
    printf("\tEND\n");
}

void linked_list_print(node_ht_t *head)
{
    node_ht_t *current = head;
    while (current)
    {
        printf("%s ", current->data);
        current = current->next;
    }
}

void linked_list_free(node_ht_t **head)
{
    node_ht_t *current = *head;
    node_ht_t *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

node_ht_t *node_ht_create(char *string)
{
    node_ht_t *new_node = (node_ht_t *)malloc(sizeof(node_ht_t));
    if (!new_node)
        return NULL;
    strcpy(new_node->data, string);
    new_node->next = NULL;
    return new_node;
}

// node_ht_t *hashtable_delete_ec(hashtable_ec_t *hashtable_ec, char *string)
// {
//     if (!string)
//         return NULL;

//     int index = hash(string);
//     node_ht_t *current = hashtable_ec->hashtable_ec_arr[index];
//     node_ht_t *prev = NULL;

//     while (current != NULL)
//     {
//         if (strcmp(current->data, string) == 0)
//         {
//             if (prev == NULL)
//                 hashtable_ec->hashtable_ec_arr[index] = current->next;
//             else
//                 prev->next = current->next;
//             hashtable_ec->size--;
//             return current;
//         }
//         prev = current;
//         current = current->next;
//     }
//     return NULL;
// }

// node_ht_t *hashtable_find_ec(hashtable_ec_t *hashtable_ec, char *string)
// {
//     if (!string)
//         return NULL;

//     int index = hash(string);
//     node_ht_t *current = hashtable_ec->hashtable_ec_arr[index];

//     while (current != NULL)
//     {
//         if (strcmp(current->data, string) == 0)
//             return current;
//         current = current->next;
//     }

//     return NULL;
// }