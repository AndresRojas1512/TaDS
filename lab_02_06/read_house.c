#include "read_house.h"

// MAIN: house
int read_house(FILE *file, house_type *house_buffer)
{
    int exit_code = EXIT_SUCCESS;
    if (read_address_general(file, house_buffer->address))
        exit_code = ERROR_READING_ADDRESS;
    else if (read_sqr_meters(file, &house_buffer->sqr_meters))
        exit_code = ERROR_READING_SQR_METERS;
    else if (read_rooms_n(file, &house_buffer->rooms_n))
        exit_code = ERROR_READING_ROOMS_N;
    else if (read_sqr_meter_price(file, &house_buffer->sqr_meter_price))
        exit_code = ERROR_READING_SQR_METER_PRICE;
    else if (read_is_primary(file, &house_buffer->is_primary))
        exit_code = ERROR_READING_HOUSE_TYPE;
    else
    {
        // printf("\ttype: %d\n", house_buffer->is_primary);
        if (house_buffer->is_primary)
        {
            if (read_primary_general(file, &house_buffer->house_type.primary_house))
                exit_code = ERROR_READING_PRIM_FIELDS;
        }
        else if (!(house_buffer->is_primary))
        {
            if (read_secondary_general(file, &house_buffer->house_type.secondary_house))
                exit_code = ERROR_READING_SEC_FIELDS;
        }
    }
    return exit_code;
}

// GENERAL: address
int read_address_general(FILE *file, char *house_address)
{
    int exit_code = EXIT_SUCCESS;
    char street[ADDRESS_STR_ITEM_SIZE + 1];
    char house[ADDRESS_STR_ITEM_SIZE + 1];
    char apartment[ADDRESS_STR_ITEM_SIZE + 1];
    char region[ADDRESS_STR_ITEM_SIZE + 1];
    char country[ADDRESS_STR_ITEM_SIZE + 1];
    char postalcode[ADDRESS_STR_ITEM_SIZE + 1];
    if (read_address_street(file, street))
        exit_code = 101;
    else if (read_address_house(file, house))
        exit_code = 102;
    else if (read_address_apartment(file, apartment))
        exit_code = 103;
    else if (read_address_region(file, region))
        exit_code = 104;
    else if (read_address_country(file, country))
        exit_code = 105;
    else if (read_address_postalcode(file, postalcode))
        exit_code = 106;
    if (!exit_code)
        sprintf(house_address, "%s %s %s %s %s %s", street, house, apartment, region, country, postalcode);
    return exit_code;
}

// GENERAL: primary fields
int read_primary_general(FILE *file, primary_type *primary_buffer) // DONE
{
    int exit_code = EXIT_SUCCESS;
    if (read_bool_interior(file, &primary_buffer->interior))
        exit_code = ERROR_READING_PRIM_FIELDS;
    return exit_code;
}

// GENERAL: secondary fields
int read_secondary_general(FILE *file, secondary_type *secondary_buffer) // DONE
{
    int exit_code = EXIT_SUCCESS;
    if (read_build_year(file, &secondary_buffer->build_year))
        exit_code = ERROR_READING_SEC_FIELDS;
    else if (read_owners_n(file, &secondary_buffer->owners_n))
        exit_code = ERROR_READING_SEC_FIELDS;
    else if (read_bool_pets(file, &secondary_buffer->pets))
        exit_code = ERROR_READING_SEC_FIELDS;
    return exit_code;
}

// PARSE: address
int read_address_street(FILE *file, char *street)
{
    int exit_code = EXIT_SUCCESS;
    char street_buffer[ADDRESS_STR_ITEM_SIZE + 1];
    if (fscanf(file, "%16s ", street_buffer) != 1)
        exit_code = EXIT_FAILURE;
    else
    {
        size_t street_buffer_len = strlen(street_buffer);
        if (!street_buffer_len || street_buffer_len > ADDRESS_STR_ITEM_SIZE)
            exit_code = EXIT_FAILURE;
        else
        {
            street_buffer[street_buffer_len] = '\0';
            strcpy(street, street_buffer);
        }
    }
    return exit_code;
}

// PARSE: address
int read_address_house(FILE *file, char *house)
{
    int exit_code = EXIT_SUCCESS;
    int house_no;
    if (fscanf(file, "%d ", &house_no) != 1)
        exit_code = EXIT_FAILURE;
    else
    {
        if (house_no < 0 || house_no > 99)
            exit_code = EXIT_FAILURE;
        else
            itos(house_no, house);
    }
    return exit_code;
}

// PARSE: address
int read_address_apartment(FILE *file, char *apartment)
{
    int exit_code = EXIT_SUCCESS;
    int apartment_no;
    if (fscanf(file, "%d ", &apartment_no) != 1)
        exit_code = EXIT_FAILURE;
    else
    {
        if (apartment_no < 0 || apartment_no > 999)
            exit_code = EXIT_FAILURE;
        else
            itos(apartment_no, apartment);
    }
    return exit_code;
}

