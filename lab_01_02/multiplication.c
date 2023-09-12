#include "multiplication.h"

int count_digits(int value);
void convert_to_format(char *number, char *result);
int count_digits_after_dec_point(char *formated_num);
int parse_mantissa_in_power(char *str, char *parse_formated_number);
void insert_decimal_point(int move_n, char *input, char *answer_multiplication);
int save_number_before_decpoint(char *multiplication_anwer);

void reverse_str(char* str, int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* multiply_strings(char num1[], char num2[])
{
    int n1 = strlen(num1);
    int n2 = strlen(num2);
    char *result = (char *)calloc(n1 + n2 + 1, sizeof(char));

    for (int i = 0; i < n1 + n2; i++) {
        result[i] = '0';
    }
    result[n1 + n2] = '\0';

    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = n2 - 1; j >= 0; j--) {
            int temp = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0') + carry;
            carry = temp / 10;
            result[i + j + 1] = (temp % 10) + '0';
        }
        result[i] += carry;
    }

    // Removing leading 0's
    int index = 0;
    while (result[index] == '0' && index < n1 + n2 - 1) {
        index++;
    }
    memmove(result, result + index, n1 + n2 - index + 1);

    return result;
}

void convert_to_format(char *number, char *result)
{
    int lenght = strlen(number);
    if (lenght == 1)
    {
        result[0] = number[0];
        result[1] = '.';
        result[2] = '0';
        result[3] = '\0';
        
    }
    else
    {
        result[0] = number[0];
        result[1] = '.';
        for (int i = 1; i < lenght; i++)
        {
            result[i + 1] = number[i];
        }
        result[lenght + 1] = '\0';
    }
}

int count_digits_after_dec_point(char *formated_num)
{
    int count = 0;
    int i = 2;
    // Find the index of the point
    while (formated_num[i] != '\0')
    {
        count++;
        i++;
    }
    return count;
}

int parse_mantissa_in_power(char *str, char *parse_formated_number)
{
    int index = 0;
    int exit_code = EXIT_SUCCESS;
    int mantissa_index = 0;
    int buffer_decimal_index = -1;
    char buffer_mantissa[40 + 1];
    while ((isdigit(str[index]) || str[index] == '.') && !exit_code)
    {
        if (str[index] == '.')
        {
            if (buffer_decimal_index != -1)
            {
                exit_code = EXIT_FAILURE;
            }
            buffer_decimal_index = mantissa_index;
        }
        else
        {
            buffer_mantissa[mantissa_index++] = str[index];
        }
        (index)++;
    }
    if (buffer_decimal_index == -1)
    {
        buffer_decimal_index = mantissa_index;
    }
    buffer_mantissa[mantissa_index] = '\0';
    // Copy into the string
    strcpy(parse_formated_number, buffer_mantissa);
    return exit_code;
}

void insert_decimal_point(int move_n, char *input, char *answer_multiplication)
{
    int len = strlen(input);
    printf("idp: %d\n", len);
    printf("idp move_n: %d\n", move_n);
    int before_point_n = len - move_n;
    char buffer_output[40 + 2]; // To handle the dec point and \0
    int idx_input = 0;
    int idx_buffer = 0;
    while (before_point_n)
    {
        buffer_output[idx_buffer] = input[idx_input];
        before_point_n--;
        idx_buffer++;
        idx_input++;
    }
    buffer_output[idx_buffer] = '.';
    idx_buffer++;
    while (move_n)
    {
        buffer_output[idx_buffer] = input[idx_input];
        move_n--;
        idx_buffer++;
        idx_input++;
    }
    buffer_output[idx_buffer + 1] = '\0';
    strcpy(answer_multiplication, buffer_output);
}

int save_number_before_decpoint(char *multiplication_anwer)
{
    char buffer[41];
    int i = 0;
    while (multiplication_anwer[i] != '.')
    {
        buffer[i] = multiplication_anwer[i];
        i++;
    }
    buffer[i] = '\0';
    char *endptr;
    int value = strtol(buffer, &endptr, 10);
    return value;
}

int multiply_real_numbers(real_type num1, real_type num2, result_type *result)
{
    // Create buffers
    char mantissa_wpoint_01[42]; // Decimal point in index 1 (num1)
    char mantissa_wpoint_02[42]; // Decimal point in index 1 (num2)
    char parsed_mantissa_01[42]; // Get the new mantissa after adding point (num1)
    char parsed_mantissa_02[42]; // Get the new mantissa after adding point (num2)
    char answer_multiplication[42]; // Multiplication with the decimal point
    // Calculate base sign
    char sign = '+';
    if (num1.base_sign != num2.base_sign) {
        sign = '-';
    }
    // Add the decimal point to the mantissa
    convert_to_format(num1.mantissa, mantissa_wpoint_01);
    convert_to_format(num2.mantissa, mantissa_wpoint_02);
    // Count digits after the dec point of each converted new mantissa
    int count_01 = count_digits_after_dec_point(mantissa_wpoint_01);
    int count_02 = count_digits_after_dec_point(mantissa_wpoint_02);
    int move_n = count_01 + count_02;
    // Now to multiply we have to remove the points of the new mantissas
    if (parse_mantissa_in_power(mantissa_wpoint_01, parsed_mantissa_01))
    {
        return 101;
    }
    if (parse_mantissa_in_power(mantissa_wpoint_02, parsed_mantissa_02))
    {
        return 102;
    }
    // Now with the new mantissas parsed we multiply them
    char *mult_result = (char *)malloc(42 * sizeof(char));
    mult_result = multiply_strings(parsed_mantissa_01, parsed_mantissa_02);
    // According to move_n, insert the point in the mult_result of the new mantissas
    insert_decimal_point(move_n, mult_result, answer_multiplication);
    // Save the number before the decimal
    int number = save_number_before_decpoint(answer_multiplication);
    // Calculate resultant power
    // char *endptr_01;
    // double num_01_mantissa_conv = strtod(num1.mantissa, &endptr_01);
    // while (num_01_mantissa_conv > 10)
    // {
    //     num_01_mantissa_conv /= 10.0;
    // }
    // char *endptr_02;
    // double num_02_mantissa_conv = strtod(num2.mantissa, &endptr_02);
    // while (num_02_mantissa_conv > 10)
    // {
    //     num_02_mantissa_conv /= 10.0;
    // }
    int temp_power = num1.power + num2.power;
    int final_power = (number <  10) ? temp_power - 1 : temp_power;
    // Parse the result
    sprintf(result->mantissa, "%s", mult_result);
    result->base_sign = sign;
    result->decimal_point_index = 0;
    result->power = final_power;
    // Free used memory
    free(mult_result);
    return 0;
}

void print_result_fields(result_type *result)
{
    printf("Mantissa: %s\n", result->mantissa);
    printf("Base_sign: %c\n", result->base_sign);
    printf("Decimal_point_index: %d\n", result->decimal_point_index);
    printf("Power: %d\n", result->power);
}

int count_digits(int value)
{
    int count = 0;
    while (value != 0)
    {
        count++;
        value /= 10;
    }
    return count;
}