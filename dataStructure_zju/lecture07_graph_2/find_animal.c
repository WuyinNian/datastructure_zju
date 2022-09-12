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
};
typedef struct graph_node *Graph;

void myprint(int m[][MAX_VERTEX], int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}

Graph buildGraph(int N, int M)
{
    Graph graph = (Graph)malloc(sizeof(struct graph_node));
    graph->vertex_num = N;
    graph->edge_num = M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i != j)
                graph->weight[i][j] = INF;
        }
    }

    int v1, v2, w;
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d %d", &v1, &v2, &w);
        graph->weight[v1 - 1][v2 - 1] = w;
        graph->weight[v2 - 1][v1 - 1] = w;
    }

    return graph;
}

//多源最短路径算法
void myfloyd(Graph graph, int distance[][MAX_VERTEX])
{
    int i, j, k;
    for (i = 0; i < graph->vertex_num; i++)
    {
        for (j = 0; j < graph->vertex_num; j++)
        {
            distance[i][j] = graph->weight[i][j];
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
            }
        }
    }
}

void findAnimal(Graph graph, int N)
{
    int dist[MAX_VERTEX][MAX_VERTEX];
    myfloyd(graph, dist);
    int max_dist[N];
    int a1, a2;
    int min_animal_dist = INF;
    int min_animal = -1;
    for (int i = 0; i < N; i++)
    {
        max_dist[i] = dist[i][0];
        for (int j = 1; j < N; j++)
        {
            if (dist[i][j] > max_dist[i])
            {
                max_dist[i] = dist[i][j];
                a1 = i + 1;
                a2 = j + 1;
            }
        }
        if(max_dist[i]==INF)
        {
            printf("0\n");
            return;
        }
        if (max_dist[i] < min_animal_dist)
        {
            min_animal_dist = max_dist[i];
            min_animal = a1;
        }
    }
    printf("%d %d\n", min_animal, min_animal_dist);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M); //读取动物数和魔咒数
    Graph graph = buildGraph(N, M);
    findAnimal(graph, N);
    return 0;
}