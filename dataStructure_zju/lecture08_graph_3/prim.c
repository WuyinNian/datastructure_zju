#include <stdio.h>
#include <stdlib.h>

//图的边
typedef int Vertex;
typedef int WeightType;
struct Edge_node
{
    Vertex vertex1_index, vertex2_index;
    WeightType edge_weight;
};
typedef struct Edge_node *Edge;

//图的邻接点
typedef struct Adjacency_node *Adjacency_vertex;
struct Adjacency_node
{
    Vertex vertex_index;
    WeightType weight;
    Adjacency_vertex next;
};

//邻接表头结点
typedef int Vertex_data_type;
struct vertex_node
{
    Adjacency_vertex head_vertex;
    Vertex_data_type vertex_data;
};

//邻接表表示图
#define VERTEX_MAX 100
struct Graph_node
{
    int vertex_num;
    int egde_num;
    struct vertex_node vertex_list[VERTEX_MAX];
};
typedef struct Graph_node *LGraph;
void insertEdge(LGraph graph, Edge e)
{
    //建立v2邻接点
    Adjacency_vertex newNode;
    newNode = (Adjacency_vertex)malloc(sizeof(struct Adjacency_node));
    newNode->vertex_index = e->vertex2_index;
    newNode->weight = e->edge_weight;
    // v2插入v1表头，即vList[v1]
    newNode->next = graph->vertex_list[e->vertex1_index].head_vertex;
    graph->vertex_list[e->vertex1_index].head_vertex = newNode;

    //如果是无向图则还需将v1插入v2表头
    Adjacency_vertex newNode2;
    newNode2 = (Adjacency_vertex)malloc(sizeof(struct Adjacency_node));
    newNode2->vertex_index = e->vertex1_index;
    newNode2->weight = e->edge_weight;
    // v2插入v1表头，即vList[v1]
    newNode2->next = graph->vertex_list[e->vertex2_index].head_vertex;
    graph->vertex_list[e->vertex2_index].head_vertex = newNode2;
}
//----------------邻接表储存图------------------

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
typedef struct graph_node *MGraph;
//----------------邻接矩阵储存图----------------

/**
 * @brief
 *
 * @param graph
 * @param MST 邻接表储存最小生成树
 * @return int
 */
Vertex find_min_dist(MGraph graph, WeightType dist[]);
int prim(MGraph graph, LGraph MST)
{
    WeightType dist[MAX_VERTEX], total_weight;
    Vertex parent[MAX_VERTEX], v, w;
    int v_count;
    Edge e;

    //初始化。默认初始点下标为0
    for (v = 0; v < graph->vertex_num; v++)
    {
        dist[v] = graph->weight[0][v]; //假设V到W没有直接的边，则Graph->G[V][W]定义为INF
        parent[v] = 0;                 //暂定所有顶点的父结点都是初始点0
    }

    total_weight = 0; //初始化初始权重和
    v_count = 0;      //初始化收录的顶点数

    //创建包含所有顶点并没有边的邻接矩阵图
    MST = (LGraph)malloc(sizeof(struct graph_node));
    MST->egde_num = 0;
    MST->vertex_num = graph->vertex_num;
    for (v = 0; v < MST->vertex_num; v++)
    {
        MST->vertex_list[v].head_vertex = NULL;
    }
    //建立空结点
    e = (Edge)malloc(sizeof(struct Edge_node));

    //初始点收入进MST
    dist[0] = 0;
    v_count++;
    parent[0] = -1;

    while (1)
    {
        v = find_min_dist(graph, dist); //返回未被收录顶点中dist的最小值
        if (v == -1)                    //如果这样的v不存在，算法退出
            break;

        //将v及相应的边<parent[v],v>收录进MST
        e->vertex1_index = parent[v];
        e->vertex2_index = v;
        e->edge_weight = dist[v];
        insertEdge(MST, e);
        total_weight += dist[v];
        dist[v] = 0;
        v_count++;

        for (w = 0; w < graph->vertex_num; w++)
        {
            if (dist[w] != 0 && graph->weight[v][w] < INF) //若w未被收录且w是v的邻接点
            {
                if (graph->weight[v][w] < dist[w]) //若收录v使得dist[w]边小
                {
                    dist[w] = graph->weight[v][w];
                    parent[w] = v;
                }
            }
        }
    }
    if (v_count < graph->vertex_num)
        return -1;
    else
        return total_weight;
}

Vertex find_min_dist(MGraph graph, WeightType dist[])
{
    Vertex min_v, v;
    WeightType min_dist = INF;

    for (v = 0; v < graph->vertex_num; v++)
    {
        if (dist[v] != 0 && dist[v] < min_dist)
        {
            min_dist = dist[v];
            min_v = v;
        }
    }

    if (min_dist < INF)
        return min_v;
    else
        return -1;
}

int main()
{
    return 0;
}