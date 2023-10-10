#include "helper.h"

void reverse(char *str, size_t str_len)
{
    int pstart = 0;
    int pend = str_len - 1;
    while (pstart < pend)
    {
        char temp = str[pstart];
        str[pstart] = str[pend];
        str[pend] = temp;
        pstart++;
        pend--;
    }
}

void itos(int num, char *str)
{
    int i = 0;
    if (!num)
    {
        str[i++] = '0';
        str[i] = '\0';
    }
    else
    {
        while (num != 0)
        {
            int rem = num % 10;
            str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
            num = num / 10;
        }
        str[i] = '\0';
        reverse(str, strlen(str));
    }
}

void printer(char *general_address)
{
    int i = 0;
    while (general_address[i] != '\0')
    {
        printf("%c", general_address[i]);
        i++;
    }
    printf("\n");
}

void print_record_primary(house_type *house_buffer)
{
    printf("| %-60s | %-10.2f | %-6d | %-15.2f | %-10d | %-10s | %-6s | %-4s | %-8d |\n", 
           house_buffer->address, 
           house_buffer->sqr_meters, 
           house_buffer->rooms_n, 
           house_buffer->sqr_meter_price, 
           house_buffer->is_primary, 
           "-", "-", "-",
           house_buffer->house_type.primary_house.interior);
}

void print_record_secondary(house_type *house_buffer)
{
    printf("| %-60s | %-10.2f | %-6d | %-15.2f | %-10d | %-10d | %-6d | %-4d | %-8s |\n", 
           house_buffer->address, 
           house_buffer->sqr_meters, 
           house_buffer->rooms_n, 
           house_buffer->sqr_meter_price, 
           house_buffer->is_primary, 
           house_buffer->house_type.secondary_house.build_year, 
           house_buffer->house_type.secondary_house.owners_n, 
           house_buffer->house_type.secondary_house.pets,
           "-");
}
int input_left_right_limits(double *ll, double *rl)
{
    int exit_code = EXIT_SUCCESS;
    printf("Ввод левого предела: ");
    if (scanf("%lf", ll) != 1)
        exit_code = ERROR_INPUT_LL;
    else if (*ll < 0)
        exit_code = ERROR_INPUT_LL;
    else
    {
        printf("Ввод правого предела: ");
        if (scanf("%lf", rl) != 1)
            exit_code = ERROR_INPUT_RL;
        else if (*rl < 0)
            exit_code = ERROR_INPUT_RL;
        if (*ll > *rl)
            exit_code = ERROR_INPUT_RL;
    }
    return exit_code;
}

void clear_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_house(house_type *house_buffer)
{
    if (house_buffer->is_primary)
        print_record_primary(house_buffer);
    else
        print_record_secondary(house_buffer);
}

double calc_price(double sqr_meters, double sqr_meters_price)
{
    return sqr_meters * sqr_meters_price;
}

void print_table_header(void)
{
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-60s | %-10s | %-6s | %-15s | %-10s | %-10s | %-6s | %-4s | %-4s |\n", 
           "Address", "Sq. Meters", "Rooms", "Sq. Meter Price", "Is Primary", "Build Year", "Owners", "Pets", "Interior");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void print_keys_header(void)
{
    printf("----------------------------\n");
    printf("| %-6s | %-10s |\n", 
           "Index", "Sq. Meter Price");
    printf("----------------------------\n");
}