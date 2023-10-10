#ifndef TYPES_MACROS_H
#define TYPES_MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Errors
#define ERROR_OPEN_FILE 100
#define ERROR_TABLE_OVERFLOW 101

#define ERROR_READING_ADDRESS 102
#define ERROR_READING_SQR_METERS 103
#define ERROR_READING_ROOMS_N 104
#define ERROR_READING_SQR_METER_PRICE 105
#define ERROR_READING_HOUSE_TYPE 106

#define ERROR_HOUSE_TYPE_FLAG 107
#define ERROR_PETS_FLAG 108
#define ERROR_READING_UB 109
#define ERROR_OWNERS_VALUE 110
#define ERROR_YEAR_VALUE 111
#define ERROR_READING_SEC_FIELDS 112
#define ERROR_READING_PRIM_FIELDS 113
#define ERROR_NO_DATA_IMPORTED 114

#define MAX_ADDRESS_SIZE 100
#define MAX_TABLE_SIZE 500
#define MAX_OWNERS_AMOUNT 50
#define LL_YEAR 1500
#define RL_YEAR 2070
#define ADDRESS_STR_ITEM_SIZE 15
#define FILE_NAME_SIZE 20

#define ERROR_INPUT_ADDRESS 115
#define ERROR_INPUT_STREET 123
#define ERROR_INPUT_HOUSE_NO 116
#define ERROR_INPUT_APARTMENT_NO 117
#define ERROR_INPUT_REGION 118
#define ERROR_INPUT_COUNTRY 119
#define ERROR_INPUT_POSTALCODE 120

#define ERROR_INPUT_EMPTY_READ 121
#define ERROR_INPUT_OVERFLOW 122
#define ERROR_CANNOT_ADD_OVERFLOW 123
#define ERROR_FILE_NAME 124

#define ERROR_INPUT_LL 125
#define ERROR_INPUT_RL 126


typedef int (*comparator_t)(const void *, const void *);
typedef struct primary_type
{
    int interior;
} primary_type;

typedef struct secondary_type
{
    int build_year;
    int owners_n;
    int pets;
} secondary_type;

typedef union type_type
{
    primary_type primary_house;
    secondary_type secondary_house;
} type_type;

typedef struct house_type
{
    char address[MAX_ADDRESS_SIZE];
    double sqr_meters;
    int rooms_n;
    double sqr_meter_price;
    int is_primary;
    type_type house_type;
} house_type;

typedef struct key_type
{
    double sqr_meter_price;
    int ot_idx;
} key_type;

#endif