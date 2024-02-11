#define _POSIX_C_SOURCE 199309L
#include "complexity_analysis.h"

int complexity_analysis(int iter_threshold)
{
    int exit_code = EXIT_SUCCESS;
    char string_array[WORDS_MAX_AMOUNT_CA][STRING_MAX_SIZE_CA];
    char string_array_sorted[WORDS_MAX_AMOUNT_CA][STRING_MAX_SIZE_CA];
    int string_array_len = 0;
    int string_array_sorted_len = 0;

    double data_time_delete_bst[DIRECTORIES_N][PERCENTAGES_N]; // Time deletion from tree
    double data_time_delete_avl[DIRECTORIES_N][PERCENTAGES_N]; // Time deletion from av
    double data_time_delete_ht_oa[DIRECTORIES_N][PERCENTAGES_N]; // Time deletion from ht oa
    double data_time_delete_ht_ec[DIRECTORIES_N][PERCENTAGES_N]; // Time delettion from ht ec
    
    double data_time_find_avl[DIRECTORIES_N]; // Time find in avl tree
    double data_time_find_bst[DIRECTORIES_N]; // Time find in bst tree
    double data_time_find_ht_oa[DIRECTORIES_N]; // Time find in ht oa
    double data_time_find_ht_ec[DIRECTORIES_N]; // time find int ht ec

    int directories[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int percentages[] = {25, 50, 75, 100};
    int times_n = 100;

    for (int i = 0; i < DIRECTORIES_N; i++)
    {
        int dir_current = directories[i];
        printf("\nКоличество слов: %d\n", directories[i]);
        for (int j = 0; j < PERCENTAGES_N; j++)
        {
            node_t *root = NULL;
            node_t *root_avl = NULL;

            hashtable_oa_t hashtable_oa;
            hashtable_ec_t hashtable_ec;

            node_t *node_found = NULL; // buffer
            
            /*
            Read the words and fill the array data source
            */
            char filename_in[FILEPATH_N];
            sprintf(filename_in, "data/%d/%d.txt", directories[i], percentages[j]);
            printf("\tПроцент удаления слов: %d\n", percentages[j]);
            if (file_read_data(filename_in, string_array, &string_array_len))
                return ERROR_FILE_READ_DATA;
            /*
            Fill the BST
            */
            exit_code = bst_import(&root, string_array, string_array_len);
            if (exit_code)
            {
                printf("ERROR: AVL INIT\n");
                return EXIT_FAILURE;
            }
            int height_bst = bst_find_height(root);
            printf("\t\tВысота bst дерева: %d\n", height_bst);

            /*
            Fill the AVL
            */
            exit_code = avl_import(&root_avl, string_array, string_array_len);
            if (exit_code)
            {
                printf("ERROR: AVL INIT\n");
                return EXIT_FAILURE;
            }
            int height_avl = bst_find_height(root_avl);
            printf("\t\tВысота avl дерева: %d\n", height_avl);

            /*
            Fill the OA table
            */
            exit_code = hashtable_oa_init(&hashtable_oa, string_array_len, string_array, string_array_len, iter_threshold);
            if (exit_code)
            {
                printf("ERROR: OA INIT\n");
                return EXIT_FAILURE;
            }
            int hashtable__oa_count = hashtable_oa_count_records(&hashtable_oa);
            printf("\t\tКоличество записей в ОА таблице: %d\n", hashtable__oa_count);

            /*
            Fill the EC table
            */
            exit_code = hashtable_ec_init(&hashtable_ec, string_array_len, string_array, string_array_len, iter_threshold);
            if (exit_code)
            {
                printf("ERROR: EC INIT\n");
                return EXIT_FAILURE;
            }
            int hashtable_ec_count = hashtable_ec_count_records(&hashtable_ec);
            printf("\t\tКоличество записей в EC таблице: %d\n", hashtable_ec_count);

            /*
            Find in BST tree
            */
            unsigned long long time_find_bst = 0;
            for (int k = 0; k < times_n; k++)
            {
                unsigned long long beg_find_bst = microseconds_now();
                for (int n = 0; n < string_array_len; n++)
                    bst_find(root, string_array[n]);
                unsigned long long end_find_bst = microseconds_now();
                time_find_bst += (end_find_bst - beg_find_bst);
            }
            data_time_find_bst[i] = time_find_bst / (times_n * string_array_len);

            /*
            Find in AVL tree
            */
            unsigned long long time_find_avl = 0;
            for (int k = 0; k < times_n; k++)
            {
                unsigned long long beg_find_avl = microseconds_now();
                for (int n = 0; n < string_array_len; n++)
                    bst_find(root_avl, string_array[n]);
                unsigned long long end_find_avl = microseconds_now();
                time_find_avl += (end_find_avl - beg_find_avl);
            }
            data_time_find_avl[i] = time_find_avl / (times_n * string_array_len);

            /*
            Find in OA table
            */
            unsigned long long time_find_ht_oa = 0;
            for (int k = 0; k < times_n; k++)
            {
                unsigned long long beg_find_ht_oa = microseconds_now();
                for (int n = 0; n < string_array_len; n++)
                    hashtable_find_oa(&hashtable_oa, string_array[n]);
                unsigned long long end_find_ht_oa = microseconds_now();
                time_find_ht_oa += (end_find_ht_oa - beg_find_ht_oa);
            }
            data_time_find_ht_oa[i] = time_find_ht_oa / (times_n * string_array_len);

            /*
            Find in EC table
            */
            unsigned long long time_find_ht_ec = 0;
            for (int k = 0; k < times_n; k++)
            {
                unsigned long long beg_find_ht_ec = microseconds_now();
                for (int n = 0; n < string_array_len; n++)
                    hashtable_find_ec(&hashtable_ec, string_array[n]);
                unsigned long long end_find_ht_ec = microseconds_now();
                time_find_ht_ec += (end_find_ht_ec - beg_find_ht_ec);
            }
            data_time_find_ht_ec[i] = time_find_ht_ec / (times_n * string_array_len);

            /*
            BST Words Deletion
            */
            unsigned long long time_delete_bst = 0;
            for (int k = 0; k < times_n; k++)
            {
                bst_free(root);
                root = NULL;
                exit_code = bst_import(&root, string_array, string_array_len);
                if (exit_code)
                    return EXIT_FAILURE;
                
                int count = bst_node_count(root);
                // printf("Iter : %d, Count: %d\n", k, count);
                unsigned long long beg_delete_bst = microseconds_now();
                root = bst_delete_by_letter(root, 'm');
                unsigned long long end_delete_bst = microseconds_now();
                time_delete_bst += end_delete_bst - beg_delete_bst;
                // printf("Iter: %d, Time: %lld\n", k, end_tree - beg_tree);
            }
            data_time_delete_bst[i][j] = time_delete_bst / times_n;

            /*
            AVL Words Deletion
            */
            unsigned long long time_delete_avl = 0;
            for (int k = 0; k < times_n; k++)
            {
                bst_free(root_avl);
                root_avl = NULL;
                exit_code = avl_import(&root_avl, string_array, string_array_len);
                if (exit_code)
                    return EXIT_FAILURE;
                
                // int count = bst_node_count(root_avl);
                // printf("Iter : %d, Count: %d\n", k, count);
                unsigned long long beg_delete_avl = microseconds_now();
                root_avl = avl_delete_by_letter(root_avl, 'm');
                unsigned long long end_delete_avl = microseconds_now();
                time_delete_avl += end_delete_avl - beg_delete_avl;
                // printf("Iter: %d, Time: %lld\n", k, end_tree - beg_tree);
            }
            data_time_delete_avl[i][j] = time_delete_avl / times_n;

            /*
            Hashtable OA Deletion
            */
            unsigned long long time_delete_ht_oa = 0;
            for (int k = 0; k < times_n; k++)
            {
                // Recreate and repopulate the hashtable from string_array
                hashtable_oa_t hashtable_oa;
                hashtable_oa_init(&hashtable_oa, string_array_len, string_array, string_array_len, iter_threshold);

                unsigned long long beg_delete_ht_oa = microseconds_now();
                hashtable_delete_by_letter_oa(&hashtable_oa, 'm');
                unsigned long long end_delete_ht_oa = microseconds_now();
                time_delete_ht_oa += end_delete_ht_oa - beg_delete_ht_oa;

                // Free resources and reset the hashtable
                hashtable_free_oa(&hashtable_oa);
            }
            data_time_delete_ht_oa[i][j] = (double)time_delete_ht_oa / times_n;

            /*
            Hashtable EC Deletion
            */
            unsigned long long time_delete_ht_ec = 0;
            for (int k = 0; k < times_n; k++)
            {
                hashtable_ec_t hashtable_ec;
                hashtable_ec_init(&hashtable_ec, string_array_len, string_array, string_array_len, iter_threshold);
                unsigned long long beg_delete_ht_ec = microseconds_now();
                hashtable_delete_by_letter_ec(&hashtable_ec, 'm');
                unsigned long long end_delete_ht_ec = microseconds_now();
                time_delete_ht_ec += end_delete_ht_ec - beg_delete_ht_ec;
                hashtable_free_ec(&hashtable_ec);
            }
            data_time_delete_ht_ec[i][j] = (double)time_delete_ht_ec / times_n;


            printf("\t\tВремя удаления на БДП (наносекунды): %f\n", data_time_delete_bst[i][j]);
            printf("\t\tВремя удаления на AVL (наносекунды): %f\n", data_time_delete_avl[i][j]);
            printf("\t\tВремя удаления на HT OA (наносекунды): %f\n", data_time_delete_ht_oa[i][j]);
            printf("\t\tВремя удаления на HT EC (наносекунды): %f\n", data_time_delete_ht_ec[i][j]);
            bst_free(root);
            bst_free(root_avl);
            hashtable_free_ec(&hashtable_ec);
            hashtable_free_oa(&hashtable_oa);
        }
        printf("\t\tВремя поиска на БДП (наносекунды): %f\n", data_time_find_bst[i]);
        printf("\t\tВремя поиска на AVL (наносекунды): %f\n", data_time_find_avl[i]);
        printf("\t\tВремя поиска на HT OA (наносекунды): %f\n", data_time_find_ht_oa[i]);
        printf("\t\tВремя поиска на HT EC (наносекунды): %f\n", data_time_find_ht_ec[i]);
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