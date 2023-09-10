#include "real_type.h"

/*
Return: exit_code
*/
int validate_real_string(char *real_string) // DONE
{
    int exit_code = EXIT_SUCCESS;
    char buffer[MAX_REAL_LEN + 2];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        exit_code = 100;
    }
    else
    {
        int real_len = strlen(buffer);
        if (real_len && buffer[real_len - 1] == '\n')
        {
            buffer[real_len - 1] = '\0';
        }
        if (!real_len || real_len > MAX_REAL_LEN)
        {
            exit_code = 101;
        }
        else
        {
            strcpy(real_string, buffer);
            // printf("real_len: %d\n", real_len);
            // printf("real_string: %s\n", real_string);
        }
    }
    return exit_code;
}
/* Here we pass the base without sign.
Example: 412.321
Functionality: Checks the length and the amount of points in the base*/
int validate_real_mantissa(char *base_string, int *index) // DONE
{
    int is_valid = 1;
    int count = 0;
    if (base_string[*index] == '+' || base_string[*index] == '-')
    {
        (*index)++;
    }
    while (isdigit(base_string[*index]))
    {
        (*index)++;
        count++;
    }
    if (base_string[*index] == '.')
    {
        (*index)++;
        while (isdigit(base_string[*index]))
        {
            (*index)++;
            count++;
        }
    }
    if (!count || count > MAX_REAL_MANTISSA_LEN)
    {
        is_valid = 0;
    }
    return is_valid;
}

int validate_real_exponent(char *exponent_string, int *index) // DONE
{
    int is_valid = 1;
    (*index)++; // Skipp the space after the mantissa
    if (exponent_string[*index] != 'e' && exponent_string[*index] != 'E') // The number could not have exponential part
    {
        is_valid = 1; // The number has no exponent, but still correct
        (*index)--;
    }
    else // That means that there is e or E
    {
        int count = 0;
        (*index) = (*index) + 2; // pass the e_ symbols.
        if (exponent_string[*index] == '+' || exponent_string[*index] == '-') // Check for the optional +/- symbol
        {
            (*index)++; // pass the symbol sign symbol
        }
        while (isdigit(exponent_string[*index]))
        {
            (*index)++;
            count++;
        }
        if (!count || count > 5)
        {
            is_valid = 0;
        }
    }
    return is_valid;
}

int validate_real_type(char *str) // DONE
{
    int index = 0;
    int is_valid = 1;
    if (!validate_real_mantissa(str, &index))
    {
        is_valid = 0;
    }
    else
    {
        if (!validate_real_exponent(str, &index))
        {
            is_valid = 0;
        }
    }
    if (str[index] == '\0')
    {
        is_valid = 1;
    }
    else
    {
        is_valid = 0;
    }
    return is_valid;
}

/*
In these functions is guaranteed that the inputed number is correct
*/
int parse_base_sign(char *str, int *index, real_type *real_number) // DONE
{
    char buffer_sign = '+';
    int exit_code = EXIT_SUCCESS;
    if (isdigit(str[*index]))
    {
        buffer_sign = '+';
    }
    else
    {
        if (str[*index] == '+' || str[*index] == '-')
        {
            if (str[*index] == '+')
            {
                buffer_sign = '+';
            }
            else if (str[*index] == '-')
            {
                buffer_sign = '-';
            }
            (*index)++; // Se encontro el signo, pasmos al primer elemento de la mantissa
        }
    }
    real_number->base_sign = buffer_sign;
    return exit_code;
}

/*
The index will be in the first postition of the numerical value
*/
int parse_mantissa(char *str, int *index, real_type *real_number) // DONE
{
    int exit_code = EXIT_SUCCESS;
    int mantissa_index = 0;
    int buffer_decimal_index = -1;
    char buffer_mantissa[MAX_REAL_MANTISSA_LEN + 1];
    while ((isdigit(str[*index]) || str[*index] == '.') && !exit_code)
    {
        if (str[*index] == '.')
        {
            if (buffer_decimal_index != -1)
            {
                exit_code = EXIT_FAILURE;
            }
            buffer_decimal_index = mantissa_index;
        }
        else
        {
            buffer_mantissa[mantissa_index++] = str[*index];
        }
        (*index)++;
    }
    if (buffer_decimal_index == -1)
    {
        buffer_decimal_index = mantissa_index;
    }
    buffer_mantissa[mantissa_index] = '\0';
    // Copy into the struct
    real_number->decimal_index = buffer_decimal_index;
    strcpy(real_number->mantissa, buffer_mantissa);
    return exit_code;
}

int parse_power(char *str, int *index, real_type *real_number)
{
    int exit_code = EXIT_SUCCESS;
    int buffer_power_int = 0;
    if (str[*index] == '\0') // No exponent. After checking the mantissa we should be in the index after the last number of the mantissa
    {
        exit_code = EXIT_SUCCESS;
        printf("The index when no E: %d\n", (*index));
        real_number->power = buffer_power_int; // Power == 0       
    }
    else // There is power
    {
        (*index) += 3; // Pasamos al primer numero de la potencia o al signo
        printf("Index of the first number of the power: %d\n", (*index));
        char buffer_power_str[6]; // 5 digitos + \0
        int power_index = 0; // Para recorrer la string que representa la potencia
        while (isdigit(str[(*index)]) || str[(*index)] == '+' || str[(*index)] == '-')
        {
            buffer_power_str[power_index++] = str[*index];
            (*index)++;
        }
        buffer_power_str[power_index] = '\0';

        char *endptr;
        buffer_power_int = strtol(buffer_power_str, &endptr, 10);
        real_number->power = buffer_power_int;
        printf("parse_power result: %d\n", buffer_power_int);
    }
    return exit_code;
}

int parse_number(char *str, real_type *real_number)
{
    int exit_code = EXIT_SUCCESS;
    int index = 0;
    if (parse_base_sign(str, &index, real_number))
    {
        exit_code = 110;
    }
    else if (parse_mantissa(str, &index, real_number))
    {
        exit_code = 111;
    }
    else if (parse_power(str, &index, real_number))
    {
        exit_code = 112;
    }
    else if (str[index] != '\0')
    {
        exit_code = 113;
    }
    return exit_code;
}

void print_real_struct(real_type *real_number)
{
    printf("Mantissa[string]: %s\n", real_number->mantissa);
    printf("Sign[char]: %c\n", real_number->base_sign);
    printf("Decimal Index[int]: %d\n", real_number->decimal_index);
    printf("Power[int]: %d\n", real_number->power);
}

void convert_scinot(const real_type *input, real_type *output)
{
    int shift, i, j;
    output->base_sign = input->base_sign;
    if (input->decimal_index == 0)
    {
        shift = 0;
        while (input->mantissa[shift] == '0' && shift < 40)
        {
            shift++;
        }
    }
    else
    {
        shift = input->decimal_index - 1;
    }

    output->power = input->power + shift;
    output->decimal_index = 1;
    for (i = shift, j = 0; i < 40; i++, j++)
    {
        output->mantissa[j] = input->mantissa[i];
    }
    for (; j < 40; j++)
    {
        output->mantissa[j] = '0';
    }
    output->mantissa[40] = '\0';
}