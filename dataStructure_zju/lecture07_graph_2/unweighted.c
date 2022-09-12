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
typedef struct Graph_node *Graph;

struct Queue_node
{
    int data[VERTEX_MAX + 1];
    int front, rear;
    int size;
};
typedef struct Queue_node *Queue;
Queue creatQueue()
{
    Queue Q = (Queue)malloc(sizeof(struct Queue_node));
    Q->front = Q->rear = -1;
    Q->size = 0;
    return Q;
}
void addQ(Queue q, int x)
{
    q->data[++q->rear]=x;
    q->size++;
}
int getQ(Queue q)
{
    return q->data[++q->front];
}

//邻接表储存-无权图的单源最短路算法
void unweighted(Graph graph, int distance[], int path[], Vertex start_vertex)
{
    Queue queue = creatQueue();
    distance[start_vertex] = 0;//初始化源点
    addQ(queue,start_vertex);

    Vertex tmp_vertex;
    Adjacency_vertex tmp_node;
    while(queue->rear!=queue->front)
    {
        tmp_vertex = getQ(queue);
        //遍历当前结点的所有邻接点
        for(tmp_node=graph->vertex_list[tmp_vertex].head_vertex;tmp_node;tmp_node=tmp_node->next)
        {
            //如果该邻接点没有被访问过
            if(distance[tmp_node->vertex_index]==-1)
            {
                distance[tmp_node->vertex_index]=distance[tmp_vertex]+1;
                path[tmp_node->vertex_index]=tmp_vertex;
                addQ(queue,tmp_node->vertex_index);
            }
        }
    }
}
int main()
{
    return 0;
}