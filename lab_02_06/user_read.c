#include "user_read.h"

// CASE 8: Append Data
int append_house(house_type *house_buffer, house_type *house_table, int *house_table_len)
{
    if (*house_table_len == 500)
    {
        printf("\tERROR %d: Cannot add. Table overflow\n", ERROR_CANNOT_ADD_OVERFLOW);
        return ERROR_CANNOT_ADD_OVERFLOW;
    }
    if (input_address_general(house_buffer->address))
        return ERROR_INPUT_ADDRESS;
    if (input_sqr_meters(&house_buffer->sqr_meters))
        return ERROR_READING_SQR_METERS;
    if (input_rooms_n(&house_buffer->rooms_n))
        return ERROR_READING_ROOMS_N;
    if (input_sqr_meter_price(&house_buffer->sqr_meter_price))
        return ERROR_READING_SQR_METER_PRICE;
    if (input_is_primary(&house_buffer->is_primary))
        return ERROR_READING_HOUSE_TYPE;
    if (house_buffer->is_primary)
    {
        if (input_primary_general(&house_buffer->house_type.primary_house))
            return ERROR_READING_PRIM_FIELDS;
    }
    else if (!(house_buffer->is_primary))
    {
        if (input_secondary_general(&house_buffer->house_type.secondary_house))
            return ERROR_READING_SEC_FIELDS;
    }
    house_table[(*house_table_len)++] = *house_buffer; 
    return EXIT_SUCCESS;
}
int input_address_general(char *house_address)
{
    char street[ADDRESS_STR_ITEM_SIZE + 1];
    int house;
    int apartment;
    char region[ADDRESS_STR_ITEM_SIZE + 1];
    char country[ADDRESS_STR_ITEM_SIZE + 1];
    int postalcode;
    printf("Улица (до 15 символов): ");
    if (input_string(street))
        return ERROR_INPUT_STREET;
    printf("Номер дома (0 - 100): ");
    if (input_house(&house))
        return ERROR_INPUT_HOUSE_NO;
    printf("Номер квартиры (0 - 1000): ");
    if (input_apartment(&apartment))
        return ERROR_INPUT_APARTMENT_NO;
    printf("Область (до 15 символов): ");
    if (input_string(region))
        return ERROR_INPUT_REGION;
    printf("Страна (до 15 символов): ");
    if (input_string(country))
        return ERROR_INPUT_COUNTRY;
    printf("Почтовый индекс (6 цифр): ");
    if (input_postalcode(&postalcode))
        return ERROR_INPUT_POSTALCODE;
    sprintf(house_address, "%s %d %d %s %s %d", street, house, apartment, region, country, postalcode);
    return EXIT_SUCCESS;
}

int input_secondary_general(secondary_type *secondary_buffer)
{
    int exit_code = EXIT_SUCCESS;
    if (input_build_year(&secondary_buffer->build_year))
        exit_code = ERROR_READING_SEC_FIELDS;
    else if (input_owners_n(&secondary_buffer->owners_n))
        exit_code = ERROR_READING_SEC_FIELDS;
    else if (input_bool_pets(&secondary_buffer->pets))
        exit_code = ERROR_READING_SEC_FIELDS;
    return exit_code;
}

int input_primary_general(primary_type *primary_buffer)
{
    int exit_code = EXIT_SUCCESS;
    if (input_bool_interior(&primary_buffer->interior))
        exit_code = ERROR_READING_PRIM_FIELDS;
    return exit_code;
}

int input_string(char *string)
{
    int exit_code = EXIT_SUCCESS;
    char buffer[ADDRESS_STR_ITEM_SIZE + 2];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        exit_code = ERROR_READING_UB;
    else
    {
        int buffer_len = strlen(buffer);
        if (buffer[0] == '\n')
            exit_code = ERROR_INPUT_EMPTY_READ;
        else if (buffer_len == (ADDRESS_STR_ITEM_SIZE + 1) && buffer[buffer_len - 1] != '\n')
            exit_code = ERROR_INPUT_OVERFLOW;
        else
        {
            buffer[buffer_len - 1] = '\0';
            strcpy(string, buffer);
        }
    }
    return exit_code;
}

int input_house(int *house)
{
    int exit_code = EXIT_SUCCESS;
    if (scanf("%d", house) != 1)
        exit_code = ERROR_READING_UB;
    else if (*house < 0 || *house > 99)
        exit_code = ERROR_INPUT_HOUSE_NO;
    clear_buffer();
    return exit_code;
}

