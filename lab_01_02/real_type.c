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
            printf("real_len: %d\n", real_len);
            printf("real_string: %s\n", real_string);
        }
    }
    return exit_code;
}
/* Here we pass the base without sign.
Example: 412.321
Functionality: Checks the length and the amount of points in the base*/
int validate_real_mantissa(char *base_string, int *index) // DONE
{
    printf("Index start checker mantissa: %d\n", (*index));
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
    if (exponent_string[*index] != 'e' && exponent_string[*index] != 'E') // The number could not have exponential part
    {
        is_valid = 1;
    }
    else
    {
        int count = 0;
        (*index) = (*index) + 3; // pass the _e_ symbol.
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

int validate_real_type(char *str)
{
    int index = 0;
    int is_valid = 1;
    if (!validate_real_mantissa(str, &index))
    {
        is_valid = 0;
    }
    else
    {
        index++; // pass the space after the mantissa
        printf("Index after checking mantissa: %d\n", index);
    }
    return is_valid;
}

// PARSER
int parse_base_sign(char *str, int *index, char *base_sign)
{
    int exit_code = EXIT_SUCCESS;
    if (isdigit(str[*index]))
    {
        *base_sign = '+';
    }
    else
    {
        if (str[*index] == '+' || str[*index] == '-')
        {
            if (str[*index] == '+')
            {
                *base_sign = '+';
            }
            else if (str[*index] == '-')
            {
                *base_sign = '-';
            }
            (*index)++; // Se encontro el signo, pasmos al primer elemento de la mantissa
        }
    }
    return exit_code;
}

int parse_mantissa(char *str, int *index, char *mantissa, int *decimal_index)
{
    int exit_code = EXIT_SUCCESS;
    int mantissa_index = 0;
    *decimal_index = -1;
    while ((isdigit(str[*index]) || str[*index] == '.') && exit_code == EXIT_SUCCESS)
    {
        if (str[*index] == '.')
        {
            if (*decimal_index != -1)
            {
                exit_code = EXIT_FAILURE;
            }
            *decimal_index = mantissa_index;
        }
        else
        {
            mantissa[mantissa_index++] = str[*index];
        }
        (*index)++;
    }
    if (*decimal_index == -1)
    {
        *decimal_index = mantissa_index;
    }
    mantissa[mantissa_index] = '\0';
    return exit_code;
}

int parse_power(char *str, int *index, int *power)
{
    int exit_code = EXIT_SUCCESS;
    if (!(str[*index] == 'e' || str[*index] == 'E')) // No hay exponencial, por lo tanto la potencia es 0
    {
        *power = 0;
        exit_code = EXIT_SUCCESS;
    }
    else // En el caso the que si exista E o e
    {
        (*index)++; // Pasamos a los numeros de la potencia
        char power_buffer[6]; // 5 digitos + \0
        int power_index = 0; // Para recorrer la string que representa la potencia
        if (str[*index] == '+' || str[*index] == '-')
        {
            (*index)++;
        }
        while (isdigit(str[*index]))
        {
            power_buffer[power_index++] = str[*index];
            (*index)++;
        }
        power_buffer[power_index] = '\0';
        *power = atoi(power_buffer);
    }
    return exit_code;
}

int parse_number(char *str, real_type *number_buffer)
{
    int exit_code = EXIT_SUCCESS;
    int index = 0;
    if (parse_base_sign(str, &index, &number_buffer->base_sign) != EXIT_SUCCESS)
    {
        exit_code = EXIT_FAILURE;
    }
    else if (parse_mantissa(str, &index, number_buffer->mantissa, &number_buffer->decimal_index) != EXIT_SUCCESS)
    {
        exit_code = EXIT_FAILURE;
    }
    else if (parse_power(str, &index, &number_buffer->power) != EXIT_SUCCESS)
    {
        exit_code = EXIT_FAILURE;
    }
    else if (str[index] != '\0')
    {
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
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