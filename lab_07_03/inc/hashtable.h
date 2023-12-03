#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABLE_SIZE 10
#define ERROR_HT_COLLISION 50
#define STRING_SIZE 25

typedef struct hashtable_t
{
    char *hashtable_arr[HASHTABLE_SIZE];
    int capacity;
    int size;
} hashtable_t;

void hashtable_init(hashtable_t *hashtable, int capacity);
unsigned int hash(char *string);
void hashtable_print(hashtable_t *hashtable);
int hashtable_insert(hashtable_t *hashtable, char *string);
char *hashtable_find(hashtable_t *hashtable, char *string);
char *hashtable_delete(hashtable_t *hashtable, char *string);

#endif