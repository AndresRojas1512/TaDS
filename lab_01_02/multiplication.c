#include "multiplication.h"

int count_digits(int value);

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

result_type multiply_real_numbers(real_type num1, real_type num2)
{
    // Calculate base sign
    char sign = '+';
    if (num1.base_sign != num2.base_sign) {
        sign = '-';
    }
    // Calculate resultant mantissa
    char* multiplicationResult = multiply_strings(num1.mantissa, num2.mantissa);
    // Calculate resultant power
    char *endptr_01;
    double num_01_mantissa_conv = strtod(num1.mantissa, &endptr_01);
    while (num_01_mantissa_conv > 10)
    {
        num_01_mantissa_conv /= 10.0;
    }
    char *endptr_02;
    double num_02_mantissa_conv = strtod(num2.mantissa, &endptr_02);
    while (num_02_mantissa_conv > 10)
    {
        num_02_mantissa_conv /= 10.0;
    }
    int temp_power = num1.power + num2.power;
    int final_power = ((num_01_mantissa_conv * num_02_mantissa_conv) <  10.0) ? temp_power - 1 : temp_power;
    // Parse the result
    result_type result;
    sprintf(result.mantissa, "%s", multiplicationResult);
    result.base_sign = sign;
    result.decimal_point_index = 0;
    result.power = final_power;
    // Free used memory
    free(multiplicationResult);
    return result;
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