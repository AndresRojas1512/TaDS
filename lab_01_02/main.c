#include "main.h"

int main()
{
    // Create types
    char number_input_01[MAX_REAL_LEN + 1];
    char number_input_02[MAX_REAL_LEN + 1];
    real_type number_01;
    real_type number_02;
    real_type normalized_number_01;
    real_type normalized_number_02;
    result_type result;
    // UI
    puts("Enter two real numbers:");
    puts("Format: +m.n e +k\n");
    printf("--> ");
    if (validate_real_string(number_input_01))
    {
        puts("Error inputing 1st number");
        return 110;
    }
    printf("--> ");
    if (validate_real_string(number_input_02))
    {
        puts("Error inputing 2st number");
        return 110;
    }
    if (!validate_real_type(number_input_01) || !validate_real_type(number_input_02))
    {
        puts("the numbers do not are in the correct format");
        return 111;
    }
    if (parse_number(number_input_01, &number_01) || parse_number(number_input_02, &number_02))
    {
        puts("Error parsing. One of the numbers cannot be parsed");
        return 112;
    }
    puts("PARSED SUCCESSFULLY FINISHED!");
    puts("Here are the parsed numbers:\n");
    puts("\n\tNumber 1:\n");
    print_real_struct(&number_01);
    puts("\n\tNumber 2:\n");
    print_real_struct(&number_02);
    puts("\n\tNormalized Number 1:\n");
    normalize(&number_01, &normalized_number_01);
    print_real_struct(&normalized_number_01);
    puts("\n\tNormalized Number 2:\n");
    normalize(&number_02, &normalized_number_02);
    print_real_struct(&normalized_number_02);
    puts("Numbers normalized. Initializing multiplication");
    result = multiply_real_numbers(normalized_number_01, normalized_number_02);
    puts("\n\tMultiplicatin Result:\n");
    print_result_fields(&result);
    puts("\nSUCCESSFUL!\n");
    return 0;
}
