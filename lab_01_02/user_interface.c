#include "user_interface.h"

void user_interface(void)
{
    printf("\t============ Long Arithmetic ============\t\n\n");
    puts("Valid Format: +m.n e +k (the signs are optional)\n");
}

void prompt_real_number(void)
{
    printf("Enter the real number: \n");
    printf("   |--------|---------|---------|---------|---------|---------|\n");
    printf("   1-------10--------20--------30--------40--------50--------60\n");
    printf("-> ");
}

void prompt_natural_number(void)
{
    printf("Enter the natural number: \n");
    printf("   |--------|---------|---------|\n");
    printf("   1-------10--------20--------30\n");
    printf("-> ");
}