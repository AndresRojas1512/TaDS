#define _POSIX_C_SOURCE 199309L
#include "complexity_analysis.h"

int complexity_analysis(void)
{
    int exit_code = EXIT_SUCCESS;
    char string_array[WORDS_MAX_AMOUNT_CA][STRING_MAX_SIZE_CA];
    char string_array_sorted[WORDS_MAX_AMOUNT_CA][STRING_MAX_SIZE_CA];
    int string_array_len = 0;
    int string_array_sorted_len = 0;

    double data_time_tree[DIRECTORIES_N][PERCENTAGES_N]; // Time deletion from tree
    double data_time_file[DIRECTORIES_N][PERCENTAGES_N]; // Time deletion from file
    double data_time_find_balanced[DIRECTORIES_N]; // Time find in balanced tree
    double data_time_find_unbalanced[DIRECTORIES_N]; // Time find in unbalanced tree
    double data_time_find_rightmost[DIRECTORIES_N]; // Time find in rightmost tree

    int directories[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int percentages[] = {25, 50, 75, 100};
    int times_n = 10;

    for (int i = 0; i < DIRECTORIES_N; i++)
    {
        int dir_current = directories[i];
        printf("\nКоличество слов: %d\n", directories[i]);
        for (int j = 0; j < PERCENTAGES_N; j++)
        {
            node_t *root = NULL;
            node_t *root_balanced = NULL;
            node_t *root_rightmost = NULL;

            node_t *node_found = NULL;
            
            /*
            Read the words and fill the array
            */
            char filename_in[FILEPATH_N];
            sprintf(filename_in, "data/%d/%d.txt", directories[i], percentages[j]);
            printf("\tПроцент удаления: %d\n", percentages[j]);
            if (file_read_data(filename_in, string_array, &string_array_len))
                return ERROR_FILE_READ_DATA;
            /*
            Fill the BST
            */
            exit_code = bst_import(&root, string_array, string_array_len);
            if (exit_code)
                return EXIT_FAILURE;
            int height = bst_find_height(root);
            printf("\t\tВысота дерева: %d\n", height);

            /*
            Fill the string array sorted
            */
            string_array_sorted_len = 0;
            bst_store_inorder(root, string_array_sorted, &string_array_sorted_len);
            // printf("String_array_sorted len: %d\n", string_array_sorted_len);

            /*
            Create the balanced BST
            */
            root_balanced = create_balanced_bst_copy(root);
            if (!root_balanced)
            {
                printf("Error tree balanced copy.\n");
                return EXIT_FAILURE;
            }
            int height_balanced = bst_find_height(root_balanced);
            printf("\t\tВысота сбалансированого дерева: %d\n", height_balanced);

            /*
            Create the rightmost BST
            */
            bst_import(&root_rightmost, string_array_sorted, string_array_sorted_len);
            if (!root_rightmost)
            {
                printf("Error tree rightmost copy.\n");
                return EXIT_FAILURE;
            }
            int height_rightmost = bst_find_height(root_rightmost);
            printf("\t\tВысота правосторонного дерева: %d\n", height_rightmost);
            
            /*
            Tree Words Deletion
            */
            unsigned long long time_tree = 0;
            for (int k = 0; k < times_n; k++)
            {
                bst_free(root);
                root = NULL;
                exit_code = bst_import(&root, string_array, string_array_len);
                if (exit_code)
                    return EXIT_FAILURE;
                
                int count = bst_node_count(root);
                // printf("Iter : %d, Count: %d\n", k, count);
                unsigned long long beg_tree = microseconds_now();
                root = bst_delete_by_letter(root, 'm');
                unsigned long long end_tree = microseconds_now();
                time_tree += end_tree - beg_tree;
                // printf("Iter: %d, Time: %lld\n", k, end_tree - beg_tree);
            }
            data_time_tree[i][j] = time_tree / times_n;

            /*
            File Words Deletion
            */
            unsigned long long time_file = 0;
            for (int k = 0; k < times_n; k++)
            {
                int count = 0;
                unsigned long long beg_file = microseconds_now();
                exit_code = file_delete_words(filename_in, "file_out.txt", 'm', &count);
                unsigned long long end_file = microseconds_now();
                time_file += end_file - beg_file;
            }
            data_time_file[i][j] = time_file / times_n;

            /*
            Balanced Tree find word
            */
            char *word_to_find = string_array_sorted[(WORDS_MAX_AMOUNT_CA * 3) / 4];
            unsigned long long time_find_balanced = 0;
            for (int k = 0; k < times_n; k++)
            {
                // printf("Iter: %d, Nodes: %d\n", k, bst_node_count(root_balanced));
                unsigned long long beg_balanced = microseconds_now();
                bst_find(root_balanced, word_to_find);
                unsigned long long end_balanced = microseconds_now();
                time_find_balanced += (end_balanced - beg_balanced);
                // printf("Iter: %d, Time: %lld\n", k, end_balanced - beg_balanced);
            }
            data_time_find_balanced[i] = time_find_balanced / times_n;
            /*
            Unbalanced Tree find word // TODO
            */
            bst_free(root);
            root = NULL;
            exit_code = bst_import(&root, string_array, string_array_len);
            if (exit_code)
            {
                printf("Error unbalanced time init.\n");
                return EXIT_FAILURE;
            }
            unsigned long long time_find_unbalanced = 0;
            for (int k = 0; k < times_n; k++)
            {
                unsigned long long beg_unbalanced = microseconds_now();
                bst_find(root, word_to_find);
                unsigned long long end_unbalanced = microseconds_now();
                time_find_unbalanced += (end_unbalanced - beg_unbalanced);
            }
            data_time_find_unbalanced[i] = time_find_unbalanced / times_n;
            /*
            Right Most find word
            */
            unsigned long long time_find_rightmost = 0;
            for (int k = 0; k < times_n; k++)
            {
                unsigned long long beg_rightmost = microseconds_now();
                bst_find(root_rightmost, word_to_find);
                unsigned long long end_rightmost = microseconds_now();
                time_find_rightmost += (end_rightmost - beg_rightmost);
                // printf("Iter: %d, Time: %lld\n", k, end_rightmost - beg_rightmost);
            }
            data_time_find_rightmost[i] = time_find_rightmost / times_n;

            printf("\t\tвремя удаления на БДП (микросекунды): %f\n", data_time_tree[i][j]);
            printf("\t\tВремя удаления в файле (микросекунды): %f\n", data_time_file[i][j]);
            printf("\t\tВремя поиска на сбалансированном БДП (микросекунды): %f\n", data_time_find_balanced[i]);
            printf("\t\tВремя поиска на правосторонном БДП (микросекунды): %f\n", data_time_find_rightmost[i]);
            printf("\t\tВремя поиска на несбалансированном БДП (микросекунды): %f\n", data_time_find_unbalanced[i]);

        }
    }
    return EXIT_SUCCESS;
}

/*
Read data from files
*/
int file_read_data(char *filename_in, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int *string_array_len)
{
    int exit_code = EXIT_SUCCESS;
    FILE *file = fopen(filename_in, "r");
    if (!file)
        exit_code = EXIT_FAILURE;
    else
    {
        exit_code = file_read_into_array(file, string_array, string_array_len);
        fclose(file);
    }
    return exit_code;
}

/*
Timer
*/
unsigned long long microseconds_now(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
        return (unsigned long long) -1;
    return (unsigned long long)ts.tv_sec * 1000000000ULL + (unsigned long long)ts.tv_nsec;
}