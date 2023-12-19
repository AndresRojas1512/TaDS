#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABLE_SIZE 10
#define STRING_SIZE 25

#define ERROR_HT_COLLISION 50

#define ERROR_OA_ITERATIONS_OVERFLOW 30
#define ERROR_OA_MEMORY_ALLOC 31
#define ERROR_OA_INSERT 32

/*
HashTable OA
*/
typedef struct string_t
{
    char string[STRING_SIZE + 1];
} string_t;

typedef struct hashtable_oa_t
{
    string_t **hashtable_arr;
    int size;
    int capacity;
} hashtable_oa_t;

/*
HashTable EC
*/
typedef struct node_ht node_ht_t;

struct node_ht
{
    char data[STRING_SIZE + 1];
    node_ht_t *next;
};

typedef struct hashtable_ec_t
{
    node_ht_t *hashtable_ec_arr[HASHTABLE_SIZE];
    int capacity;
    int size;
} hashtable_ec_t;

unsigned int hash(char *string, int hashtable_capacity);

int hashtable_create_oa(hashtable_oa_t *hashtable_oa, int capacity);
int hashtable_restructure_oa(hashtable_oa_t *hashtable_oa);
void hashtable_print_oa(hashtable_oa_t *hashtable);
int hashtable_insert_oa(hashtable_oa_t *hashtable_oa, char *string, int *iterations, int iters_n);
string_t *hashtable_find_oa(hashtable_oa_t *hashtable, char *string);
string_t *hashtable_delete_oa(hashtable_oa_t *hashtable, char *string);
void hashtable_free_oa(hashtable_oa_t *hashtable_oa);

void hashtable_init_ec(hashtable_ec_t *hashtable_ec, int capacity);
int hashtable_insert_ec(hashtable_ec_t *hashtable_ec, char *string);
node_ht_t *node_ht_create(char *string);
void linked_list_print(node_ht_t *head);
void hashtable_print_ec(hashtable_ec_t *hashtable_ec);
node_ht_t *hashtable_delete_ec(hashtable_ec_t *hashtable_ec, char *string);
node_ht_t *hashtable_find_ec(hashtable_ec_t *hashtable_ec, char *string);

#endif