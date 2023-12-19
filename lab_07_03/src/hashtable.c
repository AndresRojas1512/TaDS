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
======= Open addressing ======
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
Restructure the hashtable open addressing
*/
int hashtable_restructure_oa(hashtable_oa_t *hashtable_oa)
{
    int new_capacity = hashtable_oa->capacity * 2;
    int new_size = 0;
    string_t **new_table = (string_t **)malloc(new_capacity * sizeof(string_t *));
    if (!new_table)
        return EXIT_FAILURE;
    
    for (int i = 0; i < new_capacity; i++)
        new_table[i] = NULL;

    for (int i = 0; i < hashtable_oa->capacity; i++)
    {
        if (hashtable_oa->hashtable_arr[i] != NULL)
        {
            int new_index = hash(hashtable_oa->hashtable_arr[i]->string, new_capacity);
            for (int j = 0; j < new_capacity; j++)
            {
                int try = (j + new_index) % new_capacity;
                if (new_table[try] == NULL)
                {
                    new_table[try] = (string_t *)malloc(sizeof(string_t));
                    if (!new_table[try])
                    {
                        for (int k = 0; k < new_capacity; k++)
                            free(new_table[k]);
                        free(new_table);
                        return EXIT_FAILURE;
                    }
                    strcpy(new_table[try]->string, hashtable_oa->hashtable_arr[i]->string);
                    new_size++;
                    break;
                }
            }
        }
    }

    hashtable_free_oa(hashtable_oa);
    hashtable_oa->hashtable_arr = new_table;
    hashtable_oa->capacity = new_capacity;
    hashtable_oa->size = new_size;
    return EXIT_SUCCESS;
}

/*
Insert open addressing
*/
int hashtable_insert_oa(hashtable_oa_t *hashtable_oa, char *string)
{
    if (!string)
        return EXIT_FAILURE;

    int index = hash(string, hashtable_oa->capacity);
    for (int i = 0; i < hashtable_oa->capacity; i++)
    {
        int try = (i + index) % hashtable_oa->capacity;
        if (hashtable_oa->hashtable_arr[try] == NULL)
        {
            hashtable_oa->hashtable_arr[try] = (string_t *)malloc(sizeof(string_t));
            if (hashtable_oa->hashtable_arr[try] == NULL)
                return EXIT_FAILURE;
            strcpy(hashtable_oa->hashtable_arr[try]->string, string);
            hashtable_oa->size++;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
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
            tmp = hashtable_oa->hashtable_arr[try];
            hashtable_oa->hashtable_arr[try] = NULL;
            return tmp;
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
External chaining
*/
// void hashtable_init_ec(hashtable_ec_t *hashtable_ec, int capacity) // done
// {
//     hashtable_ec->capacity = capacity;
//     hashtable_ec->size = 0;
//     for (int i = 0; i < capacity; i++)
//         hashtable_ec->hashtable_ec_arr[i] = NULL;
// }

// int hashtable_insert_ec(hashtable_ec_t *hashtable_ec, char *string)
// {
//     if (!string)
//         return EXIT_FAILURE;
//     int index = hash(string);
//     node_ht_t *new_node = node_ht_create(string);
//     if (!new_node)
//         return EXIT_FAILURE;
//     new_node->next = hashtable_ec->hashtable_ec_arr[index];
//     hashtable_ec->hashtable_ec_arr[index] = new_node;
//     hashtable_ec->size++;
//     return EXIT_SUCCESS;
// }

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

// node_ht_t *node_ht_create(char *string)
// {
//     node_ht_t *new_node = (node_ht_t *)malloc(sizeof(node_ht_t));
//     if (!new_node)
//         return NULL;
//     strcpy(new_node->data, string);
//     new_node->next = NULL;
// }

// void hashtable_print_ec(hashtable_ec_t *hashtable_ec)
// {
//     printf("----------------------------------\n");
//     for (int i = 0; i < hashtable_ec->capacity; i++)
//     {
//         if (hashtable_ec->hashtable_ec_arr[i] == NULL)
//             printf("%d ---\n", i);
//         else
//         {
//             printf("%d ", i);
//             linked_list_print(hashtable_ec->hashtable_ec_arr[i]);
//             printf("\n");
//         }
//     }
//     printf("----------------------------------\n");
// }

// void linked_list_print(node_ht_t *head)
// {
//     node_ht_t *current = head;
//     while (current)
//     {
//         printf("%s ", current->data);
//         current = current->next;
//     }
// }