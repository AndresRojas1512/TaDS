#include "main.h"
// ===================   MACROS   =================================
#define STANDART_NUM_LEN 49
#define MAX_POWER_SIZE 5
#define MAX_MANTISSA_SIZE 40
#define ERROR_RAW_INPUT 100
#define ERROR_EMPTY_STRING 101
#define ERROR_OVERFLOW 102
#define SPECIAL_SYMBOLS_OVERFLOW 103

int main()
{
    int exit_code = EXIT_SUCCESS;
    char real_string[MAX_REAL_LEN];
    puts("Enter the real_string:");
    puts("Format: +m.n e +k");
    if (validate_real_string(real_string))
    {
        exit_code = 103;
    }
    else
    {
        if (!validate_real_type(real_string))
        {
            puts("Error in mantissa");
        }
        else
        {
            puts("Correct mantissa");
        }
    }
    return exit_code;
}

// ===================   ALGORITHM   =================================
// void reverse_string(char *str, int len)
// {
//     int start = 0;
//     int end = len - 1;
//     while (start < len)
//     {
//         char temp = str[start];
//         str[start] = str[end];
//         str[end] = temp;
//         start++;
//         end--;
//     }
// }

// char *multiply_strings(char *num_01, char *num_02)
// {
//     int len_01 = strlen(num_01);
//     int len_02 = strlen(num_02);
//     int gen_len = len_01 + len_02;
//     int *result_number = (int *)malloc(gen_len * sizeof(int));
//     for (int i = 0; i < gen_len; i++)
//     {
//         result_number[i] = 0;
//     }
//     for (int i = len_01 - 1; i >= 0; i--)
//     {
//         for (int j = len_02 - 1; i >= 0; j--)
//         {
//             result_number[i + j + 1] += ((num_01[i] - '0') * (num_02[j] - '0'));
//             result_number[i + j] += result_number[i + j + 1] / 10;
//             result_number[i + j + 1] %= 10;
//         }
//     }
//     int i = 0;
//     while (i < gen_len && result_number[i] == 0)
//     {
//         i++;
//     }
//     char *result_string = (char *)malloc((gen_len + 1) * sizeof(char));
//     int idx = 0;
//     while (i < gen_len)
//     {
//         result_string[idx++] = result_number[i];
//         i++;
//     }
//     result_string[idx] = '\0';
//     free(result_number);
//     if (strlen(result_string) == 0)
//     {
//         strcpy(result_string, "0");
//     }
//     return result_string;
// }