// PARSE: address
int read_address_region(FILE *file, char *region)
{
    int exit_code = EXIT_SUCCESS;
    char region_buffer[ADDRESS_STR_ITEM_SIZE + 1];
    if (fscanf(file, "%16s ", region_buffer) != 1)
        exit_code = EXIT_FAILURE;
    else
    {
        size_t region_buffer_len = strlen(region_buffer);
        if (!region_buffer_len || region_buffer_len > ADDRESS_STR_ITEM_SIZE)
            exit_code = EXIT_FAILURE;
        else
        {
            region_buffer[region_buffer_len] = '\0';
            strcpy(region, region_buffer);
        }
    }
    return exit_code;
}

// PARSE: address
int read_address_country(FILE *file, char *country)
{
    int exit_code = EXIT_SUCCESS;
    char country_buffer[ADDRESS_STR_ITEM_SIZE + 1];
    if (fscanf(file, "%16s ", country_buffer) != 1)
        exit_code = EXIT_FAILURE;
    else
    {
        size_t country_buffer_len = strlen(country_buffer);
        if (!country_buffer_len || country_buffer_len > ADDRESS_STR_ITEM_SIZE)
            exit_code = EXIT_FAILURE;
        else
        {
            country_buffer[country_buffer_len] = '\0';
            strcpy(country, country_buffer);
        }
    }
    return exit_code;
}

// PARSE: address
int read_address_postalcode(FILE *file, char *postalcode)
{
    int exit_code = EXIT_SUCCESS;
    int postalcode_no;
    if (fscanf(file, "%d ", &postalcode_no) != 1)
        exit_code = EXIT_FAILURE;
    else
    {
        if (postalcode_no < 99999 || postalcode_no > 999999)
            exit_code = EXIT_FAILURE;
        else
            itos(postalcode_no, postalcode);
    }
    return exit_code;
}

// READ: main fields
int read_sqr_meters(FILE *file, double *sqr_meters)
{
    int exit_code = EXIT_SUCCESS;
    if (fscanf(file, "%lf ", sqr_meters) != 1)
        exit_code = EXIT_FAILURE;
    else if (*sqr_meters < 0 || *sqr_meters > 700)
        exit_code = EXIT_FAILURE;
    return exit_code;
}

// READ: main fields
int read_rooms_n(FILE *file, int *rooms_n)
{
    int exit_code = EXIT_SUCCESS;
    if (fscanf(file, "%d ", rooms_n) != 1)
        exit_code = EXIT_FAILURE;
    else if (*rooms_n <= 0 || *rooms_n > 50)
        exit_code = EXIT_FAILURE;
    return exit_code;
}

// READ: main fields
int read_sqr_meter_price(FILE *file, double *sqr_meter_price)
{
    int exit_code = EXIT_SUCCESS;
    if (fscanf(file, "%lf ", sqr_meter_price) != 1)
        exit_code = EXIT_FAILURE;
    else if (*sqr_meter_price < 0 || *sqr_meter_price > 1000000)
        exit_code = EXIT_FAILURE;
    return exit_code;
}

// READ: main fields
int read_is_primary(FILE *file, int *is_primary)
{
    int exit_code = EXIT_SUCCESS;
    if (fscanf(file, "%d ", is_primary) != 1)
        exit_code = EXIT_FAILURE;
    else if (*is_primary < 0)
        exit_code = EXIT_FAILURE;
    return exit_code;
}

// READ: secondary fields
int read_build_year(FILE *file, int *build_time) // DONE
{
    int exit_code = EXIT_SUCCESS;
    if (fscanf(file, "%d ", build_time) != 1)
        exit_code = ERROR_READING_UB;
    else if (*build_time < LL_YEAR || *build_time > RL_YEAR)
        exit_code = ERROR_YEAR_VALUE;
    return exit_code;
}

// READ: secondary fields
int read_owners_n(FILE *file, int *owners_n) // DONE
{
    int exit_code = EXIT_SUCCESS;
    if (fscanf(file, "%d ", owners_n) != 1)
        exit_code = ERROR_READING_UB;
    else if (*owners_n < 0 || *owners_n > MAX_OWNERS_AMOUNT)
        exit_code = ERROR_OWNERS_VALUE;
    return exit_code;
}

// READ: secondary fields
int read_bool_pets(FILE *file, int *pets) // DONE
{
    int exit_code = EXIT_SUCCESS;
    if (fscanf(file, "%d ", pets) != 1)
        exit_code = ERROR_READING_UB;
    else if (*pets != 1 && *pets != 0)
        exit_code = ERROR_PETS_FLAG;
    return exit_code;
}

// READ: primary fields
int read_bool_interior(FILE *file, int *interior) // DONE
{
    int exit_code = EXIT_SUCCESS;
    if (fscanf(file, "%d ", interior) != 1)
        exit_code = ERROR_READING_UB;
    else if (*interior != 1 && *interior != 0)
    {
        // printf("\tread_bool_interior got: %d\n", *interior);
        exit_code = ERROR_HOUSE_TYPE_FLAG;
    }
    // printf("\tread_bool_interior: %d\n", exit_code);
    return exit_code;
}