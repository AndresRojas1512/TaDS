#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STRING_SIZE 25
#define HASHTABLE_SIZE 10
#define WORDS_MAX_AMOUNT_OA 1000

/*
OA errors
*/
#define ERROR_OA_ITERATIONS_OVERFLOW 30
#define ERROR_OA_MEMORY_ALLOC 31
#define ERROR_OA_INSERT 32

/*
EC errors
*/
#define ERROR_EC_MEMORY_ALLOC 40
#define ERROR_EC_PARAMS 41
#define ERROR_EC_ITERATIONS_OVERFLOW 42

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
    node_ht_t **hashtable_ec_arr;
    int size;
    int capacity;
} hashtable_ec_t;

/*
Hash Function
*/
unsigned int hash(char *string, int hashtable_capacity);

/*
Open Addressing
*/
int hashtable_create_oa(hashtable_oa_t *hashtable_oa, int capacity);
int hashtable_restructure_oa(hashtable_oa_t *hashtable_oa);
int hashtable_insert_oa(hashtable_oa_t *hashtable_oa, char *string, int *iterations, int iters_n);
void hashtable_print_oa(hashtable_oa_t *hashtable);
string_t *hashtable_find_oa(hashtable_oa_t *hashtable, char *string);
string_t *hashtable_delete_oa(hashtable_oa_t *hashtable, char *string);
void hashtable_free_oa(hashtable_oa_t *hashtable_oa);

/*
External Chaining
*/
int hashtable_create_ec(hashtable_ec_t *hashtable_ec, int capacity);
void hashtable_free_ec(hashtable_ec_t *hashtable_ec);
int hashtable_insert_ec(hashtable_ec_t *hashtable_ec, char *string, int iters_threshold);
void hashtable_print_ec(hashtable_ec_t *hashtable_ec);
int hashtable_restructure_ec(hashtable_ec_t *hashtable_ec, int new_capacity);
node_ht_t *hashtable_find_ec(hashtable_ec_t *hashtable_ec, char *string);
node_ht_t *hashtable_delete_ec(hashtable_ec_t *hashtable_ec, char *string);

void linked_list_append(node_ht_t **head, node_ht_t *new_node, int *list_length);
void linked_list_free(node_ht_t **head);
void linked_list_print(node_ht_t *head);

node_ht_t *node_ht_create(char *string);

/*
Init Functions
*/
int hashtable_oa_init(hashtable_oa_t *hashtable_oa, int capacity, char string_array[][STRING_SIZE], int string_array_len, int iters_threshold);
int hashtable_ec_init(hashtable_ec_t *hashtable_ec, int capacity, char string_array[][STRING_SIZE], int string_array_len, int iters_threshold);


#endif