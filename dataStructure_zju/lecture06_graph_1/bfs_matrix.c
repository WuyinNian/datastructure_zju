#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define ERROR (ElementType) - 1

typedef int ElementType;
typedef int Position;
struct QNode
{
    int maxSize;          //最大容量(存放个数为maxSize-1,需要留出一个位置判断队列满)
    ElementType *data;    //储存元素的数组
    Position front, rear; //队列头尾指针
};
typedef struct QNode *Queue;

Queue creatQueue(int maxSize)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->data = (ElementType *)malloc(maxSize * sizeof(ElementType));
    Q->maxSize = maxSize;
    Q->front = 0;
    Q->rear = 0;
    return Q;
}

bool isFull(Queue Q)
{
    return (Q->rear + 1) % Q->maxSize == Q->front;
}
bool addQ(Queue Q, ElementType X)
{
    if (isFull(Q))
    {
        printf("Queue Full!\n");
        return false;
    }
    else
    {
        Q->rear = (Q->rear + 1) % Q->maxSize;
        Q->data[Q->rear] = X;
        return true;
    }
}

bool isEmpty(Queue Q)
{
    return Q->rear == Q->front;
}

ElementType deleteQ(Queue Q)
{
    if (isEmpty(Q))
    {
        printf("Queue Empty!");
        return ERROR;
    }
    else
    {
        Q->front = (Q->front + 1) % Q->maxSize;
        return Q->data[Q->front];
    }
}
//边的定义
typedef int Vertex;     //用定点下标来表示顶点
typedef int WeightType; //边的权值类型
struct ENode
{
    Vertex v1, v2;
    WeightType w;
};
typedef struct ENode *PtrToENode;
typedef PtrToENode Edge;

//图节点的定义
#define MAXV 100             //最大顶点数
#define INF 65535            //∞的大小
typedef char VertexDataType; //顶点的数据类型
struct MGNode
{
    int vNum;
    int eNum;
    WeightType edgeW[MAXV][MAXV]; //边权重值
    VertexDataType vData[MAXV];   //顶点的数据,如果顶点没有数据，则可以不定义
};
typedef struct MGNode *PtrToMGNode;
typedef PtrToMGNode MGraph;

/**
 * @brief 初始化一个有vNum个顶点，但没有边的图
 *
 * @param vNum
 * @return MGraph
 */
MGraph creatMGraph(int vNum)
{
    //初始化
    MGraph mG;
    mG = (MGraph)malloc(sizeof(struct MGNode));
    mG->eNum = 0;
    mG->vNum = vNum;

    //初始化边为无穷大，即无边
    for (int i = 0; i < vNum; i++)
    {
        for (int j = 0; j < vNum; j++)
        {
            mG->edgeW[i][j] = INF;
        }
    }

    return mG;
}

void insertEdge(MGraph mG, Edge e)
{
    mG->edgeW[e->v1][e->v2] = e->w;

    //如果为无向图，则还需执行下行语句
    mG->edgeW[e->v2][e->v1] = e->w;
}

MGraph buildGraph()
{
    MGraph mG;
    Edge e;
    int vNum;
    Vertex v;

    printf("enter the vertex number:\n");
    scanf("%d", &vNum);
    mG = creatMGraph(vNum);

    printf("enter the edge number:\n");
    scanf("%d", &(mG->eNum));
    if (mG->eNum != 0) //如果有边
    {
        e = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < mG->eNum; i++)
        {
            printf("enter the vertex1, vertex2 and the weight of edge:\n");
            scanf("%d %d %d", &(e->v1), &(e->v2), &(e->w));
            insertEdge(mG, e);
        }
    }

    //如果顶点有数据，则指向下面语句
    int flag;
    printf("is exist data of vertex?(yes:1 / no:0):\n");
    scanf("%d", &flag);
    if (flag)
    {
        for (int i = 0; i < mG->vNum; i++)
        {
            printf("enter data of vertex%d:\n", i);
            while (getchar() == '\n')
            {
                continue;
            }
            scanf("%c", &(mG->vData[i]));
        }
    }
    return mG;
}

bool visited[MAXV];

void visit(Vertex v)
{
    printf("visiting %d vertex.\n", v);
}
bool isEdge(MGraph mG, Vertex v1, Vertex v2)
{
    return mG->edgeW[v1][v2] < INF ? true : false;
}
void bfs(MGraph mG, Vertex v, void (*visit)(Vertex))
{
    visit(v);
    visited[v] = true; //标记v结点已访问

    Queue q = creatQueue(MAXV + 1);
    addQ(q, v);
    Vertex tmp;
    while (!isEmpty(q))
    {
        tmp = deleteQ(q);
        for (int i = 0; i < mG->vNum; i++)
        {
            if (!visited[i] && isEdge(mG, tmp, i))
            {
                visit(i);
                visited[i] = true;
                addQ(q, i);
            }
        }
    }
}

int main()
{
    MGraph mG = buildGraph();
    bfs(mG, 0, visit);
    return 0;
}
