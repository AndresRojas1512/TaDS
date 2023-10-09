#ifndef READ_HOUSE_H
#define READ_HOUSE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "helper.h"
#include "types_macros.h"

// MAIN: house
int read_house(FILE *file, house_type *house_buffer);

// GENERAL: address
int read_address_general(FILE *file, char *house_address);

// GENERAL: primary fields
int read_primary_general(FILE *file, primary_type *primary_buffer);

// GENERAL: secondary fields
int read_secondary_general(FILE *file, secondary_type *secondary_buffer);

// PARSE: address
int read_address_street(FILE *file, char *street);
int read_address_house(FILE *file, char *house);
int read_address_apartment(FILE *file, char *apartment);
int read_address_region(FILE *file, char *region);
int read_address_country(FILE *file, char *country);
int read_address_postalcode(FILE *file, char *postalcode);

// READ: main fields
int read_sqr_meters(FILE *file, double *sqr_meters);
int read_rooms_n(FILE *file, int *rooms_n);
int read_sqr_meter_price(FILE *file, double *sqr_meter_price);
int read_is_primary(FILE *file, int *is_primary);

//READ: secondary fields
int read_build_year(FILE *file, int *build_time);
int read_owners_n(FILE *file, int *owners_n);
int read_bool_pets(FILE *file, int *pets);

// READ: primary fields
int read_bool_interior(FILE *file, int *interior);

#endif