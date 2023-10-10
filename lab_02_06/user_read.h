#ifndef USER_READ_H
#define USER_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types_macros.h"
#include "helper.h"
#include "read_house.h"

int append_house(house_type *house_buffer, house_type *house_table, int *house_table_len);

int input_address_general(char *house_address);
int input_secondary_general(secondary_type *secondary_buffer);
int input_primary_general(primary_type *primary_buffer);

int input_string(char *string);
int input_house(int *house);
int input_apartment(int *apartment);
int input_postalcode(int *postal_code);

int input_sqr_meters(double *sqr_meters);
int input_rooms_n(int *rooms_n);
int input_sqr_meter_price(double *sqr_meter_price);
int input_is_primary(int *is_primary);

int input_build_year(int *build_time);
int input_owners_n(int *owners_n);
int input_bool_pets(int *pets);

int input_bool_interior(int *interior);

int input_bool_interior(int *interior);
#endif