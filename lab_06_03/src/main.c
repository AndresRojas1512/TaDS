#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "bst.h"
#include "ui.h"
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

    node_t *root = NULL;

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
                case 2:
                    bst_preorder(root);
                    break;
                case 3:
                    bst_inorder(root);
                    break;
                case 4:
                    bst_postorder(root);
                    break;
                case 5:
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
                case 6:
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
                case 7:
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
                case 8:
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
                case 9:
                    exit_code = complexity_analysis();
                    break;
            }
        }
    }
    while (choice != 0 && choice != 9);

    return exit_code;
}