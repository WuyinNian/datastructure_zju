#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//边的定义
struct Edge_node
{
    int vertex1, vertex2;
    int edge_weight;
};
typedef struct Edge_node *Edge;

//图的定义
#define MAX_VERTEX 100
#define INF 65535
struct graph_node
{
    int vertex_num;
    int edge_num;
    int weight[MAX_VERTEX][MAX_VERTEX];
    char vertex_data[MAX_VERTEX];
};
typedef struct graph_node *Graph;

//多源最短路径算法
bool floyd(Graph graph, int distance[][MAX_VERTEX], int path[][MAX_VERTEX])
{
    int i, j, k;
    for (i = 0; i < graph->vertex_num; i++)
    {
        for (j = 0; j < graph->vertex_num; j++)
        {
            distance[i][j] = graph->weight[i][j];
            path[i][j] = -1;
        }
    }

    for (k = 0; k < graph->vertex_num; k++)
    {
        for (i = 0; i < graph->vertex_num; i++)
        {
            for (j = 0; j < graph->vertex_num; j++)
            {
                if (distance[i][k] + distance[k][j] < distance[i][j])
                    distance[i][j] = distance[i][k] + distance[k][j];
                if (i == j && distance[i][j] < 0)
                    return false;
                path[i][j] = k;
            }
        }
    }

    return true;
}
int main()
{
    return 0;
}