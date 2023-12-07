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
    char letter;
    int count_delwords_file;

    node_t *root = NULL;

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
                    printf("Имя файла: ");
                    exit_code = string_read_validate(stdin, filepath);
                    if (exit_code)
                    {
                        printf("Ошибка: Ввод названия файла.\n");
                        return exit_code;
                    }
                    
                    file = fopen(filepath, "r");
                    if (!file)
                    {
                        printf("Ошибка: Файл не существует.\n");
                        return EXIT_FAILURE;
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
                            printf("Дирево инициализировано.\n");
                            printf("Высота дерева: %d\n", bst_find_height(root));
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
                            printf("Слово успешно добавлено.\n");
                        }
                        else
                            printf("Ошибка: Добавление слова.\n");
                    }
                    else
                        printf("Ошибка: Формат слова.\n");
                    break;
                case 6:
                    printf("Введите слово: ");
                    exit_code = string_read_validate(stdin, bst_word_delete);
                    if (!exit_code)
                    {
                        printf("Введено: %s\n", bst_word_delete);
                        root = bst_delete(root, bst_word_delete);
                        if (root)
                        {
                            file_graph = fopen("tree_deleted.gv", "w");
                            bst_graphviz_format(file_graph, root);
                            fclose(file_graph);
                            printf("Слово успешно удалено.\n");
                        }
                        else
                            printf("Внимание: Дерево стало пустым.\n");
                    }
                    break;
                case 7:
                    printf("Введите слово: ");
                    exit_code = string_read_validate(stdin, bst_word_search);
                    if (!exit_code)
                    {
                        printf("Введено: %s\n", bst_word_search);
                        bst_node_search = bst_search(root, bst_word_search);
                        if (bst_node_search)
                            printf("Слово найдено: %s\n", bst_node_search->data);
                        else
                            printf("Слово не найдено\n");
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
                            printf("Слова успешно удалены\n");
                        }
                        else
                            printf("Внимание: дерево стало пустым\n");
                        exit_code = file_delete_words(filepath, filepath_out, letter, &count_delwords_file);
                        if (!exit_code)
                            printf("Слова из файла были удалены\n");
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
