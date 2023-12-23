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
Delete element from hashtable OA
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

void hashtable_delete_by_letter_oa(hashtable_oa_t *hashtable_oa, char letter)
{
    if (!hashtable_oa)
        return;

    for (int i = 0; i < hashtable_oa->capacity; i++)
    {
        string_t *current_string = hashtable_oa->hashtable_arr[i];
        if (current_string != NULL && current_string->string[0] == letter)
        {
            free(current_string);
            hashtable_oa->hashtable_arr[i] = NULL;
            hashtable_oa->size--;
        }
    }
}


void hashtable_free_oa(hashtable_oa_t *hashtable_oa)
{
    for (int i = 0; i < hashtable_oa->capacity; i++)
        free(hashtable_oa->hashtable_arr[i]);
    free(hashtable_oa->hashtable_arr);
}

int hashtable_oa_count_records(hashtable_oa_t *hashtable_oa)
{
    if (!hashtable_oa)
        return 0;
    
    int count = 0;
    for (int i = 0; i < hashtable_oa->capacity; i++)
    {
        if (hashtable_oa->hashtable_arr[i])
            count++;
    }
    return count;
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

/*
Restrucutre the EC table
*/
int hashtable_restructure_ec(hashtable_ec_t *hashtable_ec, int new_capacity)
{
    node_ht_t **new_table = (node_ht_t **)malloc(new_capacity * sizeof(node_ht_t *));
    if (!new_table)
        return ERROR_EC_MEMORY_ALLOC;

    for (int i = 0; i < new_capacity; i++)
        new_table[i] = NULL;

    hashtable_free_ec(hashtable_ec);
    hashtable_ec->hashtable_ec_arr = new_table;
    hashtable_ec->capacity = new_capacity;
    hashtable_ec->size = 0;
    return EXIT_SUCCESS;
}

/*
Insert element to the EC table
*/
int hashtable_insert_ec(hashtable_ec_t *hashtable_ec, char *string, int iters_threshold)
{
    if (!string)
        return ERROR_EC_PARAMS;

    int index = hash(string, hashtable_ec->capacity);
    int list_length = 0;

    node_ht_t *new_node = node_ht_create(string);
    if (!new_node)
        return ERROR_EC_MEMORY_ALLOC;

    new_node->next = hashtable_ec->hashtable_ec_arr[index];
    hashtable_ec->hashtable_ec_arr[index] = new_node;
    hashtable_ec->size++;

    node_ht_t *current = new_node;
    while (current)
    {
        list_length++;
        current = current->next;
    }
    if (list_length > iters_threshold)
        return ERROR_EC_ITERATIONS_OVERFLOW;

    return EXIT_SUCCESS;
}

/*
Add to the end of the list
*/
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
Delete a word in a EC Hashtable
*/
node_ht_t *hashtable_delete_ec(hashtable_ec_t *hashtable_ec, char *string)
{
    if (!string)
        return NULL;

    int index = hash(string, hashtable_ec->capacity);
    node_ht_t *current = hashtable_ec->hashtable_ec_arr[index];
    node_ht_t *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->data, string) == 0)
        {
            if (prev == NULL)
                hashtable_ec->hashtable_ec_arr[index] = current->next;
            else
                prev->next = current->next;
            hashtable_ec->size--;
            return current;
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}

/*
Find a word in External Chain hashtable.
*/
node_ht_t *hashtable_find_ec(hashtable_ec_t *hashtable_ec, char *string)
{
    if (!string)
        return NULL;

    int index = hash(string, hashtable_ec->capacity);
    node_ht_t *current = hashtable_ec->hashtable_ec_arr[index];

    while (current != NULL)
    {
        if (!strcmp(current->data, string))
            return current;
        current = current->next;
    }
    return NULL;
}

/*
Delete words by letter in hashtable_ec
*/
void hashtable_delete_by_letter_ec(hashtable_ec_t *hashtable_ec, char letter)
{
    if (!hashtable_ec)
        return;

    for (int i = 0; i < hashtable_ec->capacity; i++)
    {
        node_ht_t **current_node = &(hashtable_ec->hashtable_ec_arr[i]);
        while (*current_node != NULL)
        {
            if ((*current_node)->data[0] == letter)
            {
                node_ht_t *temp = *current_node;
                *current_node = (*current_node)->next;
                free(temp);
                hashtable_ec->size--;
            }
            else
                current_node = &((*current_node)->next);
        }
    }
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

int hashtable_ec_count_records(hashtable_ec_t *hashtable_ec)
{
    if (!hashtable_ec)
        return 0;

    int count = 0;
    for (int i = 0; i < hashtable_ec->capacity; i++)
    {
        node_ht_t *current = hashtable_ec->hashtable_ec_arr[i];
        while (current)
        {
            count++;
            current = current->next;
        }
    }
    return count;
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

/*
Init Functions
*/
int hashtable_oa_init(hashtable_oa_t *hashtable_oa, int capacity, char string_array[][STRING_SIZE], int string_array_len, int iters_threshold)
{
    int iterations, exit_code;
    if (hashtable_create_oa(hashtable_oa, capacity) != EXIT_SUCCESS)
        return ERROR_OA_MEMORY_ALLOC;

    bool all_elements_inserted = false;
    while (!all_elements_inserted)
    {
        all_elements_inserted = true;
        for (int i = 0; i < string_array_len; i++)
        {
            exit_code = hashtable_insert_oa(hashtable_oa, string_array[i], &iterations, iters_threshold);
            if (exit_code == ERROR_OA_ITERATIONS_OVERFLOW)
            {
                // printf("Restructuring table...\n");
                if (hashtable_restructure_oa(hashtable_oa) != EXIT_SUCCESS)
                    return ERROR_OA_MEMORY_ALLOC;
                all_elements_inserted = false;
                break;
            }
            else if (exit_code != EXIT_SUCCESS)
                return exit_code;
        }
    }
    return EXIT_SUCCESS;
}

int hashtable_ec_init(hashtable_ec_t *hashtable_ec, int capacity, char string_array[][STRING_SIZE], int string_array_len, int iters_threshold)
{
    if (hashtable_create_ec(hashtable_ec, capacity) != EXIT_SUCCESS)
        return ERROR_EC_MEMORY_ALLOC;
    while (true)
    {
        bool restructuring_needed = false;
        for (int i = 0; i < string_array_len; i++)
        {
            int exit_code = hashtable_insert_ec(hashtable_ec, string_array[i], iters_threshold);
            if (exit_code == ERROR_EC_ITERATIONS_OVERFLOW)
            {
                // printf("Restructuring table...\n");
                int new_capacity = hashtable_ec->capacity * 2;
                if (hashtable_restructure_ec(hashtable_ec, new_capacity) != EXIT_SUCCESS)
                    return ERROR_EC_MEMORY_ALLOC;
                restructuring_needed = true;
                break;
            }
            else if (exit_code != EXIT_SUCCESS)
                return exit_code;
        }
        if (!restructuring_needed)
            break;
    }
    return EXIT_SUCCESS;
}
