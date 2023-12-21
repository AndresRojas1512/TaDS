#include "graph.h"

/*
Input number of vertices
*/
int input_vertices_n(int *vertices_n)
{
    if (scanf("%d", vertices_n) != 1)
        return ERROR_GRAPH_INPUT_N;
    if (*vertices_n <= 0 || *vertices_n > N_MAX)
        return ERROR_GRAPH_INPUT_RANGE;
    return EXIT_SUCCESS;
}

/*
Init all the matrix to zeros
*/
void adj_matrix_init(matrix_t *adj_matrix, int vertices_n)
{
    adj_matrix->vertices_n = vertices_n;
    for (int i = 0; i < vertices_n; i++)
    {
        for (int j = 0; j < vertices_n; j++)
            adj_matrix->matrix[i][j] = 0;
    }
}

/*
Print the matrix
*/
void matrix_print(matrix_t *adj_matrix)
{
    for (int i = 0; i < adj_matrix->vertices_n; i++)
    {
        for (int j = 0; j < adj_matrix->vertices_n; j++)
            printf("%d ", adj_matrix->matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

/*
Input the adjacency matrix
*/
int adj_matrix_input(matrix_t *adj_matrix)
{
    printf("   ");
    for (int k = 0; k < adj_matrix->vertices_n; k++)
        printf("%d ", k);
    printf("\n");
    
    for (int i = 0; i < adj_matrix->vertices_n; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < adj_matrix->vertices_n; j++)
        {
            if (scanf("%d", &adj_matrix->matrix[i][j]) != 1)
                return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

/*
Form the matrix of shortest distances for all the pairs of vertices of the graph
*/
void floydWarshall(matrix_t *dist_matrix)
{
    int i, j, k;
    for (k = 0; k < dist_matrix->vertices_n; k++)
    {
        for (i = 0; i < dist_matrix->vertices_n; i++)
        {
            for (j = 0; j < dist_matrix->vertices_n; j++)
            {
                if (dist_matrix->matrix[i][k] != INT_MAX && dist_matrix->matrix[k][j] != INT_MAX)
                    dist_matrix->matrix[i][j] = min(dist_matrix->matrix[i][j], dist_matrix->matrix[i][k] + dist_matrix->matrix[k][j]);
            }
        }
    }
}

/*
Delete all the self loops (set the diagonal to zeros)
*/
void matrix_zero_diagonal(matrix_t *dist_matrix)
{
    for (int i = 0; i < dist_matrix->vertices_n; i++)
    {
        for (int j = 0; j < dist_matrix->vertices_n; j++)
        {
            if (i == j)
                dist_matrix->matrix[i][j] = 0;
        }
    }
}

/*
Write the source matrix into the dist matrix
*/
void dist_matrix_init(matrix_t *adj_matrix, matrix_t *dist_matrix)
{
    dist_matrix->vertices_n = adj_matrix->vertices_n;
    for (int i = 0; i < adj_matrix->vertices_n; i++)
    {
        for (int j = 0; j < adj_matrix->vertices_n; j++)
            dist_matrix->matrix[i][j] = adj_matrix->matrix[i][j];
    }
}

/*
Find min of two ints
*/
int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

/*
Set the zeros that are out the diagonal to INT_MAX
*/
void dist_matrix_int_max(matrix_t *dist_matrix)
{
    for (int i = 0; i < dist_matrix->vertices_n; i++)
    {
        for (int j = 0; j < dist_matrix->vertices_n; j++)
        {
            if ((i != j) && (dist_matrix->matrix[i][j] == 0))
                dist_matrix->matrix[i][j] = INT_MAX;
        }
    }
}

/*
Convert graph to .gv format for Graphviz
*/
void graph_to_dot(FILE *file, matrix_t *graph)
{
    int i, j;

    for (i = 0; i < graph->vertices_n; i++)
    {
        for (j = i + 1; j < graph->vertices_n; j++)
        {
            if (graph->matrix[i][j] != 0)
            {
                fprintf(file, "    \"%d\" -- \"%d\" [label=\"%d\"];\n", i, j, graph->matrix[i][j]);
            }
        }
    }
}

/*
Format .gv file for Graphviz
*/
void graphviz_format(FILE *file, matrix_t *graph)
{
    fprintf(file, "graph G {\n");
    graph_to_dot(file, graph);
    fprintf(file, "}\n");
}

/*
Matrix format output
*/
void matrix_format_output(matrix_t *adj_matrix)
{
    printf("   ");
    for (int k = 0; k < adj_matrix->vertices_n; k++)
        printf("%d ", k);
    printf("\n");
    
    for (int i = 0; i < adj_matrix->vertices_n; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < adj_matrix->vertices_n; j++)
            printf("%d ", adj_matrix->matrix[i][j]);
        printf("\n");
    }
}

/*
Helper function
*/
void DFS(matrix_t *graph, int vertex, bool visited[])
{
    visited[vertex] = true;
    for (int i = 0; i < graph->vertices_n; i++)
    {
        if (graph->matrix[vertex][i] != 0 && !visited[i])
        {
            DFS(graph, i, visited);
        }
    }
}

/*
Function to check if the graph is connected
*/
bool is_graph_connected(matrix_t *graph)
{
    bool visited[N_MAX] = {false};
    DFS(graph, 0, visited);
    for (int i = 0; i < graph->vertices_n; i++)
    {
        if (!visited[i])
            return false;
    }
    return true;
}

/*
Swap rows of a matrix
*/
void swap_rows(double mat[N_MAX][N_MAX], int i, int j, int n)
{
    for (int k = 0; k < n; k++)
    {
        double temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}

double calc_determinant(matrix_t *mat_struct)
{
    int n = mat_struct->vertices_n;
    double temp_mat[N_MAX][N_MAX];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp_mat[i][j] = (double)mat_struct->matrix[i][j];
        }
    }

    double det = 1;
    for (int k = 0; k < n; k++)
    {
        int i_max = k;
        double v_max = temp_mat[i_max][k];

        for (int i = k + 1; i < n; i++)
        {
            if (fabs(temp_mat[i][k]) > v_max)
            {
                v_max = temp_mat[i][k], i_max = i;
            }
        }

        if (fabs(temp_mat[k][i_max]) < EPSILON)
            return 0;

        if (i_max != k)
        {
            swap_rows(temp_mat, k, i_max, n);
            det = det * -1;
        }

        for (int i = k + 1; i < n; i++)
        {
            double f = temp_mat[i][k] / temp_mat[k][k];
            for (int j = k + 1; j < n; j++)
            {
                temp_mat[i][j] -= temp_mat[k][j] * f;
            }
            temp_mat[i][k] = 0;
        }
        det *= temp_mat[k][k];
    }
    return det;
}

/*
Count spanning trees in a graph
*/
double count_spanning_trees(matrix_t *graph)
{
    matrix_t laplacian;
    laplacian.vertices_n = graph->vertices_n;

    for (int i = 0; i < graph->vertices_n; i++)
    {
        int degree = 0;
        for (int j = 0; j < graph->vertices_n; j++)
        {
            degree += graph->matrix[i][j];
            laplacian.matrix[i][j] = -graph->matrix[i][j];
        }
        laplacian.matrix[i][i] = degree;
    }

    matrix_t cofactor;
    cofactor.vertices_n = laplacian.vertices_n - 1;
    for (int i = 1; i < laplacian.vertices_n; i++)
    {
        for (int j = 1; j < laplacian.vertices_n; j++)
        {
            cofactor.matrix[i - 1][j - 1] = laplacian.matrix[i][j];
        }
    }
    return calc_determinant(&cofactor);
}
