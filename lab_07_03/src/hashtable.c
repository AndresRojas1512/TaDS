#include "hashtable.h"

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

void hashtable_init(hashtable_t *hashtable, int capacity)
{
    hashtable->capacity = capacity;
    hashtable->size = 0;
    for (int i = 0; i < capacity; i++)
        hashtable->hashtable_arr[i] = NULL;
}

void hashtable_print(hashtable_t *hashtable)
{
    printf("----------------------------------\n");
    for (int i = 0; i < hashtable->capacity; i++)
    {
        if (hashtable->hashtable_arr[i] == NULL)
            printf("\t%d ---\n", i);
        else
            printf("\t%s\n", hashtable->hashtable_arr[i]);
    }
    printf("----------------------------------\n");
}

int hashtable_insert(hashtable_t *hashtable, char *string)
{
    int exit_code = EXIT_SUCCESS;
    if (!string)
        return EXIT_FAILURE;
    int index = hash(string);
    if (hashtable->hashtable_arr[index] == NULL)
        hashtable->hashtable_arr[index] = string;
    else
        exit_code = ERROR_HT_COLLISION;
    return exit_code;
}

char *hashtable_find(hashtable_t *hashtable, char *string)
{
    if (!string)
        return NULL;
    int index = hash(string);
    if (hashtable->hashtable_arr[index] && !strcmp(hashtable->hashtable_arr[index], string))
        return hashtable->hashtable_arr[index];
    return NULL;
}

char *hashtable_delete(hashtable_t *hashtable, char *string)
{
    char *tmp = NULL; 
    if (!string)
        return NULL;
    int index = hash(string);
    if (hashtable->hashtable_arr[index] && !strcmp(hashtable->hashtable_arr[index], string))
    {
        tmp = hashtable->hashtable_arr[index];
        hashtable->hashtable_arr[index] = NULL;
        return tmp;
    }
    return NULL;
}

