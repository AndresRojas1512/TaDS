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
    // UI
    user_interface();
    prompt_real_number();
    if (validate_real_string(number_input_01) || !validate_real_type(number_input_01))
    {
        puts("Error: Inputing real number");
        return 110;
    }
    prompt_natural_number();
    if (validate_real_string(number_input_02) || !validate_real_type(number_input_02))
    {
        puts("Error: Inputing natural number");
        return 111;
    }
    if (parse_number(number_input_01, &number_01) || parse_number(number_input_02, &number_02))
    {
        puts("Error parsing. The numbers cannot be parsed");
        return 112;
    }
    normalize(&number_01, &normalized_number_01);
    normalize(&number_02, &normalized_number_02);
    result_type result;
    if (multiply_real_numbers(normalized_number_01, normalized_number_02, &result))
        return 200;
    puts("\n\tMultiplicatin Result:\n");
    print_result_fields(&result);
    puts("\nSUCCESSFUL!\n");
    return 0;
}
