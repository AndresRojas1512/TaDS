#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ui.h"
#include "macros_rc.h"
#include "graph.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;
    int choice;
    FILE *file_graph;

    matrix_t adj_matrix;
    matrix_t dist_matrix;
    int vertices_n;
    bool is_connected = false;
    double determinant;
    double spanning_trees_amount;

    do
    {
        menu();
        if (input_choice(&choice))
            puts("\nОшибка: Введите опцию (0 - 5).\n");
        else
        {
            switch (choice)
            {
                case 1:
                    {
                        printf("Введите количество вершин графа:");
                        exit_code = input_vertices_n(&vertices_n);
                        if (!exit_code)
                        {
                            adj_matrix_init(&adj_matrix, vertices_n);
                            printf("Введите матрицу смежности графа:\n");
                            exit_code = adj_matrix_input(&adj_matrix);
                            if (!exit_code)
                            {
                                matrix_zero_diagonal(&adj_matrix);
                                file_graph = fopen("graph.gv", "w");
                                graphviz_format(file_graph, &adj_matrix);
                                fclose(file_graph);
                            }
                            else
                                printf("Ошибка ввода.");
                        }
                        else
                            printf("Ошибка ввода.");
                        break;
                    }
                case 2:
                    {
                        dist_matrix_init(&adj_matrix, &dist_matrix);
                        matrix_zero_diagonal(&dist_matrix);
                        dist_matrix_int_max(&dist_matrix);
                        floydWarshall(&dist_matrix);
                        printf("Матрица кратчайших расстояний:\n");
                        matrix_format_output(&dist_matrix);
                        break;
                    }
                case 3:
                    {
                        is_connected = is_graph_connected(&adj_matrix);
                        if (is_connected)
                            printf("Граф связный.\n");
                        else
                            printf("Граф не является связным.\n");
                        break;
                    }
                case 4:
                    {
                        determinant = calc_determinant(&adj_matrix);
                        printf("Determinant: %f\n", determinant);
                        spanning_trees_amount = count_spanning_trees(&adj_matrix);
                        printf("Spanning trees amount: %f\n", spanning_trees_amount);
                        break;
                    }
                case 5:
                    {
                        break;
                    }
            }
        }
    }
    while (choice != 0);
    return exit_code;
}