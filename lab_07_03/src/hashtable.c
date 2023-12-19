#include "hashtable.h"

/*
Hash function
*/
unsigned int hash(char *string)
{
    int len = strlen(string);
    unsigned int hash_value = 0;
    for (int i = 0; i < len; i++)
    {
        hash_value += string[i];
        hash_value = (hash_value * string[i]) % HASHTABLE_SIZE;
    }
    return hash_value;
}

void hashtable_init_oa(hashtable_oa_t *hashtable, int capacity) // done
{
    hashtable->capacity = capacity;
    hashtable->size = 0;
    for (int i = 0; i < capacity; i++)
        hashtable->hashtable_arr[i] = NULL;
}

void hashtable_print_oa(hashtable_oa_t *hashtable) // done
{
    printf("----------------------------------\n");
    for (int i = 0; i < hashtable->capacity; i++)
    {
        if (hashtable->hashtable_arr[i] == NULL)
            printf("\t%d ---\n", i);
        else
            printf("\t%s\n", hashtable->hashtable_arr[i]->string);
    }
    printf("----------------------------------\n");
}

int hashtable_insert_oa(hashtable_oa_t *hashtable, char *string) // done
{
    if (!string)
        return EXIT_FAILURE;

    int index = hash(string);
    for (int i = 0; i < hashtable->capacity; i++)
    {
        int try = (i + index) % hashtable->capacity;
        if (hashtable->hashtable_arr[try] == NULL)
        {
            hashtable->hashtable_arr[try] = (string_t *)malloc(sizeof(string_t));
            if (hashtable->hashtable_arr[try] == NULL)
                return EXIT_FAILURE;
            strcpy(hashtable->hashtable_arr[try]->string, string);
            hashtable->size++;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

string_t *hashtable_find_oa(hashtable_oa_t *hashtable, char *string) // done
{
    if (!string)
        return NULL;
    int index = hash(string);
    for (int i = 0; i < hashtable->capacity; i++)
    {
        int try = (i + index) % hashtable->capacity;
        if ((hashtable->hashtable_arr[try] != NULL) && !strcmp(hashtable->hashtable_arr[try]->string, string))
            return hashtable->hashtable_arr[try];
    }
    return NULL;
}

string_t *hashtable_delete_oa(hashtable_oa_t *hashtable, char *string) // done
{
    string_t *tmp = NULL;
    if (!string)
        return NULL;
    int index = hash(string);
    for (int i = 0; i < hashtable->capacity; i++)
    {
        int try = (i + index) % hashtable->capacity;
        if (hashtable->hashtable_arr[try] != NULL && !strcmp(hashtable->hashtable_arr[try]->string, string))
            tmp = hashtable->hashtable_arr[try];
            hashtable->hashtable_arr[try] = NULL;
            return tmp;
    }
    return NULL;
}

/*
External chaining
*/
void hashtable_init_ec(hashtable_ec_t *hashtable_ec, int capacity) // done
{
    hashtable_ec->capacity = capacity;
    hashtable_ec->size = 0;
    for (int i = 0; i < capacity; i++)
        hashtable_ec->hashtable_ec_arr[i] = NULL;
}

int hashtable_insert_ec(hashtable_ec_t *hashtable_ec, char *string)
{
    if (!string)
        return EXIT_FAILURE;
    int index = hash(string);
    node_ht_t *new_node = node_ht_create(string);
    if (!new_node)
        return EXIT_FAILURE;
    new_node->next = hashtable_ec->hashtable_ec_arr[index];
    hashtable_ec->hashtable_ec_arr[index] = new_node;
    hashtable_ec->size++;
    return EXIT_SUCCESS;
}

node_ht_t *hashtable_delete_ec(hashtable_ec_t *hashtable_ec, char *string)
{
    if (!string)
        return NULL;

    int index = hash(string);
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

node_ht_t *hashtable_find_ec(hashtable_ec_t *hashtable_ec, char *string)
{
    if (!string)
        return NULL;

    int index = hash(string);
    node_ht_t *current = hashtable_ec->hashtable_ec_arr[index];

    while (current != NULL)
    {
        if (strcmp(current->data, string) == 0)
            return current;
        current = current->next;
    }

    return NULL;
}

node_ht_t *node_ht_create(char *string)
{
    node_ht_t *new_node = (node_ht_t *)malloc(sizeof(node_ht_t));
    if (!new_node)
        return NULL;
    strcpy(new_node->data, string);
    new_node->next = NULL;
}

void hashtable_print_ec(hashtable_ec_t *hashtable_ec)
{
    printf("----------------------------------\n");
    for (int i = 0; i < hashtable_ec->capacity; i++)
    {
        if (hashtable_ec->hashtable_ec_arr[i] == NULL)
            printf("%d ---\n", i);
        else
        {
            printf("%d ", i);
            linked_list_print(hashtable_ec->hashtable_ec_arr[i]);
            printf("\n");
        }
    }
    printf("----------------------------------\n");
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