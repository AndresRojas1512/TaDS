#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "file.h"
#include "bst.h"
#include "ui.h"
#include "hashtable.h"
#include "complexity_analysis.h"
#include "macros_rc.h"
#include "avl.h"

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
    node_t *avl_node_search;

    string_t *hashtable_oa_word_delete;
    node_ht_t *hashtable_ec_word_delete;

    string_t *hashtable_oa_word_search;
    node_ht_t *hashtable_ec_word_search;

    char letter;
    int count_delwords_file;
    int iter_threshold;

    node_t *root = NULL;
    node_t *root_avl = NULL;
    hashtable_oa_t hashtable_oa;
    hashtable_ec_t hashtable_ec;

    do
    {
        menu();
        if (input_choice(&choice))
            puts("\nОшибка: Введите опцию (0 - 9).\n");
        else
        {
            switch (choice)
            {
                case 1:
                    {
                        printf("Имя файла: ");
                        exit_code = string_read_validate(stdin, filepath);
                        if (exit_code)
                        {
                            printf("Ошибка: Ввод названия файла.\n");
                            return ERROR_FILENAME_FORMAT;
                        }
                        
                        file = fopen(filepath, "r");
                        if (!file)
                        {
                            printf("Ошибка: Файл не существует.\n");
                            return ERROR_FILE_OPENING;
                        }
                        
                        exit_code = file_read_into_array(file, string_array, &string_array_len);
                        if (exit_code)
                            printf("Ошибка: Файл испорчен.\n");
                        fclose(file);
                        
                        if (!exit_code)
                        {
                            exit_code = bst_import(&root, string_array, string_array_len);
                            if (!exit_code)
                            {
                                file_graph = fopen("tree_graphic.gv", "w");
                                bst_graphviz_format(file_graph, root);
                                fclose(file_graph);
                                printf("Дерево инициализировано.\n");
                                printf("Высота дерева: %d\n", bst_find_height(root));
                            }
                            if (!exit_code)
                            {
                                exit_code = avl_import(&root_avl, string_array, string_array_len);
                                if (!exit_code)
                                {
                                    file_graph = fopen("avl_graphic.gv", "w");
                                    bst_graphviz_format(file_graph, root_avl);
                                    fclose(file_graph);
                                    printf("AVL дерево инициализировано.\n");
                                    printf("Высота AVL дерева: %d\n", bst_find_height(root_avl));
                                }
                            }
                            if (!exit_code)
                            {
                                printf("Введите количество максимальных коллизий (1 - 20): ");
                                exit_code = input_iter_threshold(&iter_threshold);
                                if (!exit_code)
                                {
                                    exit_code = hashtable_oa_init(&hashtable_oa, string_array_len, string_array, string_array_len, iter_threshold);
                                    if (!exit_code)
                                    {
                                        exit_code = hashtable_ec_init(&hashtable_ec, string_array_len, string_array, string_array_len, iter_threshold);
                                        if (!exit_code)
                                        {
                                            printf("Таблицы инициализированы\n");
                                            printf("Таблица на основе метода Внутренее хэрирование\n");
                                            hashtable_print_oa(&hashtable_oa);
                                            printf("Таблица на основе метода Внешнее хэрирование\n");
                                            hashtable_print_ec(&hashtable_ec);
                                        }
                                    }
                                }
                                else
                                {
                                    printf("Ошибка: Невалидное значение.\n");
                                    exit_code = ERROR_INPUT_THRESHOLD_M;
                                }

                            }
                        }
                        break;
                    }
                case 2:
                    {
                        printf("\tБДП:\n");
                        bst_preorder(root);
                        printf("\n\tAVL:\n");
                        bst_preorder(root_avl);
                        break;
                    }
                case 3:
                    {
                        printf("\tБДП:\n");
                        bst_inorder(root);
                        printf("\n\tAVL:\n");
                        bst_inorder(root_avl);
                        break;
                    }
                case 4:
                    {
                        printf("\tБДП:\n");
                        bst_postorder(root);
                        printf("\n\tAVL:\n");
                        bst_postorder(root_avl);
                        break;
                    }
                case 5:
                    {
                        printf("Введите слово: ");
                        exit_code = string_read_validate(stdin, bst_word_insert);
                        if (!exit_code)
                        {
                            printf("Введено: %s\n", bst_word_insert);
                            root = bst_insert(root, bst_word_insert);
                            if (root)
                            {
                                file_graph = fopen("tree_inserted.gv", "w");
                                bst_graphviz_format(file_graph, root);
                                fclose(file_graph);
                                printf("Слово успешно добавлено в БДП.\n");
                            }
                            else
                                printf("Ошибка: Добавление слова в БДП.\n");
                            
                            root_avl = avl_insert(root_avl, bst_word_insert);
                            if (root_avl)
                            {
                                file_graph = fopen("avl_inserted.gv", "w");
                                bst_graphviz_format(file_graph, root_avl);
                                fclose(file_graph);
                                printf("Слово успешно добавлено в AVL.\n");
                            }
                            else
                                printf("Ошибка: Добавление слова в AVL.\n");
                            
                        }
                        else
                            printf("Ошибка: Формат слова.\n");
                        break;
                    }
                case 6:
                    printf("Введите слово: ");
                    exit_code = string_read_validate(stdin, bst_word_delete);
                    if (!exit_code)
                    {
                        // Delete from BST
                        printf("Введено: %s\n", bst_word_delete);
                        root = bst_delete(root, bst_word_delete);
                        if (root)
                        {
                            file_graph = fopen("tree_deleted.gv", "w");
                            bst_graphviz_format(file_graph, root);
                            fclose(file_graph);
                            printf("Слово успешно удалено из БДП.\n");
                        }
                        else
                            printf("Внимание: БДП стало пустым.\n");
                        
                        // Delete from AVL
                        root_avl = avl_delete(root_avl, bst_word_delete);
                        if (root_avl)
                        {
                            file_graph = fopen("avl_deleted.gv", "w"); 
                            bst_graphviz_format(file_graph, root_avl);
                            fclose(file_graph);
                            printf("Слово успешно удалено из AVL.\n");
                        }
                        else
                            printf("Внимание: AVL стало пустым.\n");
                        
                        // Delete from hashtable_oa
                        hashtable_oa_word_delete = hashtable_delete_oa(&hashtable_oa, bst_word_delete);
                        if (hashtable_oa_word_delete)
                        {
                            printf("Слово успешно удалено из HT_OA.\n");
                            hashtable_print_oa(&hashtable_oa);
                        }
                        else
                            printf("Не удалось найти слово.\n");

                        // Delete from hashtable_ec
                        hashtable_ec_word_delete = hashtable_delete_ec(&hashtable_ec, bst_word_delete);
                        if (hashtable_ec_word_delete)
                        {
                            printf("Слово успешно удалено из HT_EC.\n");
                            hashtable_print_ec(&hashtable_ec);
                        }
                        else
                            printf("Не удалось найти слово.\n");
                    }
                    break;
                case 7:
                    printf("Введите слово: ");
                    exit_code = string_read_validate(stdin, bst_word_search);
                    if (!exit_code)
                    {
                        // Find from BST
                        printf("Введено: %s\n", bst_word_search);
                        bst_node_search = bst_search(root, bst_word_search);
                        if (bst_node_search)
                            printf("Слово найдено: %s\n", bst_node_search->data);
                        else
                            printf("Слово не найдено БДП\n");
                        
                        // Find from AVL
                        avl_node_search = bst_search(root_avl, bst_word_search);
                        if (avl_node_search)
                            printf("Слово найдено: %s\n", avl_node_search->data);
                        else
                            printf("Слово не найдено AVL\n");
                            
                        // Find from hashtable_oa
                        hashtable_oa_word_search = hashtable_find_oa(&hashtable_oa, bst_word_search);
                        if (hashtable_oa_word_search)
                            printf("Слово найдено: %s\n", hashtable_oa_word_search->string);
                        else
                            printf("Слово не найдено HT_OA\n");
                        
                        // Find from hashtable_ec
                        hashtable_ec_word_search = hashtable_find_ec(&hashtable_ec, bst_word_search);
                        if (hashtable_ec_word_search)
                            printf("Слово найдено: %s\n", hashtable_ec_word_search->data);
                        else
                            printf("Слово не найдено HT_EC\n");
                    }
                    break;
                case 8:
                    printf("Введите букву: ");
                    if (scanf("%c", &letter) != 1)
                        printf("Ошибка: Ввод буквы\n");
                    else
                    {
                        root = bst_delete_by_letter(root, letter);
                        if (root)
                        {
                            file_graph = fopen("tree_letters.gv", "w");
                            bst_graphviz_format(file_graph, root);
                            fclose(file_graph);
                            printf("Слова успешно удалены из БДП\n");
                        }
                        else
                            printf("Внимание: БДП стало пустым\n");
                        
                        root_avl = avl_delete_by_letter(root_avl, letter);
                        if (root_avl)
                        {
                            file_graph = fopen("avl_letters.gv", "w");
                            bst_graphviz_format(file_graph, root_avl);
                            fclose(file_graph);
                            printf("Слова успешно удалены из AVL\n");
                        }
                        else
                            printf("Внимание: AVL стало пустым\n");
                    }
                    break;
                case 9:
                    exit_code = complexity_analysis();
                    break;
            }
        }
    }
    while (choice != 0 && choice != 9);
    bst_free(root);
    root = NULL;
    return exit_code;
}
