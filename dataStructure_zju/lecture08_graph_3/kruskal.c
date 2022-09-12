#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

/*--------------并查集定义------------*/
typedef Vertex ElementType;
typedef Vertex SetName;
typedef ElementType SetType[MAX_VERTEX];

void init_vset(SetType s, int n) //初始化并查集
{
    ElementType x;
    for (x = 0; x < n; x++)
        s[x] = -1;
}
void union_set(SetType s, SetName r1, SetName r2)
{
    //默认r1和r2是不同的集合
    if (s[r1] > s[r2])
    {
        s[r2] += s[r1];
        s[r1] = r2;
    }
    else
    {
        s[r1] += s[r2];
        s[r2] = r1;
    }
}
SetName find(SetType s, ElementType x)
{
    //默认集合元素全部初始化成-1
    if (s[x] < 0)
        return x;
    else
        return find(s, s[x]);
}
bool check_cycle(SetType vset, Vertex v1, Vertex v2)
{ /* 检查连接V1和V2的边是否在现有的最小生成树子集中构成回路 */
    Vertex Root1, Root2;

    Root1 = find(vset, v1); /* 得到V1所属的连通集名称 */
    Root2 = find(vset, v2); /* 得到V2所属的连通集名称 */

    if (Root1 == Root2) /* 若V1和V2已经连通，则该边不能要 */
        return false;
    else
    { /* 否则该边可以被收集，同时将V1和V2并入同一连通集 */
        union_set(vset, Root1, Root2);
        return true;
    }
}
/*--------------并查集定义结束------------*/

/*--------------边的最小堆定义------------*/
typedef Edge *EdgeSet;
void percDown(EdgeSet eset, int p, int n)
{
    int parent, child;
    Edge x;

    x = eset[p];
    for (parent = p; (parent * 2 + 1) < n; parent = child)
    {
        child = parent * 2 + 1;
        if (child != n - 1 && eset[child]->edge_weight > eset[child + 1]->edge_weight)
            child++;
        if (x->edge_weight <= eset[child]->edge_weight)
            break;
        else
            eset[parent] = eset[child];
    }
    eset[parent] = x;
}
void init_eset(LGraph graph, EdgeSet eset)
{
    Vertex v;
    Adjacency_vertex w;
    int e_count;

    /* 将图的边存入数组ESet */
    e_count = 0;
    for (v = 0; v < graph->vertex_num; v++)
    {
        for (w = graph->vertex_list[v].head_vertex; w; w = w->next)
        {
            if (v < w->vertex_index) /* 避免重复录入无向图的边，只收V1<V2的边 */
            {
                eset[e_count]->vertex1_index = v;
                eset[e_count]->vertex2_index = w->vertex_index;
                eset[e_count]->edge_weight = w->weight;
            }
        }
    }

    /* 初始化为最小堆 */
    for (e_count = graph->vertex_num / 2; e_count >= 0; e_count--)
        percDown(eset, e_count, graph->egde_num);
}
int get_edge(EdgeSet eset, int current_size)
{ /* 给定当前堆的大小CurrentSize，将当前最小边位置弹出并调整堆 */
    /* 将最小边与当前堆的最后一个位置的边交换 */
    Edge tmp = eset[0];
    eset[0] = eset[current_size - 1];
    eset[current_size] = tmp;
    percDown(eset, 0, current_size - 1);
    return current_size - 1;
}
/*--------------边的最小堆定义结束------------*/

int kruskal(LGraph graph, LGraph MST)
{
    WeightType total_weight;
    int e_count, next_edge;
    SetType vset;
    init_vset(vset, graph->vertex_num);

    EdgeSet eset = (EdgeSet)malloc(sizeof(struct Edge_node) * graph->egde_num);
    init_eset(graph, eset);

    //创建包含所有顶点并没有边的邻接矩阵图
    MST = (LGraph)malloc(sizeof(struct graph_node));
    MST->egde_num = 0;
    MST->vertex_num = graph->vertex_num;
    for (int v = 0; v < MST->vertex_num; v++)
    {
        MST->vertex_list[v].head_vertex = NULL;
    }

    total_weight = 0;
    e_count = 0;
    next_edge = graph->egde_num;            //原始边集的规模
    while (e_count < graph->vertex_num - 1) /* 当收集的边不足以构成树时 */
    {
        next_edge = get_edge(eset, next_edge);
        if (next_edge < 0) //边集已空
            break;
        /* 如果该边的加入不构成回路，即两端结点不属于同一连通集 */
        if (check_cycle(vset, eset[next_edge]->vertex1_index, eset[next_edge]->vertex2_index))
        {
            /* 将该边插入MST */
            insertEdge(MST, eset[next_edge]);
            total_weight += eset[next_edge]->edge_weight;
            e_count++;
        }
    }
    if (e_count < graph->vertex_num - 1)
        total_weight = -1;
    return total_weight;
}

int main()
{
    return 0;
}
