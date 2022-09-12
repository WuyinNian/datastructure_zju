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

int find_min_dist(Graph g, int dist[], bool collected[])
{
    int min_vertex, v;
    int min_dist = INF;
    for (v = 0; v < g->vertex_num; v++)
    {
        if (collected[v] == false && dist[v] < min_dist)
        {
            min_dist = dist[v];
            min_vertex = v;
        }
    }
    if (min_dist < INF)
        return min_dist;
    else
        return -1;
}
bool dijkstra(Graph graph, int distance[], int path[], int start_vertex)
{
    bool collected[MAX_VERTEX]; //储存已经收录的结点
    int v, w;

    //传入的矩阵图不存在的边已经默认用INF表示
    for (v = 0; graph->vertex_num; v++)
    {
        distance[v] = graph->weight[start_vertex][v];
        if (distance[v] < INF)
            path[v] = start_vertex;
        else
            path[v] = -1;
        collected[v] = false;
    }

    distance[start_vertex] = 0;
    collected[start_vertex] = true;

    while (1)
    {
        v = find_min_dist(graph, distance, collected);
        if (v == -1) //如果v不存在
            break;
        collected[v] = true;
        //遍历图的每一个顶点
        for (w = 0; w < graph->vertex_num; w++)
        {
            if (collected[w] == false && graph->weight[v][w] < INF)
            {
                if (graph->weight[v][w] < 0)
                    return false;
                // 如果收录v使dist[w]更小
                if (distance[v] + graph->weight[v][w] < distance[w])
                {
                    distance[w] = distance[v] + graph->weight[v][w];
                    path[w] = v;
                }
            }
        }
    }
    return true;
}
int main()
{
    return 0;
}