int input_apartment(int *apartment)
{
    int exit_code = EXIT_SUCCESS;
    if (scanf("%d", apartment) != 1)
        exit_code = ERROR_READING_UB;
    else if (*apartment < 0 || *apartment > 999)
        exit_code = ERROR_INPUT_APARTMENT_NO;
    clear_buffer();
    return exit_code;
}

int input_postalcode(int *postal_code)
{
    int exit_code = EXIT_SUCCESS;
    if (scanf("%d", postal_code) != 1)
        exit_code = ERROR_READING_UB;
    else if (*postal_code < 99999 || *postal_code > 999999)
        exit_code = ERROR_INPUT_POSTALCODE;
    clear_buffer();
    return exit_code;
}

// MAIN FIELDS
int input_sqr_meters(double *sqr_meters)
{
    printf("Кватратные метров (0 - 700): ");
    int exit_code = EXIT_SUCCESS;
    if (scanf("%lf", sqr_meters) != 1)
        exit_code = ERROR_READING_UB;
    else if (*sqr_meters < 0 || *sqr_meters > 700)
        exit_code = ERROR_READING_SQR_METERS;
    clear_buffer();
    return exit_code;
}

int input_rooms_n(int *rooms_n)
{
    printf("Количество комнат (0 - 50): ");
    int exit_code = EXIT_SUCCESS;
    if (scanf("%d", rooms_n) != 1)
        exit_code = ERROR_READING_UB;
    else if (*rooms_n <= 0 || *rooms_n > 50)
        exit_code = ERROR_READING_ROOMS_N;
    clear_buffer();
    return exit_code;
}

int input_sqr_meter_price(double *sqr_meter_price)
{
    printf("Цена кватртного метра (0 - 1000000): ");
    int exit_code = EXIT_SUCCESS;
    if (scanf("%lf", sqr_meter_price) != 1)
        exit_code = ERROR_READING_UB;
    else if (*sqr_meter_price < 0 || *sqr_meter_price > 1000000)
        exit_code = ERROR_READING_SQR_METER_PRICE;
    clear_buffer();
    return exit_code;
}

int input_is_primary(int *is_primary)
{
    printf("Тип жилья (1 - первичное, 0 - вторичное) ");
    int exit_code = EXIT_SUCCESS;
    if (scanf("%d", is_primary) != 1)
        exit_code = ERROR_READING_UB;
    else if (*is_primary != 1 && *is_primary != 0)
        exit_code = ERROR_READING_HOUSE_TYPE;
    clear_buffer();
    return exit_code;
}

// Secondary Fields
int input_build_year(int *build_time)
{
    printf("Год постройки (1500 - 2070): ");
    int exit_code = EXIT_SUCCESS;
    if (scanf("%d", build_time) != 1)
        exit_code = ERROR_READING_UB;
    else if (*build_time < LL_YEAR || *build_time > RL_YEAR)
        exit_code = ERROR_YEAR_VALUE;
    clear_buffer();
    return exit_code;
}

int input_owners_n(int *owners_n)
{
    printf("Количество предыдущих собстенников (0 - 50): ");
    int exit_code = EXIT_SUCCESS;
    if (scanf("%d", owners_n) != 1)
        exit_code = ERROR_READING_UB;
    else if (*owners_n < 0 || *owners_n > MAX_OWNERS_AMOUNT)
        exit_code = ERROR_OWNERS_VALUE;
    clear_buffer();
    return exit_code;
}

int input_bool_pets(int *pets)
{
    printf("Были ли животные (1 - да, 0 - нет): ");
    int exit_code = EXIT_SUCCESS;
    if (scanf("%d", pets) != 1)
        exit_code = ERROR_READING_UB;
    else if (*pets != 1 && *pets != 0)
        exit_code = ERROR_PETS_FLAG;
    clear_buffer();
    return exit_code;
}

int input_bool_interior(int *interior)
{
    printf("С отделкойя (1 - да, 0 - нет): ");
    int exit_code = EXIT_SUCCESS;
    if (scanf("%d", interior) != 1)
        exit_code = ERROR_READING_UB;
    else if (*interior != 1 && *interior != 0)
        exit_code = ERROR_HOUSE_TYPE_FLAG;
    clear_buffer();
    return exit_code;
}