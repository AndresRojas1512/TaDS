#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "file.h"
#include "bst.h"
#include "ui.h"
#include "hashtable.h"
#include "complexity_analysis.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;
    int choice;
    char filepath[STRING_MAX_SIZE + 1];
    char filepath_out[] = "file_out.txt";
    FILE *file;
    FILE *file_graph;

    char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE];
    int string_array_len;

    char bst_word_insert[STRING_MAX_SIZE + 1];
    char bst_word_delete[STRING_MAX_SIZE + 1];
    char bst_word_search[STRING_MAX_SIZE + 1];
    node_t *bst_node_search;
    char letter = 'm';
    int count_delwords_file;
    // bst
    node_t *root = NULL;
    // hashtable
    hashtable_oa_t hashtable_oa;
    hashtable_ec_t hashtable_ec;
    char string_ht_deleted[STRING_MAX_SIZE + 1];

    do
    {
        menu();
        if (input_choice(&choice))
            puts("\nОшибка: Введите опцию (0 - 8).\n");
        else
        {
            switch (choice)
            {
                case 1:
                    {
                        printf("filename: ");
                        exit_code = string_read_validate(stdin, filepath);
                        if (exit_code)
                            return exit_code;
                        
                        file = fopen(filepath, "r");
                        if (!file)
                            return EXIT_FAILURE;
                        
                        exit_code = file_read_into_array(file, string_array, &string_array_len);
                        if (exit_code)
                            printf("Error: File Damaged\n");
                        fclose(file);
                        
                        if (!exit_code)
                        {
                            exit_code = bst_import(&root, string_array, string_array_len);
                            if (!exit_code)
                            {
                                file_graph = fopen("arbol.gv", "w");
                                bst_graphviz_format(file_graph, root);
                                fclose(file_graph);
                                printf("bst correctly initialized\n");
                                printf("Height: %d\n", bst_find_height(root));
                            }
                        }
                        break;
                    }
                case 2:
                    {
                        bst_preorder(root);
                        break;
                    }
                case 3:
                    {
                        bst_inorder(root);
                        break;
                    }
                case 4:
                    {
                        bst_postorder(root);
                        break;
                    }
                case 5:
                    {
                        printf("enter the word: ");
                        exit_code = string_read_validate(stdin, bst_word_insert);
                        if (!exit_code)
                        {
                            root = bst_insert(root, bst_word_insert);
                            printf("insertion succesfull\n");
                            if (root)
                            {
                                file_graph = fopen("arbol_insered.gv", "w");
                                bst_graphviz_format(file_graph, root);
                                fclose(file_graph);
                                printf("bst inserted created\n");
                            }
                        }
                        break;
                    }
                case 6:
                    {
                        printf("enter the word: ");
                        exit_code = string_read_validate(stdin, bst_word_delete);
                        if (!exit_code)
                        {
                            printf("Word to delete: %s\n", bst_word_delete);
                            root = bst_delete(root, bst_word_delete);
                            if (root)
                            {
                                file_graph = fopen("arbol_deleted.gv", "w");
                                bst_graphviz_format(file_graph, root);
                                fclose(file_graph);
                                printf("bst deleted created\n");
                            }
                        }
                        break;
                    }
                case 7:
                    {
                        printf("enter the search word: ");
                        exit_code = string_read_validate(stdin, bst_word_search);
                        if (!exit_code)
                        {
                            bst_node_search = bst_search(root, bst_word_search);
                            if (bst_node_search)
                                printf("found word: %s\n", bst_node_search->data);
                            else
                                printf("no found\n");
                        }
                        break;
                    }
                case 8:
                    {
                        root = bst_delete_by_letter(root, letter);
                        if (root)
                        {
                            file_graph = fopen("arbol_letters.gv", "w");
                            bst_graphviz_format(file_graph, root);
                            fclose(file_graph);
                            printf("bst letters created\n");
                        }
                        exit_code = file_delete_words(filepath, filepath_out, letter, &count_delwords_file);
                        break;
                    }
                case 9:
                    {
                        int iters_threshold = 2;
                        int iterations = 0;
                        int insert_extra;
                        hashtable_create_oa(&hashtable_oa, 10);
                        hashtable_print_oa(&hashtable_oa);

                        int start_index = 0;
                        while (start_index < string_array_len)
                        {
                            for (int i = start_index; i < string_array_len; i++)
                            {
                                exit_code = hashtable_insert_oa(&hashtable_oa, string_array[i], &iterations, iters_threshold);
                                // printf("Inserted: %s, Iterations: %d\n", string_array[i], iterations);
                                if (exit_code == ERROR_OA_ITERATIONS_OVERFLOW)
                                {
                                    hashtable_print_oa(&hashtable_oa);
                                    printf("Restructuring table...\n");
                                    if (hashtable_restructure_oa(&hashtable_oa) != EXIT_SUCCESS)
                                    {
                                        printf("Error restructuring table.\n");
                                        return -1;
                                    }
                                    start_index = 0;
                                    break;
                                }
                                else if (exit_code == EXIT_SUCCESS)
                                {
                                    printf("Inserted: %s, Iterations: %d\n", string_array[i], iterations);
                                    if (i == string_array_len - 1)
                                        start_index = string_array_len;
                                }
                                else
                                {
                                    printf("Error inserting element: %s\n", string_array[i]);
                                    return -1;
                                }
                            }
                        }
                        hashtable_print_oa(&hashtable_oa);
                        break;
                    }
                case 10:
                    {
                        int list_length = 0;
                        int iters_threshold = 1;
                        hashtable_create_ec(&hashtable_ec, 10);

                        while (true) {
                            bool restructuring_needed = false;
                            for (int i = 0; i < string_array_len; i++) {
                                int exit_code = hashtable_insert_ec(&hashtable_ec, string_array[i], iters_threshold);
                                if (exit_code == ERROR_EC_ITERATIONS_OVERFLOW) {
                                    printf("Restructuring table...\n");
                                    int new_capacity = hashtable_ec.capacity * 2;
                                    if (hashtable_restructure_ec(&hashtable_ec, new_capacity) != EXIT_SUCCESS) {
                                        printf("Error restructuring table.\n");
                                        return -1;
                                    }
                                    restructuring_needed = true;
                                    break;
                                } else if (exit_code != EXIT_SUCCESS) {
                                    printf("Error inserting element: %s\n", string_array[i]);
                                    return -1;
                                }
                            }

                            if (!restructuring_needed) {
                                break; // All elements inserted without exceeding threshold
                            }
                        }
                        hashtable_print_ec(&hashtable_ec);
                        break;
                    }
                case 11:
                    exit_code = complexity_analysis();
                    break;
            }
        }
    }
    while (choice != 0 && choice != 10);

    return exit_code;
}